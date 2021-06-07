#include "chaveXvalor.h"

typedef struct{
    char *chave;
    void *valor;
}chaveXvalor;

ChaveXValor createChaveValor(char *chave, void *valor){
    chaveXvalor *t = malloc(sizeof(chaveXvalor));

    t->chave = malloc(sizeof(char)*strlen(chave)+1);
    strcpy(t->chave,chave);
    t->valor = valor;

    return t;
}

char *chaveXvalorGetChave(ChaveXValor chaveValor){
    chaveXvalor *t = (chaveXvalor *) chaveValor;
    return t->chave;
}

void *chaveXvalorGetValor(ChaveXValor chaveValor){
    chaveXvalor *t = (chaveXvalor *) chaveValor;
    return t->valor;
}

void *chaveXvalorSetValor(ChaveXValor chaveValor, void *valor){
    chaveXvalor *t = (chaveXvalor *) chaveValor;
    void *antigo = t->valor;
    t->valor = valor;
    return antigo;
}

void *freeChaveXvalor(ChaveXValor chaveValor){
    chaveXvalor *t = (chaveXvalor *) chaveValor;
    void *retorno = t->valor;
    free(t->chave);
    free(t);

    return retorno;
}
