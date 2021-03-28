#include "estabelecimento.h"

typedef struct{
    char cnpj[17];
    char cpf[15];
    char *descricao;
    char cep[30];
    char face;
    int num;
    char nome[50];
    Ponto coord;
}estabelecimentoTad;

Estabelecimento createEstabelecimento(char *cnpj, char *cpf, char *descricao, Quadra quadra, char face, int num, char *nome){
    estabelecimentoTad *est = malloc(sizeof(estabelecimentoTad));
    strcpy(est->cnpj,cnpj);
    strcpy(est->cpf,cpf);
    est->descricao = malloc(sizeof(char)*strlen(descricao)+1);
    strcpy(est->descricao,descricao);
    strcpy(est->nome,nome);
    est->coord = createPoint(0,0);
    EstSetEndereco(est,quadra,face,num);
    return est;
}

void EstSetEndereco(Estabelecimento e, Quadra quadra, char face, int num){
    estabelecimentoTad *est = (estabelecimentoTad*)e;

    strcpy(est->cep,quadraGetCep(quadra));
    est->face = face;
    est->num = num;

    double xQuadra = quadraGetX(quadra), yQuadra = quadraGetY(quadra), wQuadra = quadraGetW(quadra), hQuadra = quadraGetH(quadra);
    
    switch(face){
        case 'S':
            pontoSetX(est->coord,xQuadra + num);
            pontoSetY(est->coord,yQuadra);
            break;
        case 'N':
            pontoSetX(est->coord,xQuadra + num);
            pontoSetY(est->coord,yQuadra + hQuadra);
            break;
        case 'L':
            pontoSetX(est->coord,xQuadra);
            pontoSetY(est->coord,yQuadra + num);
            break;
        case 'O':
            pontoSetX(est->coord,xQuadra + wQuadra);
            pontoSetY(est->coord,yQuadra + num);
            break;
    }
}

char * estabelecimentoGetCnpj(Estabelecimento e){
    estabelecimentoTad *est = (estabelecimentoTad *) e;
    return est->cnpj;
}

char * estabelecimentoGetCpf(Estabelecimento e){
    estabelecimentoTad *est = (estabelecimentoTad *) e;
    return est->cpf;
}

char * estabelecimentoGetDescricao(Estabelecimento e){
    estabelecimentoTad *est = (estabelecimentoTad *) e;
    return est->descricao;
}

char * estabelecimentoGetCep(Estabelecimento e){
    estabelecimentoTad *est = (estabelecimentoTad *) e;
    return est->cep;
}

char estabelecimentoGetFace(Estabelecimento e){
    estabelecimentoTad *est = (estabelecimentoTad *) e;
    return est->face;
}

int estabelecimentoGetNum(Estabelecimento e){
    estabelecimentoTad *est = (estabelecimentoTad *) e;
    return est->num;

}

char * estabelecimentoGetNome(Estabelecimento e){
    estabelecimentoTad *est = (estabelecimentoTad *) e;
    return est->nome;

}

Ponto estabelecimentoGetCoord(Estabelecimento e){
    estabelecimentoTad *est = (estabelecimentoTad *) e;
    return est->coord;
}

void freeEstabelecimento(Estabelecimento e){
    estabelecimentoTad *est = (estabelecimentoTad *) e;
    free(est->coord);
    free(est->descricao);
    free(est);
}





