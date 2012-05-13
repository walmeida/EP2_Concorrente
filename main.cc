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

int n;
Graph* G = NULL;
Queue<Path> *shortest_paths;
Queue<Path> paths;         
int num_finished_vertex;
Log& l = Log::getInstance ();

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

int main (int argc, char* argv[]) {
    char* input_file_name = read_parameters (argc,argv);
    G = GraphFactory::readGraphFromFile (input_file_name); 
    std::stringstream message;
    int num_proc = numberOfProcessors();
    message << "Numero de Processadores On: " << num_proc;
    l.info (message);

    /* Threads */
    ThreadManager tm(num_proc);
    tm.createAndRunThreads (dummy_function);

    return 0;
}
