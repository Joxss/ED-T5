#include "linha.h"

typedef struct l{
    char borda[20];
    char corBorda[20];
    Ponto ponto1;
    Ponto ponto2;
}linha;

Line createLine(double x1, double y1, double x2, double y2, char borda[], char corBorda[]){
    linha *lin = (linha*)malloc(sizeof(linha));

    strcpy(lin->borda,borda);
    strcpy(lin->corBorda,corBorda);

    lin->ponto1 = createPoint(x1,y1);
    lin->ponto2 = createPoint(x2,y2);

    return lin;
}

//GETTES


char *lineGetBorda(Line l){
    linha *lin = (linha*)l;
    return lin->borda;
}

char *lineGetCorBorda(Line l){
    linha *lin = (linha*)l;
    return lin->corBorda;
}

Ponto lineGetP1(Line l){
    linha *lin = (linha*) l;
    return lin->ponto1;
}

Ponto lineGetP2(Line l){
    linha *lin = (linha*) l;
    return lin->ponto2;
}

double lineGetX1(Line l){
    linha *lin = (linha*) l;
    return pontoGetX(lin->ponto1);
}

double lineGetX2(Line l){
    linha *lin = (linha*) l;
    return pontoGetX(lin->ponto2);
}

double lineGetY1(Line l){
    linha *lin = (linha*) l;
    return pontoGetY(lin->ponto1);
}

double lineGetY2(Line l){
    linha *lin = (linha*) l;
    return pontoGetY(lin->ponto2);
}

void freeLine(Line l){
    linha *lin = (linha*) l;
    free(lin->ponto1);
    free(lin->ponto2);
    free(lin);
}