#ifndef GRAPHFACTORY_H_INCLUDED
#define GRAPHFACTORY_H_INCLUDED

#include "graph.h"

class GraphFactory {
    public:
        static Graph readGraphFromFile (char* nome_arquivo_entrada);
};

#endif
