#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <unistd.h>
#include <pthread.h>
#include "graph.h"
#include "queue.h"
#include "path.h"
#include "graphfactory.h"
#include "log.h"

int n;
Graph* G = NULL;
Queue<int> *shortest_paths;
Queue<int> paths;         
int num_finished_vertex;
Log& l = Log::getInstance ();

pthread_t *programthread = NULL;

/* ep2.exe <número de caminhos mínimos> <arquivo de entrada> [-debug] */
char* read_parameters(int argc, char* argv[]){
    if(argc < 3){
      l.error ("Erro na leitura da entrada. Argumentos esperados: <número de caminhos mínimos> <arquivo de entrada> [-debug]\n");
      exit(-1);
    }
    
    n = atoi(argv[1]);
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

void *dummy_function(void *arg) {
    for (int i=0; i<5; ++i) {
        printf("Hi!\n");
        sleep(1);
    }
    return NULL;
}

bool create_program_threads(int num_proc){
    programthread = new pthread_t[num_proc];
    if (!programthread)
        return false;
    for (int i = 0; i < num_proc; ++i){
        if (pthread_create ( &programthread[i], NULL, dummy_function, NULL) ) {
            l.error ("Error creating thread.");
            return false;
        }
    }
    return true;
}

int main (int argc, char* argv[]) {
    char* input_file_name = read_parameters (argc,argv);
    G = GraphFactory::readGraphFromFile (input_file_name); 
    std::stringstream message;
    int num_proc = numberOfProcessors();
    message << "Numero de Processadores On: " << num_proc;
    l.info (message);

    /* Threads */
    if (!create_program_threads(num_proc)){
        exit(-1);
    }

    for (int i = 0; i < num_proc; ++i){
        if (pthread_join (programthread[i], NULL)) {
            l.error ("Error joining thread.");
            exit (-1);
        }
    }

    // TODO delete aqui??
    delete[] programthread;

    return 0;
}
