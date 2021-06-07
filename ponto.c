#include "ponto.h"

typedef struct p{
    double x;
    double y;
}ponto;

Ponto createPoint(double x, double y){
    ponto *p = (ponto*)malloc(sizeof(ponto));
    p->x = x;
    p->y = y;
    return p;
}

double pontoGetX(Ponto p){
    ponto *point = (ponto*)p;
    return point->x;
}

double pontoGetY(Ponto p){
    ponto *point = (ponto*)p;
    return point->y;
}

void pontoSetX(Ponto p, double x){
    ponto *point = (ponto*)p;
    point->x = x;
}

void pontoSetY(Ponto p, double y){
    ponto *point = (ponto*)p;
    point->y = y;
}

Ponto pontoGetPonto(Ponto p){
    return p;
}

char *pontoGetId(Ponto p){
    return "PONTO";
}

void freePonto(Ponto p){
    free(p);
}