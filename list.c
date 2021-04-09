#include "list.h"

typedef struct no{
    struct no *ant;
    struct no *prox;
    void *data;
}No;

typedef struct {
    No *prim;
    No *ult;
    int tam;
}list;

List createLista(){
    list *lista = (list*)malloc(sizeof(list));
    lista->prim = NULL;
    lista->ult = NULL;
    lista->tam = 0;
    return lista;
}

int listLenght(List l){
    list *lista = (list*) l;
    return lista->tam;
}

Node listInsert(List l, void* g){
    No *node = (No*)malloc(sizeof(No));
    node->data = g;

    list *lista = (list*) l;

    if(lista->tam==0){ // lista vazia
        node->ant = NULL;
        lista->prim = node;
    } else{
        lista->ult->prox = node;
        node->ant = lista->ult;
    }

    node->prox = NULL;
    lista->ult = node;
    lista->tam++;

    return node;
}

void freeNode(No *node, void(*func)(void*)){
    func(node->data);
    free(node);
}

void listRemoveNode2(List l, Node node){
    No *cNode = (No*)node;
    list *lista = (list*) l;

    if(!node) return;

    if(lista->tam == 1){
        
        lista->prim = NULL;
        lista->ult = NULL;
    }else{
        if(cNode == lista->prim){
            cNode->prox->ant = NULL;
            lista->prim = cNode->prox;
        }else if(cNode == lista->ult){
            cNode->ant->prox = NULL;
            lista->ult = cNode->ant;
        }else{
            cNode->prox->ant = cNode->ant;
            cNode->ant->prox = cNode->prox;
        }
    }
    
    free(cNode);
    lista->tam--;
}

void *listRemoveNode(List l, Node node){
    No *cNode = (No*)node;
    list *lista = (list*) l;

    if(!node) return NULL;

    if(lista->tam == 1){
        
        lista->prim = NULL;
        lista->ult = NULL;
    }else{
        if(cNode == lista->prim){
            cNode->prox->ant = NULL;
            lista->prim = cNode->prox;
        }else if(cNode == lista->ult){
            cNode->ant->prox = NULL;
            lista->ult = cNode->ant;
        }else{
            cNode->prox->ant = cNode->ant;
            cNode->ant->prox = cNode->prox;
        }
    }

    void *elemento = cNode->data; 
    free(cNode);
    lista->tam--;

    return elemento;
}

void *listRemoveFirst(List l){
    list *lista = (list*) l;
    No *targ;
    if(lista->tam==0) return NULL;
    if(lista->tam == 1){
        targ = lista->prim;
        lista->prim = NULL;
        lista->ult = NULL;
    }else{
        targ = lista->prim;
        lista->prim = targ->prox;
        lista->prim->ant = NULL;
    }
    void *elemento = targ->data;
    free(targ);
    lista->tam--;

    return elemento;    
}

void *listRemoveLast(List l){
    list *lista = (list*) l;
    No *targ;
    if(lista->tam==0) return NULL;
    if(lista->tam == 1){
        targ = lista->prim;
        lista->prim = NULL;
        lista->ult = NULL;
    }else{
        targ = lista->ult;
        lista->ult = targ->ant;
        targ->ant->prox = NULL;
    }
    void *elemento = targ->data;
    free(targ);
    lista->tam--;

    return elemento;
}

void freeLista(List l, void(*freeFunc)(void*)){
    list *lista = (list*) l;
    No *node;
    while(lista->prim != NULL){
        node = lista->prim;
        lista->prim = lista->prim->prox;
        freeNode(node,freeFunc);
    }
    
    free(lista);
}

void freeListaHT(List l, void(*freeFunc)(void*)){
    list *lista = (list*) l;
    No *node;
    while(lista->prim != NULL){
        node = lista->prim;
        lista->prim = lista->prim->prox;
        
        if(freeFunc != NULL) freeFunc(freeChaveXvalor(node->data));
        else freeChaveXvalor(node->data);
        free(node);
    }
    
    free(lista);
}

void freeLista2(List l){ // Função para desalocar a memória de listas auxiliares criadas por funções das quadtree
    list *lista = (list*) l;
    No *node;
    while(lista->prim != NULL){
        node = lista->prim;
        lista->prim = lista->prim->prox;
        free(node);
    }
    
    free(lista);
}

Node listGetById(List l, char id[], char*(*getId)(void*)){

    list *lista = (list*) l;
    if(lista->tam==0) return NULL;
    No *node = lista->prim;
    
    char currentId[100];
    strcpy(currentId, getId(node->data));

    while(strcmp(currentId,id) != 0){
        node = node->prox;
        if(node == NULL) return NULL;
        strcpy(currentId, getId(node->data));
    }
    
    return node;
}

Node listGetByData(List l, void*data){
    list *lista = (list*) l;
    if(lista->tam==0) return NULL;

    No *node = lista->prim;

    while(data != node->data){
        node = node->prox;
        if(node == NULL) return NULL;
    }

    return node;
}

Node listGetFirst(List l){
    list *lista = (list*) l;
    if(lista->tam == 0) return NULL;
    return lista->prim;
}

Node listGetLast(List l){
    list *lista = (list*) l;
    if(lista->tam == 0) return NULL;
    return lista->ult;
}

int nodeHasNext(Node n){
    No *node = (No*) n;
    if(node->prox != NULL) return 1;
    else return 0;
}

Node nodeGetNext(Node n){
    No *node = (No*) n;
    return node->prox;
}

Node nodeGetPrevious(Node n){
    No *node = (No*) n;
    return node->ant;
}

void *nodeGetData(Node n){
    No *node = (No*) n;
    return node->data;
}

Node listInsertBefore(List l, Node t, void* g){
    list *lista = (list*) l;
    No *targ = (No*)t;
    No *node = (No*)malloc(sizeof(No));
    node->data = g;

    if(lista->prim == targ){
        lista->prim = node;
        node->ant = NULL;
    }else{
        node->ant = targ->ant;
        targ->ant->prox = node;
    }

    targ->ant = node;
    node->prox = targ;
    lista->tam++;
    return node;
}

Node listInsertAfter(List l, Node t, void* g){
    list *lista = (list*) l;
    No *targ = (No*)t;
    No *node = (No*)malloc(sizeof(No));
    node->data = g;

    if(lista->ult == targ){
        lista->ult = node;
        node->prox = NULL;
        
    }else{
        targ->prox->ant = node;
        node->prox = targ->prox;
    }

    targ->prox = node;
    node->ant = targ;
    lista->tam++;
    return node;
}