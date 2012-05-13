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

unsigned int n;
Graph* G = NULL;
Queue<Path*> *shortest_paths;
Queue<Path*> paths;         
int num_finished_vertex = 0;
Log& l = Log::getInstance ();

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
    const int num_finished_vertex_final = G->numVertex () - 1; // subtract 1 because of vertex 0
    QueueCond cond (1);
    while (!paths.empty () && (num_finished_vertex < num_finished_vertex_final)){
        Path **next_path = paths.atomicRemove (cond);
        while (next_path != NULL) {
            const Path *path_current = *next_path;
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
                        }
                    }
                }
            }
            delete path_current;
            next_path = paths.atomicRemove (cond);
        }
        cond.incrementSizeCondition ();
        // Barreira
    }
    return NULL;
}

void *dummy_function(void *arg) {
  for (int i=0; i<5; ++i) {
        printf("Hi!\n");
        sleep(1);
    }
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
    
    /* Threads */
    ThreadManager tm(num_proc);
    tm.createAndRunThreads (dummy_function);

    return 0;
}
