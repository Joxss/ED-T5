#include "grafo.h"
#include "list.h"
#include "hashTable.h"

#define INT_MAX 999999999
typedef struct{
    int index;
    char id[50];
    void *data;
    List adjacentes;
}vertice;

typedef struct{
    vertice *inicio;
    vertice *fim;
    int distancia;
    int velocidadeMedia;
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

void grafoInsereVertice(Grafo g, char *id, void *info){
    grafo *graf = (grafo*)g;
    vertice *vertex = _criaVertice(id,info,graf->qtdAtual);

    graf->vertices[graf->qtdAtual] = vertex;

    int *indice = malloc(sizeof(int));
    *indice = graf->qtdAtual;

    hashInsert(graf->indices,vertex->id,indice);
    graf->qtdAtual++;
}

aresta* _criaAresta(grafo *graf, char *v1, char *v2, void *info, int distancia, int velocidade){
    int *index1 = hashGetKey(graf->indices,v1);
    vertice *vertice1 = graf->vertices[*index1];

    int *index2 = hashGetKey(graf->indices,v2);
    vertice *vertice2 = graf->vertices[*index2];

    aresta *edge = malloc(sizeof(aresta));
    edge->inicio = vertice1;
    edge->fim = vertice2;
    edge->data = info;

    edge->distancia = distancia;
    edge-> velocidadeMedia = velocidade;

    return edge;
}

void grafoInsereAresta(Grafo g, char *v1, char *v2, void *info, int dist, int velocidade){
    grafo *graf = (grafo*)g;
    aresta *edge = _criaAresta(graf,v1,v2,info,dist,velocidade);
    
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

void iniciaDijkstra(grafo* grafo, int* distancia, int* pai, int noInicial) {
    for(int i = 0; i < grafo->qtdAtual; i++) {
        distancia[i] = INT_MAX;
        pai[i] = -1;
    }
    distancia[noInicial] = 0;
}

void relaxa(grafo* grafo, int* distancia, int* pai, int no1, int no2) {
    Node nodeEdge = listGetFirst(grafo->vertices[no1]->adjacentes);
    aresta *edge = NULL;
    while(nodeEdge){
        edge = nodeGetData(nodeEdge);
        if(edge->fim->index == no2)
            break;
        nodeEdge = nodeGetNext(nodeEdge);
    }

    if(nodeEdge && edge) {
        if(distancia[no2] > distancia[no1] + edge->distancia) {
            distancia[no2] = distancia[no1] + edge->distancia;
            pai[no2] = no1;
        }
    }
}

// void relaxa(Grafo* grafo, int* distancia, int* pai, int no1, int no2) {
//     Adjacencia* aresta = grafo->arranjo[no1].inicio;

//     while(aresta && aresta->vertice != no2) 
//         aresta = aresta->proximo;

//     if(aresta) {
//         if(distancia[no2] > distancia[no1] + aresta->peso) {
//             distancia[no2] = distancia[no1] + aresta->peso;
//             pai[no2] = no1;
//         }
//     }
// }

int existeAberto(grafo* grafo, int* aberto) {
    for(int i = 0; i < grafo->qtdAtual; i++) {
        if(aberto[i])
            return 1;
    }
    
    return 0;
}

int menorDistancia(grafo* grafo, int* aberto, int* distancia) {
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

int* dijkstra(Grafo g, char *idRaiz) {
    grafo *graph = (grafo*)g;
    int noInicial = _getIndex(graph,idRaiz);
    int* distancia = (int*) malloc(graph->qtdAtual*sizeof(int));
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
            relaxa(graph, distancia, pai, menor, edge->fim->index);
            nodeEdge = nodeGetNext(nodeEdge);
        }
    }

    printaCaminhos(graph,pai,noInicial);

    return distancia;
}





//