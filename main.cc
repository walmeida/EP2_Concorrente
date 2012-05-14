#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include "graph.h"
#include "queue.h"
#include "path.h"
#include "graphfactory.h"
#include "threadmanager.h"
#include "queuecond.h"
#include "barrier.h"

unsigned int n;
Graph* G = NULL;
Queue<Path*> *shortest_paths;
Queue<Path*> paths;         
int num_finished_vertex = 0;
pthread_mutex_t num_finished_vertex_mutex;
Barrier *barrier = NULL;
bool debug_mode = false;
pthread_mutex_t print_mutex;
int barrier_iterations = 0;
pthread_mutex_t barrier_iterations_mutex;
int current_working_threads = 0;
pthread_mutex_t current_working_threads_mutex;

/* ep2.exe <número de caminhos mínimos> <arquivo de entrada> [-debug] */
char* read_parameters(int argc, char* argv[]){
    if (argc < 3){
        std::cerr << "Erro na leitura da entrada. Argumentos esperados: "
                    "<número de caminhos mínimos> <arquivo de entrada> [-debug]"
                  << std::endl;
        exit (-1);
    }
    
    n = (unsigned int) atoi(argv[1]);
    char* input_file_name = argv[2];
        
    if(argc > 3){
        debug_mode = (strcmp("-debug",argv[3]) == 0);
    }

    return input_file_name;
}

int numberOfProcessors () {
    int num = sysconf(_SC_NPROCESSORS_ONLN);
    if (num < 2) num = 2;
    return num;
}

void printPaths (int iteration_number) {
    pthread_mutex_lock (&print_mutex);
    if (iteration_number)
        std::cout << "Caminhos encontrados na iteracao " << iteration_number
            << ":" << std::endl << std::endl;
    for (int v = 1; v < G->numVertex (); ++v) {
        std::cout << "Para o vertice " << v << ":" << std::endl;
        const std::list<Path*>::const_iterator end = shortest_paths[v].end ();
        unsigned int num_paths = 0;
        for (std::list<Path*>::const_iterator it = shortest_paths[v].begin ();
                it != end; ++it) {
            std::ostringstream path_text;
            (*it)->print (path_text);
            std::cout << path_text.str () << std::endl;
            /* Nao imprimir mais caminhos do que o necessario */
            ++num_paths;
            if(num_paths == n)
                break;
        }
        std::cout << std::endl;
    }
    std::cout.flush ();
    pthread_mutex_unlock (&print_mutex);
}

void *find_path (void *arg) {
    const int *thread_id = (int *) arg;
    const int num_finished_vertex_final = G->numVertex () - 1; // subtract 1 because of vertex 0
    bool is_working = true;
    QueueCond cond (1);
    int barrier_stops = 0;
    while (num_finished_vertex < num_finished_vertex_final) {
        Path *path_current;
        bool has_paths_to_proccess = paths.atomicRemove (cond, path_current);

        pthread_mutex_lock (&current_working_threads_mutex);
        if (has_paths_to_proccess) {
            if (!is_working) { // started to work again
                is_working = true;
                ++current_working_threads;
            }
        } else {
            if (is_working) { // no work left to do right now
                is_working = false;
                --current_working_threads;
            }
        }
        if (current_working_threads == 0) { // no work left to do
            pthread_mutex_unlock (&current_working_threads_mutex);
            break;
        }
        pthread_mutex_unlock (&current_working_threads_mutex);

        while (has_paths_to_proccess) {
            const Vertex v = path_current->lastVertex ();
            const std::list<Vertex>::const_iterator end = G->getNeighboursEnd (v);
            for (std::list<Vertex>::const_iterator it = G->getNeighboursBegin (v);
                    it != end; ++it) {
                const Vertex w = *it;
                if (!path_current->containsVertex (w)) {
                    Path *path_new = new Path (*path_current);
                    path_new->insertVertex (w);
                    paths.atomicInsert (path_new);
                    /* Inserir caminho mínimo na fila de caminhos com índice w */
                    if (shortest_paths[w].size () < n) {
                        const unsigned long new_size = 
                            shortest_paths[w].atomicInsert (new Path (*path_new));
                        if (new_size == n) {
                            pthread_mutex_lock (&num_finished_vertex_mutex);
                            num_finished_vertex++;
                            pthread_mutex_unlock (&num_finished_vertex_mutex);
                        }
                    }
                }
            }
            delete path_current;
            has_paths_to_proccess = paths.atomicRemove (cond, path_current);
        }
        // Barreira
        ++barrier_stops;
        if (debug_mode) {
            pthread_mutex_lock (&print_mutex);
            std::cout << "Iteracao " << cond.getSizeCondition ()
                      << ": Thread " << *thread_id << " chegou na barreira pela "
                      << barrier_stops << "a vez" << std::endl;
            pthread_mutex_unlock (&print_mutex);
        }
        barrier->sync (*thread_id);
        if (debug_mode) {
            ++barrier_stops;

            pthread_mutex_lock (&print_mutex);
            std::cout << "Iteracao " << cond.getSizeCondition ()
                      << ": Thread " << *thread_id << " chegou na barreira pela "
                      << barrier_stops << "a vez" << std::endl;
            pthread_mutex_unlock (&print_mutex);
            
            if (*thread_id == 0) {
                printPaths (cond.getSizeCondition ());
            }
            barrier->sync (*thread_id);
        }
        cond.incrementSizeCondition ();
    }
    barrier->setFinished (*thread_id);
    pthread_mutex_lock (&barrier_iterations_mutex);
    int iterations = cond.getSizeCondition () - 1;
    if (barrier_iterations < iterations)
        barrier_iterations = iterations;
    pthread_mutex_unlock (&barrier_iterations_mutex);
    return NULL;
}

void free_memory () {
    Path *p;
    bool has_elements = paths.remove (p);
    while (has_elements) {
        delete p;
        has_elements = paths.remove (p);
    }

    for (int i = 0; i < G->numVertex (); ++i) {
        has_elements = shortest_paths[i].remove (p);
        while (has_elements) {
            delete p;
            has_elements = shortest_paths[i].remove (p);
        }
    }
    delete[] shortest_paths;
}   

int main (int argc, char* argv[]) {
    char* input_file_name = read_parameters (argc,argv);
    G = GraphFactory::readGraphFromFile (input_file_name); 
    pthread_mutex_init (&print_mutex, NULL);
    pthread_mutex_init (&barrier_iterations_mutex, NULL);
    pthread_mutex_init (&current_working_threads_mutex, NULL);
    pthread_mutex_init (&num_finished_vertex_mutex, NULL);
    int num_proc = numberOfProcessors();
    pthread_mutex_lock (&current_working_threads_mutex);
    current_working_threads = num_proc;
    pthread_mutex_unlock (&current_working_threads_mutex);
    
    /* Fila de caminhos */
    Path *path_zero = new Path ();
    path_zero->insertVertex(0);
    paths.atomicInsert (path_zero);

    shortest_paths = new Queue<Path*>[G->numVertex ()];
    
    /* Threads */
    barrier = new Barrier (num_proc);
    ThreadManager tm (num_proc);
    tm.createAndRunThreads (find_path);

    /* Imprimindo resultado */
    std::cout << std::endl << "Numero de iteracoes: " << barrier_iterations << std::endl;
    std::cout << "As threads se encontraram na barreira "
              << (debug_mode ? barrier_iterations << 1 : barrier_iterations)
              << " vezes (" << (debug_mode ? "2" : "1") << " por iteracao)."
              << std::endl << std::endl;
    printPaths (0);

    pthread_mutex_destroy (&num_finished_vertex_mutex);
    pthread_mutex_destroy (&current_working_threads_mutex);
    pthread_mutex_destroy (&barrier_iterations_mutex);
    pthread_mutex_destroy (&print_mutex);
    free_memory ();

    return 0;
}
