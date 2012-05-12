#include "graph.h" 

Digraph::Digraph () : V_(0), A_(0)  {};

void Digraph::insertArc (Vertex v, Vertex w, double cst) {
    if (v != w && adj_[v][w] == 0){
        adj_[v][w] = cst;
        A_++;
    }
}

Digraph::~Digraph () {};

void Digraph::insertEdge (Vertex v, Vertex w, double cst){
    insertArc (v,w,cst);
    insertArc (w,v,cst);
}

