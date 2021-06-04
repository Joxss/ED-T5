#include "rua.h"

typedef struct{
    char nome[100];
    char cepLadoDireito[50];
    char cepLadoEsquerdo[50];
    double distancia;
    double velocidadeMedia;
    double tempo;
}rua;

Rua createRua(char nome[], char cepLadoDireito[], char cepLadoEsquerdo[], double distancia, double velocidadeMedia){
    rua *r = malloc(sizeof(rua));
    strcpy(r->nome,nome);
    strcpy(r->cepLadoDireito,cepLadoDireito);
    strcpy(r->cepLadoEsquerdo,cepLadoEsquerdo);
    r->distancia = distancia;
    r->velocidadeMedia = velocidadeMedia;
    r->tempo = distancia/velocidadeMedia;
}

char *ruaGetNome(Rua r){
    rua *street = (rua*)r;
    return street->nome;
}

char *ruaGetCepDireito(Rua r){
    rua *street = (rua*)r;
    return street->cepLadoDireito;
}

char *ruaGetCepEsquerdo(Rua r){
    rua *street = (rua*)r;
    return street->cepLadoEsquerdo;
}

double ruaGetDistancia(Rua r){
    rua *street = (rua*)r;
    return street->distancia;
}

double ruaGetVelocidadeMedia(Rua r){
    rua *street = (rua*)r;
    return street->velocidadeMedia;
}

double ruaGetTempo(Rua r){
    rua *street = (rua*)r;
    return street->tempo;
}

void freeRua(Rua r){
    rua *street = (rua*)r;
    free(street);
}

