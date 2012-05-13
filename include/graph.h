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
        std::list<Vertex>::const_iterator getNeighboursBegin (Vertex v) {
            return adj_[v].begin ();
        }
        const std::list<Vertex>::const_iterator getNeighboursEnd (Vertex v) {
            return adj_[v].end ();
        }
        friend class GraphFactory;
};
typedef Digraph Graph;

#endif // GRAPH_H_INCLUDED
