#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>

typedef int Vertex;

class Digraph {
    private:
        int V_;
        int A_;
        std::vector<std::vector<int> > adj_;
    public:
        Digraph ();
        ~Digraph ();
        void insertArc (Vertex v, Vertex w, double cst);
        void insertEdge (Vertex v, Vertex w, double cst);
        friend class GraphBuilder;
};
typedef Digraph Graph;

#endif // GRAPH_H_INCLUDED
