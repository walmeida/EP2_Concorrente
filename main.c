#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "queue.h"
#include "grafo.h"

int debug_mode;
int n;
FILE * arquivo_entrada;
Graph G;
queue *caminhos_minimos;
queue caminhos;         

//ep2.exe <número de caminhos mínimos> <arquivo de entrada> [-debug]
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

int constroi_grafo(){
  int i,j,cst,V;
  char c;
  
  
  if(debug_mode) printf("Debug Mode: On\n"); else printf("Debug Mode: Off\n");
  
  V = 0;
  c = '0';
  
  while( (c = getc(arquivo_entrada)) && (c!= '\n') ){
    if(c == '0' || c == '1') V++;
  }

  fseek(arquivo_entrada, 0, SEEK_SET);
  
  G = GRAPHinit(V);
  
  for(i = 0; i < V; i++){
    for(j = 0; j < V; j++){
      fscanf(arquivo_entrada, "%d", &cst);
      G->adj[i][j] = cst;
      printf("%d ",cst);
    }
    printf("\n");
  }
  
  fclose(arquivo_entrada);
  
  return V;
      
}

int numeroDeProcessadores(){
  int num;
  num = sysconf(_SC_NPROCESSORS_ONLN);
  if (num < 2) num = 2;
  return num;
}

int main(int argc, char* argv[]){
  int V;
  
  leitura_entrada(argc,argv);
  V = constroi_grafo();
  printf("Numero de Processadores On: %d\n",numeroDeProcessadores());
  GRAPHdestroy(G, V);
  
  return 0;
}
