#include "graphfactory.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using std::vector;
using std::list;

Graph* GraphFactory::readGraphFromFile (char* input_file_name) {
    FILE* arquivo_entrada = fopen (input_file_name, "r");
    if (arquivo_entrada == NULL){
        std::cerr << "Nao foi possivel abrir o arquivo de entrada" << std::endl;
        exit(-1);
    }

    int V = 0;
    char c = '0';
    while( (c = getc(arquivo_entrada)) && (c!= '\n') ){
        if(c == '0' || c == '1') V++;
    }
    fseek(arquivo_entrada, 0, SEEK_SET);

    Graph* G = new Graph();
    G->adj_ = vector<list<int> >(V);
    G->V_ = V;

    int cst = 0;
    for (int i = 0; i < V; i++){
        for (int j = 0; j < V; j++){
            fscanf (arquivo_entrada, "%d", &cst);
            if (cst) {
                G->adj_[i].push_back (j);
                G->A_++;
            }
        }
    }
    fclose (arquivo_entrada);

    return G;
}
