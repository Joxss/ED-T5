#include "grafo.h"
#include "list.h"
#include "hashTable.h"

#define INT_MAX 999999999
typedef struct{
    int index;
    char id[100];
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

int _getIndex(grafo *graph, char *id){
    int *index = hashGetKey(graph->indices, id);
    return *index;
}

void getIndexes(Grafo g){
    grafo *graph = (grafo*)g;
    for(int i=0; i<graph->qtdAtual; i++){
        printf("%d - %s\n", i, graph->vertices[i]->id);
    }
}

Grafo createGrafo(int qtdVertices){
    grafo *graf = malloc(sizeof(grafo));

    graf->vertices = malloc(sizeof(vertice*)*qtdVertices);
    graf->indices = createHashTable(qtdVertices);
    graf->max = qtdVertices;
    graf->qtdAtual = 0;

    return graf;    
}

vertice* _criaVertice(char *id, void *info, int index){
    vertice *vertex = malloc(sizeof(vertice));
    strcpy(vertex->id,id);
    vertex->data = info;
    vertex->adjacentes = createLista();
    vertex->index = index;

    return vertex;
}

Vertice grafoInsereVertice(Grafo g, char *id, void *info){
    grafo *graf = (grafo*)g;
    vertice *vertex = _criaVertice(id,info,graf->qtdAtual);

    graf->vertices[graf->qtdAtual] = vertex;

    int *indice = malloc(sizeof(int));
    *indice = graf->qtdAtual;

    hashInsert(graf->indices,vertex->id,indice);
    graf->qtdAtual++;
    return vertex;
}

char* verticeGetId(Vertice v){
    vertice *vertex = (vertice*)v;
    return vertex->id;
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

aresta* _getAresta(Grafo g, char *v1, char *v2){
    grafo *graf = (grafo*)g;
    int indexV1 = _getIndex(graf,v1);
    List arestas = graf->vertices[indexV1]->adjacentes;
    Node aux = listGetFirst(arestas);
    aresta *edge;
    while(aux){
        edge = nodeGetData(aux);
        if(strcmp(edge->fim->id,v2) == 0)
            return edge;

        aux = nodeGetNext(aux);
    }
    return NULL;
}

int grafoExisteAresta(Grafo g, char *v1, char *v2){
    if(_getAresta(g,v1,v2))
        return 1;
    return 0;
}

void grafoRemoveAresta(Grafo g, char *v1, char *v2, void(*freeArestaData)(void*)){
    grafo *graf = (grafo*)g;
    int indexV1 = _getIndex(graf,v1);
    List arestas = graf->vertices[indexV1]->adjacentes;
    Node aux = listGetFirst(arestas);
    aresta *edge;
    while(aux){
        edge = nodeGetData(aux);
        if(strcmp(edge->fim->id,v2) == 0)
            break;

        aux = nodeGetNext(aux);
    }
    if(!aux){
        freeArestaData(listRemoveNode(arestas,aux));
        printf("Removeu\n");
    }
    return;
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

void iniciaDijkstra(grafo* grafo, double* distancia, int* pai, int noInicial) {
    for(int i = 0; i < grafo->qtdAtual; i++) {
        distancia[i] = INT_MAX;
        pai[i] = -1;
    }
    distancia[noInicial] = 0;
}

void relaxa(grafo* grafo, double* distancia, int* pai, int no1, int no2, double(*getPeso)(void*)) {
    Node nodeEdge = listGetFirst(grafo->vertices[no1]->adjacentes);
    aresta *edge = NULL;
    while(nodeEdge){
        edge = nodeGetData(nodeEdge);
        if(edge->fim->index == no2)
            break;
        nodeEdge = nodeGetNext(nodeEdge);
    }

    if(nodeEdge && edge) {
        if(distancia[no2] > distancia[no1] + getPeso(edge->data)) {
            distancia[no2] = distancia[no1] + getPeso(edge->data);
            pai[no2] = no1;
        }
    }
}

int existeAberto(grafo* grafo, int* aberto) {
    for(int i = 0; i < grafo->qtdAtual; i++) {
        if(aberto[i])
            return 1;
    }
    
    return 0;
}

int menorDistancia(grafo* grafo, int* aberto, double* distancia) {
    int i, menor;
    
    for(i = 0; i < grafo->qtdAtual; i++) {
        if(aberto[i])
            break;
    }
    
    if(i == grafo->qtdAtual)
        return -1;
    
    menor = i;

    for(i = i+1; i < grafo->qtdAtual; i++) {
        if(aberto[i] && distancia[menor] > distancia[i])
            menor = i;
    }
    return menor;
}

void printaCaminho(grafo *graph, int *pai, int i){
    if(pai[i] == -1)
        return;
    printaCaminho(graph,pai,pai[i]);
    int index = pai[i];
    printf("%s -> ",graph->vertices[index]->id);
}

void printaCaminhos(grafo *graph, int *pai, int raiz){

    for(int i=0; i<graph->qtdAtual; i++){
        printf("Caminho de %s para %s:  ",graph->vertices[raiz]->id,graph->vertices[i]->id);
        if(pai[i]==-1)
            printf("Nao ha caminho disponivel\n");
        else{
            printaCaminho(graph,pai,i);
            printf("%s\n",graph->vertices[i]->id);
        }
    }
}

double* dijkstra(Grafo g, char *idRaiz, double(*getPeso)(void*)) {
    grafo *graph = (grafo*)g;
    int noInicial = _getIndex(graph,idRaiz);
    double* distancia = (double*) malloc(graph->qtdAtual*sizeof(double));
    int pai[graph->qtdAtual];
    int menor;
    int aberto[graph->qtdAtual];
    Node nodeEdge;
    aresta *edge;
    
    iniciaDijkstra(graph, distancia, pai, noInicial);

    for(int i = 0; i < graph->qtdAtual; i++) 
        aberto[i] = 1;

    while (existeAberto(graph, aberto))
    {
        menor = menorDistancia(graph, aberto, distancia);
        aberto[menor] = 0;

        nodeEdge = listGetFirst(graph->vertices[menor]->adjacentes);
        while(nodeEdge) {
            edge = nodeGetData(nodeEdge);
            relaxa(graph, distancia, pai, menor, edge->fim->index,getPeso);
            nodeEdge = nodeGetNext(nodeEdge);
        }
    }

    printaCaminhos(graph,pai,noInicial);

    return distancia;
}





//