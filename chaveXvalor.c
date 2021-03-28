#include "chaveXvalor.h"

typedef struct{
    char chave[10];
    char *valor;
}chaveXvalor;

ChaveXValor createChaveValor(char *chave, char *valor){
    chaveXvalor *t = malloc(sizeof(chaveXvalor));

    t->valor = malloc(sizeof(char)*strlen(valor)+1);
    strcpy(t->valor,valor);
    strcpy(t->chave,chave);

    return t;
}

char *chaveXvalorGetChave(ChaveXValor chaveValor){
    chaveXvalor *t = (chaveXvalor *) chaveValor;
    return t->chave;
}

char *chaveXvalorGetValor(ChaveXValor chaveValor){
    chaveXvalor *t = (chaveXvalor *) chaveValor;
    return t->valor;
}

void chaveXvalorSetValor(ChaveXValor chaveValor, char *valor){
    chaveXvalor *t = (chaveXvalor *) chaveValor;
    free(t->valor);
    t->valor = malloc(sizeof(char)*strlen(valor)+1);
    strcpy(t->valor,valor);
}

void freeChaveXvalor(ChaveXValor chaveValor){
    chaveXvalor *t = (chaveXvalor *) chaveValor;
    free(t->valor);
    free(t);
}
