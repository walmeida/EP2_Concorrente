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
char* input_file_name;
Graph G;
Queue<int> *shortest_paths;
Queue<int> paths;         
int num_finished_vertex;
Log& l = Log::getInstance ();

pthread_t *programthread;

/* ep2.exe <número de caminhos mínimos> <arquivo de entrada> [-debug] */
void read_parameters(int argc, char* argv[]){
    if(argc < 3){
      l.error ("Erro na leitura da entrada. Argumentos esperados: <número de caminhos mínimos> <arquivo de entrada> [-debug]\n");
      exit(-1);
    }
    
    n = atoi(argv[1]);
    input_file_name = argv[2];
        
    if(argc > 3){
        bool debug_mode = (strcmp("-debug",argv[3]) == 0);
        Log::setDebugMode(debug_mode);
    }
}

int numberOfProcessors () {
  int num = sysconf(_SC_NPROCESSORS_ONLN);
  if (num < 2) num = 2;
  return num;
}

void *dummy_function(void *arg) {
  int i;
  for ( i=0; i<5; i++ ) {
    printf("Hi!\n");
    sleep(1);
  }
  return NULL;
}

bool create_program_threads(int num_proc){
  programthread = (pthread_t*) malloc( num_proc * sizeof(*programthread));
  if(!programthread)
    return -1;
  
  for(int i = 0; i < num_proc; i++){
    if ( pthread_create( &programthread[i], NULL, dummy_function, NULL) ) {
      printf("error creating thread.");
      return -1;
    }
  }
  
  return 0;
}

int main (int argc, char* argv[]) {
  int num_proc;
  
  read_parameters (argc,argv);
  G = GraphFactory::readGraphFromFile (input_file_name); 
  std::stringstream message;
  num_proc = numberOfProcessors();
  message << "Numero de Processadores On: " << num_proc;
  l.info (message);

  /* Threads */
  if(!create_program_threads(num_proc)){
    exit(-1);
  }
  
  for(int i = 0; i < num_proc; i++){
    if ( pthread_join ( programthread[i], NULL ) ) {
      printf("error joining thread.");
      exit(-1);
    }
  }
  
  /*TODO: free aqui não xD */
  free(programthread);
   
  return 0;
}
