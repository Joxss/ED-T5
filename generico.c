#include "generico.h"
#include "quadra.h"
#include "morador.h"

typedef struct g{
    char tipo[20];
    void *valores; // CIRCULO RETANGULO OU TEXTO
    Ponto (*getPonto)(void*);
    void (*freeFunc)(void*);
}generico;

Generic createGeneric(char tipo[], void *valor, void(*func)(void*), Ponto(*getPonto)(void*)){
    generico *elemento = (generico*)malloc(sizeof(generico));
    
    strcpy(elemento->tipo,tipo);
    elemento->valores = valor;
    elemento->freeFunc = func;
    elemento->getPonto = getPonto;
    return elemento;
}

Ponto genericGetPonto(Generic g){
    generico *elemento = (generico*) g;
    return elemento->getPonto(elemento->valores);
}

char* genericGetTipo(Generic g){
    generico *elemento = (generico*) g;
    return elemento->tipo; 
}

void *genericGetValores(Generic g){
    generico *elemento = (generico*) g;
    return elemento->valores;
}

void freeGeneric(Generic g){
    generico *elemento = (generico*) g;

    elemento->freeFunc(elemento->valores);
    
    free(elemento);
}

char *genericGetId(Generic g){
    generico *elemento = (generico*) g;
    
    if(!strcmp(elemento->tipo, "circulo")) return circGetId(elemento->valores);
    else if(!strcmp(elemento->tipo,"retangulo")) return rectGetId(elemento->valores);
    else if(!strcmp(elemento->tipo,"quadra")) return quadraGetCep(elemento->valores);
    else if(!strcmp(elemento->tipo, "texto")) return textGetId(elemento->valores);
    else if(!strcmp(elemento->tipo, "chaveXvalor")) return chaveXvalorGetChave(elemento->valores);
    else if(!strcmp(elemento->tipo, "pessoa")) return pessoaGetCpf(elemento->valores);
    else if(!strcmp(elemento->tipo, "morador")) return moradorGetCpf(elemento->valores);
}


void genericSetCores(Generic g, char corBorda[], char corPreench[]){
    generico *elemento = (generico*) g;

    if(!strcmp(elemento->tipo, "circulo")){
        circSetCorBorda(elemento->valores, corBorda);
        circSetCorPreench(elemento->valores, corPreench);

    }else if(!strcmp(elemento->tipo, "retangulo")){
        rectSetCorBorda(elemento->valores, corBorda);
        rectSetCorPreench(elemento->valores, corPreench);

    }else if(!strcmp(elemento->tipo, "texto")){
        textSetCorBorda(elemento->valores, corBorda);
        textSetCorPreench(elemento->valores, corPreench);
        
    }
}

void genericSetTipo(Generic g, char tipo[]){
    generico *elemento = (generico*) g;
    strcpy(elemento->tipo,tipo);
}