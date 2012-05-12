#ifndef GRAPHBUILDER_H_INCLUDED
#define GRAPHBUILDER_H_INCLUDED

#include <stdio.h>

class GraphBuilder {
    public:
        static Graph readGraphFromFile (FILE* arquivo_entrada);
};

#endif
