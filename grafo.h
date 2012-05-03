#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#define Vertex int
#define Edge Arc
#define EDGE ARC
#define graph digraph
#define Graph Digraph
#define GRAPHinit DIGRAPHinit
#define GRAPHdestroy DIGRAPHdestroy

/* Para o dijkstra */
Vertex parnt[maxV];
double cst[maxV];

/* Fila */
Vertex *q;
int inicio, fim;

typedef struct digraph{
	int V;
	int A;
	int **adj;
}*Digraph;

typedef struct {
  Vertex v;
  Vertex w;
  double cst;
} Arc;

Digraph DIGRAPHinit (int V);
void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w, double cst);
void GRAPHinsertE (Graph G, Vertex v, Vertex w, double cst);
void DIGRAPHdestroy (Digraph G, int V);

void PQinit(int maxN);
int PQempty();
Vertex PQdelmin();
void PQdec(Vertexv);
void PQfree();


#endif // GRAFO_H_INCLUDED
