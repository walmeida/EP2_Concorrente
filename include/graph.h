#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <list>
#include <algorithm>

typedef int Vertex;

class Digraph {
    private:
        int V_;
        int A_;
        std::vector<std::list<Vertex> > adj_; // lista de adjacencia
        Digraph ();
    public:
        ~Digraph ();
        template <class Function>
        void neighboursForEach (Vertex v, Function f) {
            for_each (adj_[v].begin (), adj_[v].end (), f);
        }
        friend class GraphFactory;
};
typedef Digraph Graph;

#endif // GRAPH_H_INCLUDED
