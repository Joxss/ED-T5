#include "grafo.h"
#include "hashTable.h"
#include "math.h"

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

int grafoGetQtdVertices(Grafo g){
    grafo *graph = (grafo*)g;
    return graph->qtdAtual;
}

Vertice* grafoGetVertices(Grafo g){
    grafo *graph = (grafo*)g;
    return (Vertice*)graph->vertices;
}

List grafoVerticeGetAdjacencias(Vertice v){
    vertice *vertex = (vertice*)v;
    return vertex->adjacentes;
}

void* grafoVerticeGetData(Vertice v){
    vertice *vertex = (vertice*)v;
    return vertex->data;
}

Vertice grafoArestaGetDestino(Aresta a){
    aresta *edge = (aresta*) a;
    return edge->fim;
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

    int *indexInicio = hashGetKey(graf->indices,v1);
    int *indexFim = hashGetKey(graf->indices,v2);
    if(indexInicio == NULL || indexFim == NULL){
        printf("Vertinice nao existente\n");
        return;
    }

    aresta *edge = _criaAresta(graf,v1,v2,info);
    
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

int* dijkstra(Grafo g, char *idRaiz, double(*getPeso)(void*)) {
    grafo *graph = (grafo*)g;
    int noInicial = _getIndex(graph,idRaiz);
    double* distancia = (double*) malloc(graph->qtdAtual*sizeof(double));
    int* pai = malloc(sizeof(int) * graph->qtdAtual);
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

    free(distancia);

    return pai;
}

int printMST(int pai[], double pesos[], int n){
    printf("Edge \tWeight\n");
    for (int i = 0; i < n; i++)
        printf("%d - %d \t%lf \n", pai[i], i, pesos[i]);
}

Grafo _converteGrafo(grafo* graph, int pai[], double pesos[]){
    grafo *mst = createGrafo(graph->max);
    for(int i=0;i<graph->qtdAtual; i++){
        grafoInsereVertice(mst,graph->vertices[i]->id,graph->vertices[i]->data);
    }
    char *id1, *id2;
    for(int i=1; i<graph->qtdAtual; i++){
        if(pai[i] == -1){
            continue;
        }
        int indexFim = i, indexInicio = pai[i];

        id1 = graph->vertices[indexInicio]->id;
        id2 = graph->vertices[indexFim]->id;

        aresta* a = _getAresta(graph,id1,id2); // ID1 -> ID2  incio = ID1 - fim = ID2

        aresta* a1 = _criaAresta(mst,id1,id2,a->data);
        listInsert(mst->vertices[indexInicio]->adjacentes,a1);
        
        aresta* a2 = _criaAresta(mst,id2,id1,a->data);
        listInsert(mst->vertices[indexFim]->adjacentes,a2);
    }
    return mst;
}

Grafo primMST(Grafo g, double(*getPeso)(void*)){
    grafo *graph = (grafo*)g;
    int V = graph->qtdAtual;
    int parent[V];
    double key[V];
    int mstSet[V];
    Node nodeEdge;
    aresta *edge;

    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = 1, parent[i] = -1;

    key[0] = 0;
    // parent[0] = -1;
    for (int count = 0; count < V - 1; count++)
    {
        int u = menorDistancia(graph, mstSet, key);
        mstSet[u] = 0;

        nodeEdge = listGetFirst(graph->vertices[u]->adjacentes);
        while (nodeEdge)
        {
            edge = nodeGetData(nodeEdge);
            if (mstSet[edge->fim->index] == 1 && getPeso(edge->data) < key[edge->fim->index])
            {
                parent[edge->fim->index] = u;
                key[edge->fim->index] = getPeso(edge->data);
            }
            nodeEdge = nodeGetNext(nodeEdge);
        }
    }

    //printMST(parent,key,V);
    return _converteGrafo(graph,parent,key);
}

void freeMST(Grafo mst){
    grafo *graf = (grafo*)mst;
    freeHashTable(graf->indices,free);
    for(int i=0;i<graf->qtdAtual;i++){
        freeLista(graf->vertices[i]->adjacentes,free);
        free(graf->vertices[i]);
    }
    free(graf->vertices);
    free(graf);
}

//nao exerce mutação no grafo g
Grafo grafoCopiaParaNaoDirecionado(Grafo original){
    grafo* graph = (grafo*) original;

    grafo *copia = createGrafo(graph->max);
    for(int i=0;i<graph->qtdAtual; i++){
        grafoInsereVertice(copia,graph->vertices[i]->id,graph->vertices[i]->data);
    }
    
    char id1[100], id2[100];
    for(int i=0; i<graph->qtdAtual; i++){
        strcpy(id1,copia->vertices[i]->id);
        List arestas = graph->vertices[i]->adjacentes;
        Node aux = listGetFirst(arestas);
        aresta *edge;
        while(aux){
            edge = nodeGetData(aux);
            strcpy(id2,edge->fim->id);
            if(_getAresta(copia,id1,id2) == NULL){
                aresta *a1 = _criaAresta(copia,id1,id2,edge->data);
                listInsert(copia->vertices[i]->adjacentes,a1);
            }
            if(_getAresta(copia,id2,id1) == NULL){
                aresta *a2 = _criaAresta(copia,id2,id1,edge->data);
                listInsert(copia->vertices[edge->fim->index]->adjacentes, a2);
            }
            aux = nodeGetNext(aux);
        }
    }
    return copia;
}

void montaCaminho(List caminho, grafo *graph, int *pai, int destino){
    if(pai[destino] == -1)
        return;
    montaCaminho(caminho,graph,pai,pai[destino]);
    // printf("%s -> ",graph->vertices[index]->id);
    listInsert(caminho,graph->vertices[destino]);
}

List melhorCaminho(Grafo g, Vertice inicio, Vertice fim, double(*getPeso)(void*), char *txt){
    vertice *vInicio = (vertice*)inicio;
    vertice *vFim = (vertice*)fim;
    int *caminhos = dijkstra(g,vInicio->id,getPeso);
    grafo *graph = (grafo*)g;

    int index1 = vInicio->index;
    int index2 = vFim->index;

    if(caminhos[index2] == -1){
        free(caminhos);
        return NULL;
    }

    List caminho = createLista();
    listInsert(caminho,graph->vertices[index1]);
    montaCaminho(caminho,graph,caminhos,index2);

    free(caminhos);
    // printa txt

    return caminho;
}

Vertice grafoVerticeMaisProximo(Ponto ponto, Grafo g){
    grafo *graph = (grafo*)g;
    double menorDistancia = 9999999999.0;
    int indexMenor = -1;

    for(int i=0; i<graph->qtdAtual; i++){
        double dX = pontoGetX(ponto) - pontoGetX(graph->vertices[i]->data);
        dX = dX*dX;
        double dY = pontoGetY(ponto) - pontoGetY(graph->vertices[i]->data);
        dY = dY*dY;
        double dist = sqrt(dX+dY);
        if(dist < menorDistancia){
            menorDistancia = dist;
            indexMenor = i;
        }
    }

    if(indexMenor < 0) return NULL;

    vertice* v = graph->vertices[indexMenor];
    return v;
}


//