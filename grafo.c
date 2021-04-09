#include "grafo.h"
#include "list.h"
#include "hashTable.h"

typedef struct{
    char id[50];
    void *data;
    List adjacentes;
}vertice;

typedef struct{
    vertice *inicio;
    vertice *fim;
    void *data;
}aresta;

typedef struct{
    vertice **vertices;
    Htable indices;
    int max, qtdAtual;
}grafo;

Grafo createGrafo(int qtdVertices){
    grafo *graf = malloc(sizeof(grafo));

    graf->vertices = malloc(sizeof(vertice*)*qtdVertices);
    graf->indices = createHashTable(qtdVertices);
    graf->max = qtdVertices;
    graf->qtdAtual = 0;

    return graf;    
}

vertice* _criaVertice(char *id, void *info){
    vertice *vertex = malloc(sizeof(vertice));
    strcpy(vertex->id,id);
    vertex->data = info;
    vertex->adjacentes = createLista();

    return vertex;
}

void grafoInsereVertice(Grafo g, char *id, void *info){
    grafo *graf = (grafo*)g;
    vertice *vertex = _criaVertice(id,info);

    graf->vertices[graf->qtdAtual] = vertex;

    int *indice = malloc(sizeof(int));
    *indice = graf->qtdAtual;

    hashInsert(graf->indices,vertex->id,indice);
    graf->qtdAtual++;
}

aresta* _criaAresta(grafo *graf, char *v1, char *v2, void *info){
    int *index1 = hashGetKey(graf->indices,v1);
    vertice *vertice1 = graf->vertices[*index1];

    int *index2 = hashGetKey(graf->indices,v2);
    vertice *vertice2 = graf->vertices[*index2];

    aresta *edge = malloc(sizeof(aresta));
    edge->inicio = vertice1;
    edge->fim = vertice2;
    edge->data = info;

    return edge;
}

void grafoInsereAresta(Grafo g, char *v1, char *v2, void *info){
    grafo *graf = (grafo*)g;
    aresta *edge = _criaAresta(graf,v1,v2,info);
    
    int *indexInicio = hashGetKey(graf->indices,v1);
    vertice *inicio = graf->vertices[*indexInicio];

    listInsert(inicio->adjacentes,edge);
}

void _freeAresta(aresta *a , void(*freeArestaData)(void*)){
    freeArestaData(a->data);
    free(a);
}

void _freeVertice(vertice *vertex, void(*freeVerticeData)(void*), void(*freeArestaData)(void*)){
    while(listLenght(vertex->adjacentes) != 0){
        aresta *edge = listRemoveFirst(vertex->adjacentes);
        _freeAresta(edge,freeArestaData);
    }
    free(vertex->adjacentes);

    freeVerticeData(vertex->data);
    free(vertex);
}

void freeGrafo(Grafo g, void(*freeVerticeData)(void*), void(*freeArestaData)(void*)){
    grafo *graf = (grafo*)g;
    freeHashTable(graf->indices,free);
    for(int i=0; i<graf->qtdAtual; i++){
        _freeVertice(graf->vertices[i],freeVerticeData,freeArestaData);
    }
    free(graf->vertices);

    free(graf);
}

void printGrafo(Grafo g){
    grafo *graf = (grafo*) g;
    for(int i=0; i<graf->qtdAtual; i++){
        vertice *vert = graf->vertices[i];
        Node auxAresta = listGetFirst(vert->adjacentes);
        while(auxAresta){
            aresta *ares = nodeGetData(auxAresta);
            printf("(%s->%s), ",ares->inicio->id,ares->fim->id);
            auxAresta = nodeGetNext(auxAresta);
        }
        printf("\n");
    }
}
