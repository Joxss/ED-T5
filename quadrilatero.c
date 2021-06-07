#include "quadrilatero.h"

typedef struct q{
    Ponto coord;
    double w;
    double h;
    double n;
    char face;
}quad;

Quad createQuad(double x, double y, double w, double h, double n){
    quad *q = (quad*)malloc(sizeof(quad));
    q->coord = createPoint(x,y);
    q->w = w;
    q->h = h;
    q->n = n;
    return q;
}

char *QuadGetId(Quad q){
    return "Easter egg";
}

Ponto quadGetPonto(Quad q){
    quad *qua = (quad*)q;
    return qua->coord;
}

double quadGetX(Quad q){
    quad *qua = (quad*)q;
    return pontoGetX(qua->coord);
}

double quadGetY(Quad q){
    quad *qua = (quad*)q;
    return pontoGetY(qua->coord);
}

double quadGetW(Quad q){
    quad *qua = (quad*)q;
    return qua->w;
}

double quadGetH(Quad q){
    quad *qua = (quad*)q;
    return qua->h;
}

double quadGetN(Quad q){
    quad *qua = (quad*)q;
    return qua->n;
}

double quadGetXc(Quad q){
    quad *qua = (quad*)q;
    return (qua->w/2 + pontoGetX(qua->coord));
}

double quadGetYc(Quad q){
    quad *qua = (quad*)q;
    return (qua->h/2 + pontoGetY(qua->coord));
}

char quadGetFace(Quad q){
    quad *qua = (quad*)q;
    return qua->face;
}

void quadSetX(Quad q, double x){
    quad *qua = (quad*)q;
    pontoSetX(qua->coord,x);
}

void quadSetY(Quad q, double y){
    quad *qua = (quad*)q;
    pontoSetY(qua->coord,y);
}

void quadSetW(Quad q, double w){
    quad *qua = (quad*)q;
    qua->w = w;
}

void quadSetH(Quad q, double h){
    quad *qua = (quad*)q;
    qua->h = h;
}

void quadSetN(Quad q, double n){
    quad *qua = (quad*)q;
    qua->n = n;
}

void quadSetFace(Quad q, char face){
    quad *qua = (quad*)q;
    qua->face = face;
}

void freeQuad(Quad q){
    quad *qua = (quad*)q;
    free(qua->coord);
    free(qua);
}

//