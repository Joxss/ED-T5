#include "rua.h"

typedef struct{
    char nome[100];
    char cepLadoDireito[50];
    Quadra quadraDireita;
    char cepLadoEsquerdo[50];
    Quadra quadraEsquerda;
    double distancia;
    double velocidadeMedia;
    double tempo;
}rua;

Rua createRua(char nome[], Quadra quadraDireita, Quadra quadraEsquerda, double distancia, double velocidadeMedia){
    rua *r = malloc(sizeof(rua));
    strcpy(r->nome,nome);

    r->quadraDireita = quadraDireita;
    r->quadraEsquerda = quadraEsquerda;

    r->distancia = distancia;
    r->velocidadeMedia = velocidadeMedia;
    r->tempo = distancia/velocidadeMedia;

    if(quadraDireita != NULL)
        strcpy(r->cepLadoDireito,quadraGetCep(quadraDireita));
    else
        strcpy(r->cepLadoDireito,"#");
    if(quadraEsquerda != NULL)
        strcpy(r->cepLadoEsquerdo,quadraGetCep(quadraEsquerda));
    else
        strcpy(r->cepLadoEsquerdo,"#");
    
    return r;
}

char *ruaGetNome(Rua r){
    rua *street = (rua*)r;
    return street->nome;
}

Quadra ruaGetQuadraDireita(Rua r){
    rua *street = (rua*)r;
    return street->quadraDireita;
}

Quadra ruaGetQuadraEsquerda(Rua r){
    rua *street = (rua*)r;
    return street->quadraEsquerda;
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

