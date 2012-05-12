#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "graph.h"
#include "queue.h"
#include "graphfactory.h"
#include "log.h"

int n;
char* nome_arquivo_entrada;
Graph G;
Queue<int> *caminhos_minimos;
Queue<int> caminhos;         

/* ep2.exe <número de caminhos mínimos> <arquivo de entrada> [-debug] */
void leitura_entrada(int argc, char* argv[]){
    if(argc < 3){
      printf("Erro na leitura da entrada. Argumentos esperados: <número de caminhos mínimos> <arquivo de entrada> [-debug]\n");
      exit(-1);
    }
    
    n = atoi(argv[1]);
    nome_arquivo_entrada = argv[2];
        
    if(argc > 3){
        bool debug_mode = (strcmp("-debug",argv[3]) == 0);
        Log::setDebugMode(debug_mode);
    }
}

int numeroDeProcessadores(){
  int num = sysconf(_SC_NPROCESSORS_ONLN);
  if (num < 2) num = 2;
  return num;
}

int main(int argc, char* argv[]){
  leitura_entrada(argc,argv);
  G = GraphFactory::readGraphFromFile (nome_arquivo_entrada); 
  printf("Numero de Processadores On: %d\n",numeroDeProcessadores());
  
  return 0;
}
