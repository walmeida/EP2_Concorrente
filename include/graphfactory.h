#ifndef GRAPHFACTORY_H_INCLUDED
#define GRAPHFACTORY_H_INCLUDED

#include "graph.h"

class GraphFactory {
    public:
        static Graph* readGraphFromFile (char* input_file_name);
};

#endif
