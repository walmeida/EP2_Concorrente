#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "graph.h"
#include "queue.h"
#include "graphbuilder.h"

int debug_mode;
int n;
FILE * arquivo_entrada;
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
    
    arquivo_entrada = fopen(argv[2],"r");
    if(arquivo_entrada == NULL){ 
      printf("Nao foi possivel abrir o arquivo de entrada"); 
      exit(-1);
    }
        
    if(argc > 3){
      if(strcmp("-debug",argv[3])==0) debug_mode = 1;
    }
}

void constroi_grafo(){
    G = GraphBuilder::readGraphFromFile (arquivo_entrada); 
}

int numeroDeProcessadores(){
  int num;
  num = sysconf(_SC_NPROCESSORS_ONLN);
  if (num < 2) num = 2;
  return num;
}

int main(int argc, char* argv[]){
  leitura_entrada(argc,argv);
  constroi_grafo();
  printf("Numero de Processadores On: %d\n",numeroDeProcessadores());
  
  return 0;
}
