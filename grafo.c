#include "grafo.h" 
double maxcst; // A ser definido dinammicamente

Digraph DIGRAPHinit (int V){
	Digraph G;
	int i,j;

	G = malloc(sizeof *G);
	G->V = V;
	G->A = 0;
	G->adj = malloc(V * sizeof(int *));
	for (i = 0; i < V; i++)
    G->adj[i] = malloc(V * sizeof(int));

   	for (i = 0; i < V; i++)
      for (j = 0; j < V; j++)
      		G->adj[i][j] = 0;

	return G;
}

void DIGRAPHinsertA (Digraph G, Vertex v, Vertex w, double cst) {
    if (v != w && G->adj[v][w] == 0){
      G->adj[v][w] = cst;
      G->A++;
    }
}

void DIGRAPHdestroy (Digraph G, int V){
	int i;

  /* Liberando o espaço dos vetores de listas e do Digrafo */
	for (i = 0; i < V; i++){
      free(G->adj[i]);
	}
	free(G->adj);
	free(G);
}

void GRAPHinsertE (Graph G, Vertex v, Vertex w, double cst){
	DIGRAPHinsertA (G,v,w,cst);
	DIGRAPHinsertA (G,w,v,cst);
}


/*void PQinit(int maxN) {
    q=(Vertex*)malloc(maxN*sizeof(Vertex));
    inicio = 0;
    fim = 0;
}

int PQempty() {
    return inicio==fim;
}

void PQinsert(Vertex v){
    q[fim++] = v;
}

Vertex PQdelmin() {
    int i, j; Vertex x;
    i = inicio;
    for (j=i+1; j < fim; j++)
        if (cst[q[i]] > cst[q[j]]) i = j;
    x = q[i];
    q[i] = q[--fim];
    return x;
}

void PQdec(Vertexv) {
     //faz nada xD 
}

void PQfree() {
    free(q);
}*/
