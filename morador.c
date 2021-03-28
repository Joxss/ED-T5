#include "morador.h"

typedef struct{
    char cpf[15];
    char cep[30];
    Ponto coord;
    char face;
    int num;
    char compl[30];
} moradorTad;

Morador createMorador(char * cpf, Quadra quadra, char face, int num, char *compl){
    moradorTad *morador = malloc(sizeof(moradorTad));
    strcpy(morador->cpf,cpf);
    morador->coord = createPoint(0,0);
    moradorSetEndereco(morador, quadra, face, num, compl);

    return morador;
}

void moradorSetEndereco(Morador m, Quadra quadra, char face, int num, char *compl){
    moradorTad *morador = (moradorTad*)m;

    strcpy(morador->cep,quadraGetCep(quadra));
    strcpy(morador->compl,compl);
    morador->face = face;
    morador->num = num;

    double xQuadra = quadraGetX(quadra), yQuadra = quadraGetY(quadra), wQuadra = quadraGetW(quadra), hQuadra = quadraGetH(quadra);
    
    switch(face){
        case 'S':
            pontoSetX(morador->coord,xQuadra + num);
            pontoSetY(morador->coord,yQuadra);
            break;
        case 'N':
            pontoSetX(morador->coord,xQuadra + num);
            pontoSetY(morador->coord,yQuadra + hQuadra);
            break;
        case 'L':
            pontoSetX(morador->coord,xQuadra);
            pontoSetY(morador->coord,yQuadra + num);
            break;
        case 'O':
            pontoSetX(morador->coord,xQuadra + wQuadra);
            pontoSetY(morador->coord,yQuadra + num);
            break;
    }
}

Ponto moradorGetPonto(Morador m){
    moradorTad *morador = (moradorTad*)m;

    return morador->coord;
}

char * moradorGetCep(Morador m){
    moradorTad *morador = (moradorTad*)m;
    return morador->cep;
}

char * moradorGetCpf(Morador m){
    moradorTad *morador = (moradorTad*)m;
    return morador->cpf;
}

char moradorGetFace(Morador m){
    moradorTad *morador = (moradorTad*)m;
    return morador->face;
}

int moradorGetNum(Morador m){
    moradorTad *morador = (moradorTad*)m;
    return morador->num;
}

char * moradorGetCompl(Morador m){
    moradorTad *morador = (moradorTad*)m;
    return morador->compl;
}

void freeMorador(Morador m){
   moradorTad *morador = (moradorTad*)m;
   free(morador->coord);
   free(morador); 
}