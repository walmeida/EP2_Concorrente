#include "graphfactory.h"
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

using std::vector;

Graph GraphFactory::readGraphFromFile (char* input_file_name) {
    FILE* arquivo_entrada = fopen (input_file_name, "r");
    if (arquivo_entrada == NULL){
        Log& l = Log::getInstance ();
        l.error ("Nao foi possivel abrir o arquivo de entrada"); 
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
    Log& l = Log::getInstance ();
    for (int i = 0; i < V; i++){
        std::stringstream ss;
        for (int j = 0; j < V; j++){
            fscanf (arquivo_entrada, "%d", &cst);
            G.adj_[i][j] = cst;
            ss << cst << " ";
        }
        l.info (ss);
    }

    fclose (arquivo_entrada);

    return G;
}
