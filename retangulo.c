#include "retangulo.h"

typedef struct r{
    char id[50];
    char borda[20];
    char corBorda[20];
    char corPreench[20];
    Ponto coord;
    double w;
    double h;
}retangulo;

Rect createRect(char id[], double x, double y, double w, double h, char borda[], char corBorda[], char corPreench[]){
    retangulo *rect = (retangulo*)malloc(sizeof(retangulo));
    strcpy(rect->id,id);
    strcpy(rect->borda,borda);
    strcpy(rect->corBorda,corBorda);
    strcpy(rect->corPreench,corPreench);
    rect->coord = createPoint(x,y);
    rect->w = w;
    rect->h = h;
    return rect;
}
//GETTERS

char *rectGetId(Rect r){
    retangulo *rect = (retangulo*) r;
    return rect->id;
}

char *rectGetBorda(Rect r){
    retangulo *rect = (retangulo*) r;
    return rect->borda;
}

char *rectGetCorBorda(Rect r){
    retangulo *rect = (retangulo*) r;
    return rect->corBorda;
}

char *rectGetCorPreench(Rect r){
    retangulo *rect = (retangulo*) r;
    return rect->corPreench;
}

Ponto rectGetPonto(Rect r){
    retangulo *rect = (retangulo*) r;
    return rect->coord;
}

double rectGetX(Rect r){
    retangulo *rect = (retangulo*) r;
    return pontoGetX(rect->coord);
}

double rectGetY(Rect r){
    retangulo *rect = (retangulo*) r;
    return pontoGetY(rect->coord);
}

double rectGetW(Rect r){
    retangulo *rect = (retangulo*) r;
    return rect->w;
}

double rectGetH(Rect r){
    retangulo *rect = (retangulo*) r;
    return rect->h;
}

double rectGetXc(Rect r){
    retangulo *rect = (retangulo*) r;
    return (rect->w/2 + pontoGetX(rect->coord));
}

double rectGetYc(Rect r){
    retangulo *rect = (retangulo*) r;
    return (rect->h/2 + pontoGetY(rect->coord));
}

// SETTERS

void rectSetCorBorda(Rect r, char corBorda[]){
    retangulo *rect = (retangulo*) r;
    strcpy(rect->corBorda, corBorda);
}

void rectSetCorPreench(Rect r, char corPreench[]){
    retangulo *rect = (retangulo*) r;
    strcpy(rect->corPreench, corPreench);
}

void freeRect(Rect r){
    retangulo *rect = (retangulo*) r;
    free(rect->coord);
    free(rect);
}
