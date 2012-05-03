#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include grafo.h

int debug_mode;
int n;
FILE * arquivo_entrada;

//ep2.exe <número de caminhos mínimos> <arquivo de entrada> [-debug]
void leitura_entrada(int argc, char* argv[]){
    if(argc < 3){
      printf("Erro na leitura da entrada. Argumentos esperados: <número de caminhos mínimos> <arquivo de entrada> [-debug]\n");
      exit(-1);
    }
    if(argc == 3){
      n = atoi(argv[1]);
      arquivo_entrada = fopen(argv[2],"r");
      return;
    }
    if(strcmp("-debug",argv[3])==0) debug_mode = 1;
}

void monta_grafo(){

}

int main(int argc, char* argv[]){
  leitura_entrada(argc,argv);
  monta_grafo();
  return 0;
}
