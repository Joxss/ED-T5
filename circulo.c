#include "circulo.h"

typedef struct c{
    char id[50];
    char borda[20];
    char corBorda[20];
    char corPreench[20];
    Ponto coord;
    double r;
}circulo;

Circ createCircle(char id[], double x, double y, double r, char borda[], char corBorda[], char corPreench[]){
    circulo *circ = (circulo*)malloc(sizeof(circulo));
    strcpy(circ->id,id);
    strcpy(circ->borda,borda);
    strcpy(circ->corBorda,corBorda);
    strcpy(circ->corPreench,corPreench);
    circ->coord = createPoint(x,y);
    circ->r = r;
    return circ;
}

//GETTERS

char *circGetId(Circ c){
    circulo *circ = (circulo*) c;
    return circ->id;
}

char *circGetBorda(Circ c){
    circulo *circ = (circulo*) c;
    return circ->borda;
}

char *circGetCorBorda(Circ c){
    circulo *circ = (circulo*) c;
    return circ->corBorda;
}

char *circGetCorPreench(Circ c){
    circulo *circ = (circulo*) c;
    return circ->corPreench;
}

Ponto circGetPonto(Circ c){
    circulo *circ = (circulo*) c;
    return circ->coord;
}

double circGetX(Circ c){
    circulo *circ = (circulo*) c;
    return pontoGetX(circ->coord);
}

double circGetY(Circ c){
    circulo *circ = (circulo*) c;
    return pontoGetY(circ->coord);
}

double circGetR(Circ c){
    circulo *circ = (circulo*) c;
    return circ->r;
}

//SETTERS

void circSetCorBorda(Circ c, char corBorda[]){
    circulo *circ = (circulo*)c;

    strcpy(circ->corBorda, corBorda);
}

void circSetCorPreench(Circ c, char corPreench[]){
    circulo *circ = (circulo*)c;

    strcpy(circ->corPreench, corPreench);
}

void freeCircle(Circ c){
    circulo *circ = (circulo*)c;
    free(circ->coord);
    free(circ);
}