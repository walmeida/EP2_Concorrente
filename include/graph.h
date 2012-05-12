#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <list>

typedef int Vertex;

class Digraph {
    private:
        int V_;
        int A_;
        std::vector<std::list<int> > adj_; // lista de adjacencia
        Digraph ();
    public:
        ~Digraph ();
        friend class GraphFactory;
};
typedef Digraph Graph;

#endif // GRAPH_H_INCLUDED
