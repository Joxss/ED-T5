#ifndef _H_GRAFO
#define _H_GRAFO

#include <stdio.h>
#include <stdlib.h>

typedef void* Grafo;
typedef void* Vertice;
typedef void* Aresta;

Grafo createGrafo(int qtdVertices);
void grafoInsereVertice(Grafo g, char *id, void *info);
void grafoInsereAresta(Grafo g, char *v1, char *v2, void *info, double dist, double velocidade);
int grafoExisteAresta(Grafo g, char *v1, char *v2);
void grafoRemoveAresta(Grafo g, char *v1, char *v2, void(*freeArestaData)(void*));
void freeGrafo(Grafo g, void(*freeVerticeData)(void*), void(*freeArestaData)(void*));
void printGrafo(Grafo g);

void getIndexes(Grafo g);

double* dijkstra(Grafo g, char *idRaiz, double(*getPeso)(void*));

#endif