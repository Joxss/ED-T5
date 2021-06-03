#include "grafo.h"
#include "list.h"
#include "hashTable.h"

#define INT_MAX 999999999
typedef struct{
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

struct MinHeapNode{
    int v;
    int dist;
};

struct MinHeap{

    // Number of heap nodes present currently
    int size;

    // Capacity of min heap
    int capacity;

    // This is needed for decreaseKey()
    int *pos;
    struct MinHeapNode **array;
};

struct MinHeapNode *newMinHeapNode(int v,
                                   int dist){
    struct MinHeapNode *minHeapNode =
        (struct MinHeapNode *)
            malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

struct MinHeap *createMinHeap(int capacity){
    struct MinHeap *minHeap =
        (struct MinHeap *)
            malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(
        capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
        (struct MinHeapNode **)
            malloc(capacity *
                   sizeof(struct MinHeapNode *));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode **a,
                     struct MinHeapNode **b){
    struct MinHeapNode *t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap *minHeap,
                int idx){
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist <
            minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist <
            minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx){
        // The nodes to be swapped in min heap
        struct MinHeapNode *smallestNode = minHeap->array[smallest];
        struct MinHeapNode *idxNode = minHeap->array[idx];

        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

int isEmpty(struct MinHeap *minHeap)
{
    return minHeap->size == 0;
}

struct MinHeapNode *extractMin(struct MinHeap *
                                   minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    // Store the root node
    struct MinHeapNode *root =
        minHeap->array[0];

    // Replace root node with last node
    struct MinHeapNode *lastNode =
        minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Update position of last node
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Function to decreasy dist value
// of a given vertex v. This function
// uses pos[] of min heap to get the
// current index of node in min heap
void decreaseKey(struct MinHeap *minHeap, int v, int dist){
    // Get the index of v in  heap array
    int i = minHeap->pos[v];

    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;

    // Travel up while the complete
    // tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->dist <
                    minHeap->array[(i - 1) / 2]->dist)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] =
            (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],
                        &minHeap->array[(i - 1) / 2]);

        // move to parent index
        i = (i - 1) / 2;
    }
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
int isInMinHeap(struct MinHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return 1;
    return 0;
}

void printPath(int parent[], int j)
{

    // Base Case : If j is source
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j]);

    printf("%d ", j);
}

// A utility function used to print the solution
int printSolution(int dist[], int n,
                  int parent[])
{
    int src = 0;
    printf("Vertex\t Distance\tPath");
    for (int i = 1; i < n; i++)
    {
        printf("\n%d -> %d \t\t %d\t\t%d ",
               src, i, dist[i], src);
        printPath(parent, i);
    }
}

void dijkstra(Grafo g, int src)
{
    grafo *graph = (grafo*)g;
    // Get the number of vertices in graph
    int V = graph->qtdAtual;

    // dist values used to pick
    // minimum weight edge in cut
    int dist[V];
    int parent[V];

    // minHeap represents set E
    struct MinHeap *minHeap = createMinHeap(V);

    // Initialize min heap with all
    // vertices. dist value of all vertices
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v,
                                           dist[v]);
        minHeap->pos[v] = v;
        parent[0] = -1;
    }

    // Make dist value of src vertex
    // as 0 so that it is extracted first
    minHeap->array[src] =
        newMinHeapNode(src, dist[src]);
    minHeap->pos[src] = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    // Initially size of min heap is equal to V
    minHeap->size = V;

    // In the followin loop,
    // min heap contains all nodes
    // whose shortest distance
    // is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with
        // minimum distance value
        struct MinHeapNode *minHeapNode =
            extractMin(minHeap);

        // Store the extracted vertex number
        int u = minHeapNode->v;

        // Traverse through all adjacent
        // vertices of u (the extracted
        // vertex) and update
        // their distance values
        Node nodeCrawl =
            listGetFirst(graph->vertices[u]->adjacentes);
            
        while (nodeCrawl != NULL){
            aresta *pCrawl = nodeGetData(nodeCrawl);
            int v = _getIndex(graph, pCrawl->fim->id);

            // If shortest distance to v is
            // not finalized yet, and distance to v
            // through u is less than its
            // previously calculated distance
            if (isInMinHeap(minHeap, v) &&
                dist[u] != INT_MAX &&
                pCrawl->distancia + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->distancia;
                parent[v] = u;
                // update distance
                // value in min heap also
                decreaseKey(minHeap, v, dist[v]);
            }
            nodeCrawl = nodeGetNext(nodeCrawl);
        }
    }

    // print the calculated shortest distances
    printSolution(dist, V, parent);
}





//