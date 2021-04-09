#ifndef _H_GRAFO
#define _H_GRAFO

#include "stdio.h"
#include "stdlib.h"

typedef void* Grafo;
typedef void* Vertice;
typedef void* Aresta;

Grafo createGrafo(int qtdVertices);
void grafoInsereVertice(Grafo g, char *id, void *info);
void grafoInsereAresta(Grafo g, char *v1, char *v2, void *info);
void freeGrafo(Grafo g, void(*freeVerticeData)(void*), void(*freeArestaData)(void*));
void printGrafo(Grafo g);

#endif