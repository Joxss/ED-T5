#ifndef _H_GRAFO
#define _H_GRAFO

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
typedef void* Grafo;
typedef void* Vertice;
typedef void* Aresta;

Grafo createGrafo(int qtdVertices);

// Retorna um array de vertices
Vertice* grafoGetVertices(Grafo g);

// Retorna a lista de adjacencia de um vertice v
List grafoVerticeGetAdjacencias(Vertice v);

// Retorna a quantiade de vertices de um grafo g 
int grafoGetQtdVertices(Grafo g);

// Retorna um void pointer representando a data armazenada no vertice v
void* grafoVerticeGetData(Vertice v);

char* grafoVerticeGetId(Vertice v);

Vertice grafoArestaGetInicio(Aresta a);

// Retorna o vertice de destino da aresta edge
Vertice grafoArestaGetFim(Aresta a);

void* grafoArestaGetData(Aresta a);

// o ponto retornado precisa ser desalocado!
Ponto grafoArestaGetPontoMedio(Aresta a);

// 1 = SUL 2 = NORTE 3 = LESTE 4 = OESTE
int grafoArestaGetOrientacao(Aresta a);

Vertice grafoInsereVertice(Grafo g, char *id, void *info);

Vertice* grafoRemoveVertice(Grafo g, Vertice v, void(*freeVerticeData)(void*), void(*freeArestaData)(void*));

void grafoInsereAresta(Grafo g, char *v1, char *v2, void *info);

char* verticeGetId(Vertice v);

int grafoExisteAresta(Grafo g, char *v1, char *v2);

void grafoRemoveAresta(Grafo g, char *v1, char *v2, void(*freeArestaData)(void*));

void freeGrafo(Grafo g, void(*freeVerticeData)(void*), void(*freeArestaData)(void*));

void printGrafo(Grafo g);

void getIndexes(Grafo g);

int* dijkstra(Grafo g, char *idRaiz, double(*getPeso)(void*));

/* Obtem a árvore geradora minima de um grafo não direcionado. O Grafo retornado DEVE ter sua memória desalocada utlizando a função freeMST
*  Parâmetros: Recebe um ponteiro não nulo para o grafo, e um ponteiro para a função que obtem o peso das arestas.
*  Retorno: Retorna um grafo não orientado contendo apenas as arestas que fazem parte da arvore geradora minima */
Grafo primMST(Grafo g, double(*getPeso)(void*));

/* Desaloca a memória de um grafo não orientado gerado pelo função primMST.
*  Parâmetros: Recebe um ponteiro não nulo para o grafo não orientado.
*  Retorno: Não possui retorno. */
void freeMST(Grafo mst);

Grafo grafoCopiaParaNaoDirecionado(Grafo original);

List melhorCaminho(Grafo g, Vertice inicio, Vertice fim, double(*getPeso)(void*), FILE *txt);

Vertice grafoVerticeMaisProximo(Ponto ponto, Grafo g);

void grafoMarkDeleted(Vertice v);
#endif