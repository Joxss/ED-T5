#ifndef _H_GRAFO
#define _H_GRAFO

/* 
    Esse header especifica um TAD que representa um grafo não direcionado, podendo ser utilizado como direcionado,
    e possui funções para inserção e remoção de vértices e arestas, desalocamento e acesso das variáveis do grafo, 
    alem de algoritimos conhecidos como o melhor caminho utilizando dijkstra e arvore geradora minima utilizando prim.
*/

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
typedef void* Grafo;
typedef void* Vertice;
typedef void* Aresta;

/* Inicialzia um novo grafo com espaçi para até n vértices. O ponteiro retornado deve ter sua memória desalocada pela função freeGrafo
*  Parâmetros: Recebe a quantidade maxima de vértieces do grafo.
*  Retorno: Retorna um ponteiro para o grafo criado. */ 
Grafo createGrafo(int qtdVertices);

/* Obtem os vértices de um grafo. Nenhum vertice deve ter sua memória desalocada
*  Parâmetros: Recebe o ponteiro para o grafo.
*  Retorno: Retorna um array contendo os vertices do grafo. */ 
Vertice* grafoGetVertices(Grafo g);

/* Obtem a lista de adjacencia de um vértice. Nenhuma node da lista deve ter sua memória desalocada
*  Parâmetros: Recebe o ponteiro para o vertice.
*  Retorno: Retorna uma lista de adjacencia contendo todas as arestas que saem do vertice. */ 
List grafoVerticeGetAdjacencias(Vertice v);

/* Obtem a quantidade de vertices de um grafo.
*  Parâmetros: Recebe o ponteiro para o vertice.
*  Retorno: Retorna um inteiro contendo a quantidade de vertices. */ 
int grafoGetQtdVertices(Grafo g);

/* Obtem a informação armazenada em um vértice. O ponteiro retornado não deve ter sua memória desalocada
*  Parâmetros: Recebe o ponteiro para o vertice.
*  Retorno: Retorna um void* contendo a informação armazenada. */ 
void* grafoVerticeGetData(Vertice v);

/* Obtem o id de um vértice.
*  Parâmetros: Recebe o ponteiro para o vertice.
*  Retorno: Retorna uma string contendo o id. */ 
char* grafoVerticeGetId(Vertice v);

/* Obtem a origem de uma aresta
*  Parâmetros: Recebe o ponteiro para a aresta.
*  Retorno: Retorna o vertice de onde sai a aresta. */ 
Vertice grafoArestaGetInicio(Aresta a);

/* Obtem o destino de uma aresta
*  Parâmetros: Recebe o ponteiro para a aresta.
*  Retorno: Retorna o vertice de onde chega a aresta. */
Vertice grafoArestaGetFim(Aresta a);

/* Obtem a informação armazenada em uma aresta. O ponteiro retornado não deve ter sua memória desalocada
*  Parâmetros: Recebe o ponteiro para a aresta.
*  Retorno: Retorna um void* contendo a informação armazenada. */ 
void* grafoArestaGetData(Aresta a);

/* Obtem o ponto médio de uma aresta. O ponteiro retornado deve ter sua memória desalocada usando a função freePonto
*  Parâmetros: Recebe o ponteiro para a aresta.
*  Retorno: Retorna um ponto contendo a coordenada do ponto médio da aresta. */ 
Ponto grafoArestaGetPontoMedio(Aresta a);

// 1 = SUL 2 = NORTE 3 = LESTE 4 = OESTE
/* Obtem a orientação de uma aresta.
*  Parâmetros: Recebe o ponteiro para a aresta.
*  Retorno: Retorna um inteiro representando a orientação da aresta. 1 = SUL 2 = NORTE 3 = LESTE 4 = OESTE 5 = DIAGONAL */ 
int grafoArestaGetOrientacao(Aresta a);

/* Insere um novo vértice no grafo
*  Parâmetros: Recebe o ponteiro para o grafo, o identificador do vértice e a informação que será armazenada no vértice.
*  Retorno: Retorna um ponto contendo a coordenada do ponto médio da aresta. */ 
Vertice grafoInsereVertice(Grafo g, char *id, void *info);

/* Remove um vértice de um grafo e todas as arestas que saem ou chegam nesse vértice. 
   Essa função desaloca a memória das informações armazenadas no vertice e arestas removidos
*  Parâmetros: Recebe o ponteiro para o grafo, o ponteiro do vértice que sera removido 
               e ponteiro para as funções que desalocam a memória das informações armazenadas no vertice e nas arestas
*  Retorno: Retorna um array de vértices sem o vertice removido. */ 
Vertice* grafoRemoveVertice(Grafo g, Vertice v, void(*freeVerticeData)(void*), void(*freeArestaData)(void*));

/* Insere uma nova aresta no grafo.
*  Parâmetros: Recebe o ponteiro para o grafo, o identificador do vértice de origem, o identificador do vertice de destino e a informação que sera armazenada na aresta
*  Retorno: Não possui retorno. */ 
void grafoInsereAresta(Grafo g, char *v1, char *v2, void *info);

/* Checa se existe uma aresta de um vértice para outro.
*  Parâmetros: Recebe o ponteiro para o grafo, o identificador do vértice de origem e o identificador do vertice de destino
*  Retorno: Retorna 1 caso a aresta exista e 0 caso a aresta não exista. */ 
int grafoExisteAresta(Grafo g, char *v1, char *v2);

/* Remove uma aresta de um grafo, caso a aresta exista
*  Parâmetros: Recebe o ponteiro para o grafo, o identificador do vértice de origem e o identificador do vertice de destino
               e um ponteiro para a função que desaloca a memória da informação contida na aresta
*  Retorno: Não possui retorno. */ 
void grafoRemoveAresta(Grafo g, char *v1, char *v2, void(*freeArestaData)(void*));

/* Desaloca a memória de um grafo e das informações contidas nos vértices e arestas
*  Parâmetros: Recebe o ponteiro para o grafo, e ponteiros para as funções que desalocam as informações dos vértices e arestas
*  Retorno: Não possui retorno. */ 
void freeGrafo(Grafo g, void(*freeVerticeData)(void*), void(*freeArestaData)(void*));

/* Obtem a árvore geradora minima de um grafo não direcionado. O Grafo retornado DEVE ter sua memória desalocada utlizando a função freeMST
*  Parâmetros: Recebe um ponteiro não nulo para o grafo, e um ponteiro para a função que obtem o peso das arestas.
*  Retorno: Retorna um grafo não orientado contendo apenas as arestas que fazem parte da arvore geradora minima */
Grafo primMST(Grafo g, double(*getPeso)(void*));

/* Desaloca a memória de um grafo sem desalocar a memória da inforamção contida nos vértices e arestas
*  Parâmetros: Recebe um ponteiro não nulo para o grafo não orientado.
*  Retorno: Não possui retorno. */
void freeMST(Grafo mst);

/* Copia um orientado para um grafo não orientado onde todas as arestas do grafo original são arestas ida e volta no grafo retornado.
   O Grafo retornado DEVE ter sua memória desalocada utlizando a função freeMST
*  Parâmetros: Recebe um ponteiro não nulo para o grafo.
*  Retorno: Retorna um grafo não orientado com as arestas do grafo original*/
Grafo grafoCopiaParaNaoDirecionado(Grafo original);

/* Calcula o melhor caminho de um vértice para outro e escreve esse caminho em um arquivo txt se necessário.
   A lista contendo o caminho retonada deve ter sua memória desalocada pela função freeLista2
*  Parâmetros: Recebe um ponteiro não nulo para o grafo, ponteiros não nulos os vertices de inicio e destino,
               um ponteiro para a função que obtem o peso de uma aresta e um ponteiro para o arquivo txt (se for nulo não escreve no arquivo).
*  Retorno: Retorna uma lista contendo os vértices na ordem que deve serem seguidos para o caminho. */
List melhorCaminho(Grafo g, Vertice inicio, Vertice fim, double(*getPeso)(void*), FILE *txt);

/* Obtem o vértice mais próximo que não está marcado como deletado e possui pelo menos uma aresta
*  Parâmetros: Recebe um ponteiro não nulo para o ponto de referencia e um ponteiro não nulo para o grafo.
*  Retorno: Retorna o vértice mais proximo que está diponível, caso não haja vértices disponiveis retorna NULL. */
Vertice grafoVerticeMaisProximo(Ponto ponto, Grafo g);

/* Marca um vértice como deletado. Essa função é relevante apenas para a função melhorCaminho e grafoVerticeMaisProximo como uma alternativa eficiente à deleção de um vértice
*  Parâmetros: Recebe um ponteiro não nulo para o vértice.
*  Retorno: Não possui retorno. */
void grafoMarkDeleted(Vertice v);
#endif