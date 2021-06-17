#include "QuadTree.h"
#include "calculos.h"
#include "convexHull.h"
#include "quadra.h"

typedef struct Qt{
    Ponto coordenada;
    Generic elemento;
    
    struct Qt *nw;
    struct Qt *ne;
    struct Qt *sw;
    struct Qt *se;

    struct Qt *parent;
    
    int deleted;
}Qnode;

typedef struct{
    Qnode *root;
    char*(*getId)(void*);
    int size;
    int qtdRemovidos;
}Qtree;

Qnode *createQuadNode(Ponto p, Generic info){
    Qnode *qt = (Qnode*)malloc(sizeof(Qnode));

    qt->coordenada = p;
    qt->elemento = info;

    qt->nw = NULL;
    qt->ne = NULL;
    qt->sw = NULL;
    qt->se = NULL;
    qt->parent = NULL;
    qt->deleted = 0;
    return qt;
}

QuadTree createQuadTree(getKey idFunc){
    Qtree *qt = (Qtree*)malloc(sizeof(Qtree));
    qt->getId = idFunc;
    qt->size = 0;
    qt->root = NULL;
    qt->qtdRemovidos = 0;
    
    return qt;
}

int _QtGetRegion(Qnode *parent, double x, double y){
    double xParent = pontoGetX(parent->coordenada), yParent = pontoGetY(parent->coordenada);

    if(x <= xParent && y < yParent || x == xParent && y == yParent){ // SE
        return 1;
    }
    else if(x > xParent && y <= yParent){ // SW
        return 2;
    }
    else if(x < xParent && y >= yParent){ // NE
        return 3;
    }
    else if(x >= xParent && y > yParent){ // NW
        return 4;
    }
}

QuadNode QtInsert(QuadTree tree, Ponto p, void *info){
    Qtree *qt = (Qtree*)tree;
    if(qt->root == NULL){
        Qnode *aux = createQuadNode(p,info);
        qt->root = aux;
        qt->size++;
        return aux;
    }
    else{
        Qnode *pai;
        Qnode *aux = qt->root;
        int region;
        
        while(aux != NULL){
            region = _QtGetRegion(aux,pontoGetX(p),pontoGetY(p));
            pai = aux;
            if(region == 1) aux = pai->se;
            else if(region == 2) aux = pai->sw;
            else if(region == 3) aux = pai->ne;
            else if(region == 4) aux = pai->nw;

        }
        aux = createQuadNode(p,info);
        aux->parent = pai;
        if(region == 1)pai->se = aux;
        else if(region == 2) pai->sw = aux;
        else if(region == 3) pai->ne = aux;
        else if(region == 4) pai->nw = aux;
        qt->size++;
        return aux;
    }
}

QuadNode QtGetRoot(QuadTree tree){
    Qtree *qtr = (Qtree *) tree;

    return qtr->root;
}

QuadNode QtGetParent(QuadNode tree){
    Qnode *qtr = (Qnode *) tree;

    return qtr->parent;
}

QuadNode QtGetNW(QuadNode tree){
    if(tree == NULL) return NULL;
    Qnode *qt = (Qnode*)tree;

    return qt->nw;
}

QuadNode QtGetNE(QuadNode tree){
    if(tree == NULL) return NULL;
    Qnode *qt = (Qnode*)tree;

    return qt->ne;
}

QuadNode QtGetSW(QuadNode tree){
    if(tree == NULL) return NULL;
    Qnode *qt = (Qnode*)tree;

    return qt->sw;
}

QuadNode QtGetSE(QuadNode tree){
    if(tree == NULL) return NULL;
    Qnode *qt = (Qnode*)tree;

    return qt->se;
}

QuadNode QtGetNode(QuadTree tree, double x, double y){
    Qtree *qt = (Qtree*)tree;

    if(qt->root == NULL) return NULL;

    Qnode *aux = qt->root;
    int region;
    while(pontoGetX(aux->coordenada) != x || pontoGetY(aux->coordenada) != y){
        region = _QtGetRegion(aux,x,y);
        if(region == 1) aux = aux->se;
        if(region == 2) aux = aux->sw;
        if(region == 3) aux = aux->ne;
        if(region == 4) aux = aux->nw;
        if(aux == NULL) break;
    }

    if(aux != NULL) return aux;
    else return NULL;
}

Generic QtGetInfo(QuadTree tree, QuadNode qNode){
    if(qNode == NULL) return NULL;
    Qnode *node = (Qnode*)qNode;
    if(node->deleted == 1){
        return NULL;
    }
    return node->elemento;
}

// Generic QNodeGetInfo(QuadNode n){
//     Qnode *node = (Qnode*)n;
//     return node->elemento;
// }

int QtGetQtdRemovidos(QuadTree tree){
    Qtree *q = (Qtree *) tree;
    return q->qtdRemovidos;
}

void _ChavesDentroCirculoAux(List lista, Qnode *qt, double x, double y, double r, char*(*getId)(void*)){ // TEM COMO MELHORAR
    if(qt == NULL) return;

    if(checkInsideCirc(qt->elemento,x,y,r) && qt->deleted != 1){
        char *id = getId(genericGetValores(qt->elemento));
        char *chave = malloc(sizeof(char)*strlen(id)+1);
        strcpy(chave,id);
        listInsert(lista,chave);
        _ChavesDentroCirculoAux(lista,qt->nw,x,y,r,getId);
        _ChavesDentroCirculoAux(lista,qt->ne,x,y,r,getId);
        _ChavesDentroCirculoAux(lista,qt->sw,x,y,r,getId);
        _ChavesDentroCirculoAux(lista,qt->se,x,y,r,getId);
    }else{
        if(pontoGetY(qt->coordenada) <= y-r){ // ACIMA DA CIRCUNFERENCIA
            _ChavesDentroCirculoAux(lista,qt->nw,x,y,r,getId);
            _ChavesDentroCirculoAux(lista,qt->ne,x,y,r,getId);
        }else if(pontoGetX(qt->coordenada) >= x+r){ // A DIREITA DA CIRCUNFERENCIA
            _ChavesDentroCirculoAux(lista,qt->se,x,y,r,getId);
            _ChavesDentroCirculoAux(lista,qt->ne,x,y,r,getId);
        }else if(pontoGetY(qt->coordenada) >= y+r){ // ABAIXO DA CIRCUNFERENCIA
            _ChavesDentroCirculoAux(lista,qt->se,x,y,r,getId);
            _ChavesDentroCirculoAux(lista,qt->sw,x,y,r,getId);
        }else if(pontoGetX(qt->coordenada) <= x-r){ // ABAIXO DA CIRCUNFERENCIA
            _ChavesDentroCirculoAux(lista,qt->sw,x,y,r,getId);
            _ChavesDentroCirculoAux(lista,qt->nw,x,y,r,getId);
        }else{
            _ChavesDentroCirculoAux(lista,qt->nw,x,y,r,getId);
            _ChavesDentroCirculoAux(lista,qt->ne,x,y,r,getId);
            _ChavesDentroCirculoAux(lista,qt->sw,x,y,r,getId);
            _ChavesDentroCirculoAux(lista,qt->se,x,y,r,getId);
        }
    }
}

List QtChavesDentroCirculo(QuadTree tree, double x, double y, double r){
    List lista = createLista();
    if(tree == NULL) return lista;

    Qtree *qt = (Qtree*)tree;
    _ChavesDentroCirculoAux(lista,qt->root,x,y,r,qt->getId);

    return lista;
}

void _ChavesDentroRetanguloAux(List lista, Qnode *qt, double x, double y, double w, double h, char*(*getId)(void*)){ // TEM COMO MELHORAR
    if(qt == NULL) return;

    if(checkRectInsideRect(qt->elemento,x,y,w,h) && qt->deleted != 1){
        char *id = getId(genericGetValores(qt->elemento));
        char *chave = malloc(sizeof(char)*strlen(id)+1);
        strcpy(chave,id);
        listInsert(lista,chave);
        _ChavesDentroRetanguloAux(lista,qt->nw,x,y,w,h,getId);
        _ChavesDentroRetanguloAux(lista,qt->ne,x,y,w,h,getId);
        _ChavesDentroRetanguloAux(lista,qt->sw,x,y,w,h,getId);
        _ChavesDentroRetanguloAux(lista,qt->se,x,y,w,h,getId);
    }else{
        if(pontoGetY(qt->coordenada) <= y){
            _ChavesDentroRetanguloAux(lista,qt->nw,x,y,w,h,getId);
            _ChavesDentroRetanguloAux(lista,qt->ne,x,y,w,h,getId);

        }else if(pontoGetX(qt->coordenada) >= x+w){
            _ChavesDentroRetanguloAux(lista,qt->se,x,y,w,h,getId);
            _ChavesDentroRetanguloAux(lista,qt->ne,x,y,w,h,getId);

        }else if(pontoGetY(qt->coordenada) >= y+h){
            _ChavesDentroRetanguloAux(lista,qt->se,x,y,w,h,getId);
            _ChavesDentroRetanguloAux(lista,qt->sw,x,y,w,h,getId);

        }else if(pontoGetX(qt->coordenada) <= x){
            _ChavesDentroRetanguloAux(lista,qt->sw,x,y,w,h,getId);
            _ChavesDentroRetanguloAux(lista,qt->nw,x,y,w,h,getId);
        }else{
            _ChavesDentroRetanguloAux(lista,qt->nw,x,y,w,h,getId);
            _ChavesDentroRetanguloAux(lista,qt->ne,x,y,w,h,getId);
            _ChavesDentroRetanguloAux(lista,qt->sw,x,y,w,h,getId);
            _ChavesDentroRetanguloAux(lista,qt->se,x,y,w,h,getId);
        }
    }
}

List QtChavesDentroRetangulo(QuadTree tree, double x1, double y1, double x2, double y2){

    List lista = createLista();
    if(tree == NULL) return lista;

    Qtree *qt = (Qtree*)tree;
    _ChavesDentroRetanguloAux(lista,qt->root,x1,y1,x2-x1,y2-y1,qt->getId);

    return lista;
}

void _PontosDentroCirculoAux(List lista, Qnode *qt, double x, double y, double r){ // TEM COMO MELHORAR
    if(qt == NULL) return;

    if(checkInsideCirc(qt->elemento,x,y,r) && qt->deleted != 1){
        Ponto p = createPoint(pontoGetX(qt->coordenada),pontoGetY(qt->coordenada));
        listInsert(lista,p);
        _PontosDentroCirculoAux(lista,qt->nw,x,y,r);
        _PontosDentroCirculoAux(lista,qt->ne,x,y,r);
        _PontosDentroCirculoAux(lista,qt->sw,x,y,r);
        _PontosDentroCirculoAux(lista,qt->se,x,y,r);
    }else{
        if(pontoGetY(qt->coordenada) <= y-r){ // ACIMA DA CIRCUNFERENCIA
            _PontosDentroCirculoAux(lista,qt->nw,x,y,r);
            _PontosDentroCirculoAux(lista,qt->ne,x,y,r);
        }else if(pontoGetX(qt->coordenada) >= x+r){ // A DIREITA DA CIRCUNFERENCIA
            _PontosDentroCirculoAux(lista,qt->se,x,y,r);
            _PontosDentroCirculoAux(lista,qt->ne,x,y,r);
        }else if(pontoGetY(qt->coordenada) >= y+r){ // ABAIXO DA CIRCUNFERENCIA
            _PontosDentroCirculoAux(lista,qt->se,x,y,r);
            _PontosDentroCirculoAux(lista,qt->sw,x,y,r);
        }else if(pontoGetX(qt->coordenada) <= x-r){ // ABAIXO DA CIRCUNFERENCIA
            _PontosDentroCirculoAux(lista,qt->sw,x,y,r);
            _PontosDentroCirculoAux(lista,qt->nw,x,y,r);
        }else{
            _PontosDentroCirculoAux(lista,qt->nw,x,y,r);
            _PontosDentroCirculoAux(lista,qt->ne,x,y,r);
            _PontosDentroCirculoAux(lista,qt->sw,x,y,r);
            _PontosDentroCirculoAux(lista,qt->se,x,y,r);
        }
    }
}

List QtPontosDentroCirculo(QuadTree tree, double x, double y, double r){
    List lista = createLista();
    if(tree == NULL) return lista;

    Qtree *qt = (Qtree*)tree;
    _PontosDentroCirculoAux(lista,qt->root,x,y,r);

    return lista;
}

void _PontosDentroRetanguloAux(List lista, Qnode *qt, double x, double y, double w, double h){ // TEM COMO MELHORAR
    if(qt == NULL) return;

    if(checkRectInsideRect(qt->elemento,x,y,w,h) && qt->deleted != 1){
        Ponto p = createPoint(pontoGetX(qt->coordenada),pontoGetY(qt->coordenada));
        listInsert(lista,p);
        _PontosDentroRetanguloAux(lista,qt->nw,x,y,w,h);
        _PontosDentroRetanguloAux(lista,qt->ne,x,y,w,h);
        _PontosDentroRetanguloAux(lista,qt->sw,x,y,w,h);
        _PontosDentroRetanguloAux(lista,qt->se,x,y,w,h);
    }else{
        if(pontoGetY(qt->coordenada) <= y){
            _PontosDentroRetanguloAux(lista,qt->nw,x,y,w,h);
            _PontosDentroRetanguloAux(lista,qt->ne,x,y,w,h);

        }else if(pontoGetX(qt->coordenada) >= x+w){
            _PontosDentroRetanguloAux(lista,qt->se,x,y,w,h);
            _PontosDentroRetanguloAux(lista,qt->ne,x,y,w,h);

        }else if(pontoGetY(qt->coordenada) >= y+h){
            _PontosDentroRetanguloAux(lista,qt->se,x,y,w,h);
            _PontosDentroRetanguloAux(lista,qt->sw,x,y,w,h);

        }else if(pontoGetX(qt->coordenada) <= x){
            _PontosDentroRetanguloAux(lista,qt->sw,x,y,w,h);
            _PontosDentroRetanguloAux(lista,qt->nw,x,y,w,h);
        }else{
            _PontosDentroRetanguloAux(lista,qt->nw,x,y,w,h);
            _PontosDentroRetanguloAux(lista,qt->ne,x,y,w,h);
            _PontosDentroRetanguloAux(lista,qt->sw,x,y,w,h);
            _PontosDentroRetanguloAux(lista,qt->se,x,y,w,h);
        }
    }
}

List QtPontosDentroRetangulo(QuadTree tree, double x1, double y1, double x2, double y2){

    List lista = createLista();
    if(tree == NULL) return lista;

    Qtree *qt = (Qtree*)tree;
    _PontosDentroRetanguloAux(lista,qt->root,x1,y1,x2-x1,y2-y1);

    return lista;
}

void _NosDentroCirculoAux(List lista, Qnode *qt, double x, double y, double r){ // TEM COMO MELHORAR
    if(qt == NULL) return;

    if(checkInsideCirc(qt->elemento,x,y,r) && qt->deleted != 1){
        listInsert(lista,qt->elemento);
        _NosDentroCirculoAux(lista,qt->nw,x,y,r);
        _NosDentroCirculoAux(lista,qt->ne,x,y,r);
        _NosDentroCirculoAux(lista,qt->sw,x,y,r);
        _NosDentroCirculoAux(lista,qt->se,x,y,r);
    }else{
        if(pontoGetY(qt->coordenada) <= y-r){ // ACIMA DA CIRCUNFERENCIA
            _NosDentroCirculoAux(lista,qt->nw,x,y,r);
            _NosDentroCirculoAux(lista,qt->ne,x,y,r);
        }else if(pontoGetX(qt->coordenada) >= x+r){ // A DIREITA DA CIRCUNFERENCIA
            _NosDentroCirculoAux(lista,qt->se,x,y,r);
            _NosDentroCirculoAux(lista,qt->ne,x,y,r);
        }else if(pontoGetY(qt->coordenada) >= y+r){ // ABAIXO DA CIRCUNFERENCIA
            _NosDentroCirculoAux(lista,qt->se,x,y,r);
            _NosDentroCirculoAux(lista,qt->sw,x,y,r);
        }else if(pontoGetX(qt->coordenada) <= x-r){ // ABAIXO DA CIRCUNFERENCIA
            _NosDentroCirculoAux(lista,qt->sw,x,y,r);
            _NosDentroCirculoAux(lista,qt->nw,x,y,r);
        }else{
            _NosDentroCirculoAux(lista,qt->nw,x,y,r);
            _NosDentroCirculoAux(lista,qt->ne,x,y,r);
            _NosDentroCirculoAux(lista,qt->sw,x,y,r);
            _NosDentroCirculoAux(lista,qt->se,x,y,r);
        }
    }
}

List QtNosDentroCirculo(QuadTree tree, double x, double y, double r){
    List lista = createLista();
    if(tree == NULL) return lista;

    Qtree *qt = (Qtree*)tree;
    _NosDentroCirculoAux(lista,qt->root,x,y,r);

    return lista;
}

void _NosDentroRetanguloAux(List lista, Qnode *qt, double x, double y, double w, double h){ // TEM COMO MELHORAR
    if(qt == NULL) return;

    // if(checkRectInsideRect(qt->elemento,x,y,w,h) && qt->deleted != 1){
    //     listInsert(lista,qt->elemento);
    // }
    if(checkRectInsideRect(qt->elemento,x,y,w,h) && qt->deleted != 1){
        listInsert(lista,qt->elemento);
        _NosDentroRetanguloAux(lista,qt->nw,x,y,w,h);
        _NosDentroRetanguloAux(lista,qt->ne,x,y,w,h);
        _NosDentroRetanguloAux(lista,qt->sw,x,y,w,h);
        _NosDentroRetanguloAux(lista,qt->se,x,y,w,h);
    }else{
        if(pontoGetY(qt->coordenada) < y){
            _NosDentroRetanguloAux(lista,qt->nw,x,y,w,h);
            _NosDentroRetanguloAux(lista,qt->ne,x,y,w,h);

        }else if(pontoGetX(qt->coordenada) > x+w){
            _NosDentroRetanguloAux(lista,qt->se,x,y,w,h);
            _NosDentroRetanguloAux(lista,qt->ne,x,y,w,h);

        }else if(pontoGetY(qt->coordenada) > y+h){
            _NosDentroRetanguloAux(lista,qt->se,x,y,w,h);
            _NosDentroRetanguloAux(lista,qt->sw,x,y,w,h);

        }else if(pontoGetX(qt->coordenada) < x){
            _NosDentroRetanguloAux(lista,qt->sw,x,y,w,h);
            _NosDentroRetanguloAux(lista,qt->nw,x,y,w,h);
        }else{
            _NosDentroRetanguloAux(lista,qt->nw,x,y,w,h);
            _NosDentroRetanguloAux(lista,qt->ne,x,y,w,h);
            _NosDentroRetanguloAux(lista,qt->sw,x,y,w,h);
            _NosDentroRetanguloAux(lista,qt->se,x,y,w,h);
        }
    }

    // _NosDentroRetanguloAux(lista,qt->nw,x,y,w,h);
    // _NosDentroRetanguloAux(lista,qt->ne,x,y,w,h);
    // _NosDentroRetanguloAux(lista,qt->sw,x,y,w,h);
    // _NosDentroRetanguloAux(lista,qt->se,x,y,w,h);
}

List QtNosDentroRetangulo(QuadTree tree, double x1, double y1, double x2, double y2){

    List lista = createLista();
    if(tree == NULL) return lista;

    Qtree *qt = (Qtree*)tree;
    _NosDentroRetanguloAux(lista,qt->root,x1,y1,x2-x1,y2-y1);

    return lista;
}

void _QtPercorreProfundidade(Qnode *tree, funcVisita f, ExtraInfo e){
    if(tree == NULL) return;
    
    if(!tree->deleted) f(tree->elemento, e);
    
    _QtPercorreProfundidade(tree->nw,f,e);
    _QtPercorreProfundidade(tree->ne,f,e);
    _QtPercorreProfundidade(tree->sw,f,e);
    _QtPercorreProfundidade(tree->se,f,e);
}

void QtPercorreProfundidade(QuadTree tree, funcVisita f, ExtraInfo e){
    if(tree == NULL) return;
    Qtree *qt = (Qtree*)tree;

    _QtPercorreProfundidade(qt->root,f,e);
}

void QtPercorreLargura(QuadTree tree, funcVisita f, ExtraInfo e){
    List fila = createLista();

    Qtree *qt = (Qtree*)tree;

    Qnode *aux = qt->root;
    listInsert(fila,aux);
    while(listLenght(fila) != 0){
        Node node = listGetFirst(fila);
        Qnode *qNode = nodeGetData(node);
        f(qNode->elemento, e);
        listRemoveFirst(fila);

        if(qNode->se != NULL) listInsert(fila,qNode->se);
        if(qNode->sw != NULL) listInsert(fila,qNode->sw);
        if(qNode->ne != NULL) listInsert(fila,qNode->ne);
        if(qNode->nw != NULL) listInsert(fila,qNode->nw);

    }

    freeLista2(fila);
}

// Generic _QtRemoveNode(Qtree *tree, QuadNode node){
//     if(tree == NULL) return NULL;
    
//     if(tree->cell == node && tree->deleted != 1){
//         tree->deleted = 1;
//         return tree->cell->elemento;
//     } else {
        
//         Generic targ = _QtRemoveNode(tree->nw,node);
//         if(targ != NULL) return targ;

//         targ = _QtRemoveNode(tree->ne,node);
//         if(targ != NULL) return targ;

//         targ = _QtRemoveNode(tree->sw,node);
//         if(targ != NULL) return targ;

//         targ = _QtRemoveNode(tree->se,node);
//         if(targ != NULL) return targ;

//         return NULL;
//     }
// }

Generic QtRemoveNode(QuadTree tree, QuadNode node){
    if(node == NULL || tree == NULL) return NULL;
    Qtree *qt = (Qtree*)tree;

    Qnode *qNode = (Qnode*)node;
    
    if(qNode->deleted == 1) return NULL;

    qt->qtdRemovidos++;
    qNode->deleted = 1;

    return qNode->elemento;
}

void _freeQt(Qnode *tree, void(*freeNodeData)(void*)){
    if(tree == NULL) return;

    freeNodeData(tree->elemento);

    
    _freeQt(tree->nw, freeNodeData);
    _freeQt(tree->ne, freeNodeData);
    _freeQt(tree->sw, freeNodeData);
    _freeQt(tree->se, freeNodeData);
    
    free(tree);
}

void freeQt(QuadTree tree, void(*freeNodeData)(void*)){
    if(tree == NULL) return;

    Qtree *qt = (Qtree*)tree;
    
    if(qt->root != NULL){
        _freeQt(qt->root,freeNodeData);
    }
    
    free(qt);
}

void _freeQt2(Qnode *tree){
    if(tree == NULL) return;

    _freeQt2(tree->nw);
    _freeQt2(tree->ne);
    _freeQt2(tree->sw);
    _freeQt2(tree->se);
    
    free(tree);
}

void freeQt2(QuadTree tree){
    if(tree == NULL) return;

    Qtree *qt = (Qtree*)tree;
    
    if(qt->root != NULL){
        _freeQt2(qt->root);
    }
    
    free(qt);
}

QuadNode _QtGetById(Qnode *tree, char *id, char*(*getId)(void*)){
    if(tree == NULL) return NULL;

    if(!strcmp(getId(genericGetValores(tree->elemento)),id) && tree->deleted != 1){
        return tree;
    } else{
        Qnode *targ = _QtGetById(tree->nw,id, getId);
        if(targ != NULL) return targ;

        targ = _QtGetById(tree->ne,id, getId);
        if(targ != NULL) return targ;

        targ = _QtGetById(tree->sw,id, getId);
        if(targ != NULL) return targ;

        targ = _QtGetById(tree->se,id, getId);
        if(targ != NULL) return targ;

        return NULL;
    }
}

QuadNode QtGetById(QuadTree tree, char *id){ // PRECISA TESTAR
    if(tree == NULL) return NULL;

    Qtree *qt = (Qtree*)tree; 
    if(qt->root == NULL) return NULL;

    return _QtGetById(qt->root,id,qt->getId);
}

int _QtGetLenght(Qnode *tree){
    int tamanho = 0;

    if(tree == NULL ) return 0;

    if(!tree->deleted) tamanho++;

    tamanho += _QtGetLenght(tree->nw);
    tamanho += _QtGetLenght(tree->ne);
    tamanho += _QtGetLenght(tree->sw);
    tamanho += _QtGetLenght(tree->se);

    return tamanho;
}

int QtGetLenght(QuadTree tree){
    if(tree == NULL) return 0;
    Qtree *qt = (Qtree*)tree;

    return  _QtGetLenght(qt->root);
}

void _QtCopiaArvore(Qtree *nova, Qnode *original){
    if(original == NULL) return;

    if(original->deleted != 1) QtInsert(nova,original->coordenada,original->elemento);

    _QtCopiaArvore(nova,original->se);
    _QtCopiaArvore(nova,original->sw);
    _QtCopiaArvore(nova,original->ne);
    _QtCopiaArvore(nova,original->nw);

    if(original->deleted == 1) freeGeneric(original->elemento);
    free(original);
}

void QtRefazArvore(QuadTree tree){
    Qtree *qt = (Qtree*)tree;
    if(qt->root == NULL) return;

    Qnode *original = qt->root;
    qt->root = NULL;
    qt->size = 0;
    qt->qtdRemovidos = 0;

    _QtCopiaArvore(qt,original);
}

void QtOrdenarInsercao(QuadTree tree, List lista){
    if(lista == NULL) return;
    if(listLenght(lista) == 0) return;
    int countStack = 0;
    Generic *stack = malloc(sizeof(Generic)*listLenght(lista));
    
    //calcula a envoltoria convexa enquanto existe
    while(listLenght(lista) != 0){
        int tam;
        Generic *convex = convexHull(lista,&tam);
        if(convex != NULL){
            for(int i=0; i<tam; i++){
                Generic elemento = convex[i];
                stack[countStack] = elemento;
                countStack++;

                Node nodeLista = listGetByData(lista,elemento);
                listRemoveNode(lista,nodeLista);
            }
            free(convex);

        }else if(convex == NULL){
            Node nodeLista = listGetFirst(lista);
            Node aux;

            while(nodeLista != NULL){
                Generic elemento = nodeGetData(nodeLista);
                stack[countStack] = elemento;
                countStack++;
                
                aux = nodeLista;
                nodeLista = nodeGetNext(nodeLista);
                listRemoveNode(lista,aux);
            }
        }
    }

    for(int i=countStack-1; i>=0; i--){
        Generic elemento = stack[i];
        Ponto p = genericGetPonto(elemento);

        QtInsert(tree,p,elemento);
    }

    free(stack);
}

void _QuadTreeToList(Qnode *qt, List l){
    if(qt == NULL) return;

    Generic elemento = qt->elemento;
    if(elemento != NULL) listInsert(l,elemento);

    _QuadTreeToList(qt->nw,l);
    _QuadTreeToList(qt->ne,l);
    _QuadTreeToList(qt->sw,l);
    _QuadTreeToList(qt->se,l);
}

List QuadTToList(QuadTree tree){
    Qtree *qt = (Qtree*)tree;
    List list = createLista();
    _QuadTreeToList(qt->root,list);
    return list;
}