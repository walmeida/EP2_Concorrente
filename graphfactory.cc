#include "graphfactory.h"
#include <stdio.h>

using std::vector;

Graph GraphFactory::readGraphFromFile (char* nome_arquivo_entrada) {
    //TODO arrumar
    int debug_mode = 0;

    if(debug_mode) printf("Debug Mode: On\n"); else printf("Debug Mode: Off\n");

    FILE* arquivo_entrada = fopen (nome_arquivo_entrada, "r");
    if (arquivo_entrada == NULL){ 
      printf("Nao foi possivel abrir o arquivo de entrada"); 
      exit(-1);
    }

    int V = 0;
    char c = '0';
    while( (c = getc(arquivo_entrada)) && (c!= '\n') ){
        if(c == '0' || c == '1') V++;
    }
    fseek(arquivo_entrada, 0, SEEK_SET);

    Graph G = Graph();
    G.adj_ = vector<vector<int> >(V);
    for (vector<vector<int> >::iterator it = G.adj_.begin();
            it != G.adj_.end(); ++it) {
        *it = vector<int>(V);
    }
    int cst = 0;
    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j++){
            fscanf (arquivo_entrada, "%d", &cst);
            G.adj_[i][j] = cst;
            printf ("%d ",cst);
        }
        printf ("\n");
    }

    fclose (arquivo_entrada);

    return G;
}
