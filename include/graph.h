#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#include <stdlib.h>

#define Vertex int
#define Edge Arc
#define EDGE ARC
#define graph digraph
#define Graph Digraph
#define GRAPHinit DIGRAPHinit
#define GRAPHdestroy DIGRAPHdestroy

typedef struct digraph{
	int V;
	int A;
	int **adj;
}*Digraph;

Digraph DIGRAPHinit (int V);
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w, double cst);
void GRAPHinsertE (Graph G, Vertex v, Vertex w, double cst);
void DIGRAPHdestroy (Digraph G, int V);

#endif
