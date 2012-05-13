#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <unistd.h>
#include "graph.h"
#include "queue.h"
#include "path.h"
#include "graphfactory.h"
#include "log.h"
#include "threadmanager.h"
#include "queuecond.h"
#include "barrier.h"

unsigned int n;
Graph* G = NULL;
Queue<Path*> *shortest_paths;
Queue<Path*> paths;         
int num_finished_vertex = 0;
Log& l = Log::getInstance ();
Barrier *barrier = NULL;

/* ep2.exe <número de caminhos mínimos> <arquivo de entrada> [-debug] */
char* read_parameters(int argc, char* argv[]){
    if(argc < 3){
      l.error ("Erro na leitura da entrada. Argumentos esperados: <número de caminhos mínimos> <arquivo de entrada> [-debug]\n");
      exit(-1);
    }
    
    n = (unsigned int) atoi(argv[1]);
    char* input_file_name = argv[2];
        
    if(argc > 3){
        bool debug_mode = (strcmp("-debug",argv[3]) == 0);
        Log::setDebugMode(debug_mode);
    }

    return input_file_name;
}

int numberOfProcessors () {
    int num = sysconf(_SC_NPROCESSORS_ONLN);
    if (num < 2) num = 2;
    return num;
}

void *find_path (void *arg) {
    const int *thread_id = (int *) arg;
    const int num_finished_vertex_final = G->numVertex () - 1; // subtract 1 because of vertex 0
    QueueCond cond (1);
    while (!paths.empty () && (num_finished_vertex < num_finished_vertex_final)){
        Path **next_path = paths.atomicRemove (cond);
        printf ("num finished vertex = %d of %d\n", num_finished_vertex, num_finished_vertex_final);
        while (next_path != NULL) {
            const Path *path_current = *next_path;
            if (path_current == NULL) {
                l.error ("!!!!!!!!!!!!!!!!!!!!OH OH!!!!!!!!!!!!!!!!");
                break;
            } else {
                printf ("Thread %d processando mais um caminho\n", *thread_id);
               /* std::stringstream* ss;
                ss = path_current->print ();
                *ss << " (thread " << *thread_id << ")\n";
                std::cout << ss->str();
                delete ss;
                */
                printf ("Restam %lu caminhos\n", paths.size());
            }
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
                            num_finished_vertex++;
                        } else {
                            printf ("Found %lu paths for vertex %d\n", new_size, w);
                        } 
                    }
                }
            }
            delete path_current;
            next_path = paths.atomicRemove (cond);
            printf ("Thread %d indo para prox iteracao\n", *thread_id);
        }
        cond.incrementSizeCondition ();
        // Barreira
        printf ("Thread %d passando pela barreira\n", *thread_id);
        barrier->sync (*thread_id);
        printf ("Thread %d passou pela barreira\n", *thread_id);
    }
    barrier->setFinished (*thread_id);
    printf ("Thread %d acabou\n", *thread_id);
    return NULL;
}

int main (int argc, char* argv[]) {
    char* input_file_name = read_parameters (argc,argv);
    G = GraphFactory::readGraphFromFile (input_file_name); 
    std::stringstream message;
    int num_proc = numberOfProcessors();
    message << "Numero de Processadores On: " << num_proc;
    l.info (message);
    
    /* Fila de caminhos */
    Path *path_zero = new Path ();
    path_zero->insertVertex(0);
    paths.atomicInsert (path_zero);

    shortest_paths = new Queue<Path*>[G->numVertex ()];
    
    /* Threads */
    barrier = new Barrier (num_proc);
    ThreadManager tm (num_proc);
    tm.createAndRunThreads (find_path);

    delete[] shortest_paths;

    return 0;
}
