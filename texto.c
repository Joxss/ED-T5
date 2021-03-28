#include "texto.h"

typedef struct t{
    char id[50];
    char corBorda[20];
    char corPreench[20];
    char txt[200];
    Ponto coord;
}texto;

Text createText(char id[], double x, double y, char corBorda[], char corPreench[], char str[]){
    texto *text = (texto*)malloc(sizeof(texto));

    strcpy(text->id,id);
    strcpy(text->corBorda,corBorda);
    strcpy(text->corPreench,corPreench);
    strcpy(text->txt,str);

    text->coord = createPoint(x,y);

    return text;
}

//GETTERS
char *textGetId(Text t){
    texto *text = (texto*) t;
    return text->id;
}

char *textGetCorBorda(Text t){
    texto *text = (texto*) t;
    return text->corBorda;
}

char *textGetCorPreench(Text t){
    texto *text = (texto*) t;
    return text->corPreench;
}

Ponto textGetPonto(Text t){
    texto *text = (texto*) t;
    return text->coord;
}

double textGetX(Text t){
    texto *text = (texto*) t;
    return pontoGetX(text->coord);
}

double textGetY(Text t){
    texto *text = (texto*) t;
    return pontoGetY(text->coord);
}

char *textGetTxt(Text t){
    texto *text = (texto*) t;
    return text->txt;
}

//SETTERS

void textSetCorBorda(Text t, char borda[]){
    texto *text = (texto*)t;

    strcpy(text->corBorda, borda);
}

void textSetCorPreench(Text t, char preench[]){
    texto *text = (texto*)t;

    strcpy(text->corPreench, preench);
}

void freeText(Text t){
    texto *text = (texto*)t;
    free(text->coord);
    free(text);
}
