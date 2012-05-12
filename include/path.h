#ifndef PATH_H_
#define PATH_H_

#include <list>
#include "graph.h"

class Path {
    private:
        std::list<Vertex> path_;
    public:
        Path ();
        ~Path ();
        bool containsVertex (Vertex v);
        void insertVertex (Vertex v);
        int size ();
};

#endif
