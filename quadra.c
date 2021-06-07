#include "quadra.h"
#include "retangulo.h"
typedef struct{
    Rect retangulo;
    List moradores;
    char *corSombra;
}quadra_tad;

Quadra createQuadra(char id[], double x, double y, double w, double h, char borda[], char corBorda[], char corPreench[]){
    quadra_tad *quadra = (quadra_tad*)malloc(sizeof(quadra_tad));
    quadra->retangulo = createRect(id,x,y,w,h,borda,corBorda,corPreench);
    quadra->moradores = createLista();
    quadra->corSombra = NULL;
    return quadra;
}

char *quadraGetCep(Quadra q){
    quadra_tad *quadra = (quadra_tad*) q;
    return rectGetId(quadra->retangulo);
}

char *quadraGetBorda(Quadra q){
    quadra_tad *quadra = (quadra_tad*) q;
    return rectGetBorda(quadra->retangulo);
}

char *quadraGetCorBorda(Quadra q){
    quadra_tad *quadra = (quadra_tad*) q;
    return rectGetCorBorda(quadra->retangulo);
}

char *quadraGetCorPreench(Quadra q){
    quadra_tad *quadra = (quadra_tad*) q;
    return rectGetCorPreench(quadra->retangulo);
}

Ponto quadraGetPonto(Quadra q){
    quadra_tad *quadra = (quadra_tad*) q;
    return rectGetPonto(quadra->retangulo);
}

double quadraGetX(Quadra q){
    quadra_tad *quadra = (quadra_tad*) q;
    return rectGetX(quadra->retangulo);
}

double quadraGetY(Quadra q){
    quadra_tad *quadra = (quadra_tad*) q;
    return rectGetY(quadra->retangulo);
}

double quadraGetW(Quadra q){
    quadra_tad *quadra = (quadra_tad*) q;
    return rectGetW(quadra->retangulo);
}

double quadraGetH(Quadra q){
    quadra_tad *quadra = (quadra_tad*) q;
    return rectGetH(quadra->retangulo);
}

double quadraGetXc(Quadra q){
    quadra_tad *quadra = (quadra_tad*) q;
    return rectGetXc(quadra->retangulo);
}

double quadraGetYc(Quadra q){
    quadra_tad *quadra = (quadra_tad*) q;
    return  rectGetYc(quadra->retangulo);
}

List quadraGetMoradores(Quadra q){
    quadra_tad *quadra = (quadra_tad*) q;
    return quadra->moradores;
}

char *quadraGetCorSombra(Quadra q){
    quadra_tad *quadra = (quadra_tad*) q;
    return quadra->corSombra;
}

Ponto quadraGetEndereco(Quadra q, char face, int num){
    quadra_tad *quadra = (quadra_tad*)q;
    double x, y;
    if(face == 'S'){
        x = rectGetX(quadra->retangulo) + num;
        y = rectGetY(quadra->retangulo);
    }else if(face == 'N'){
        x = rectGetX(quadra->retangulo) + num;
        y = rectGetY(quadra->retangulo) + rectGetH(quadra->retangulo);
    }else if(face == 'L'){
        x = rectGetX(quadra->retangulo);
        y = rectGetY(quadra->retangulo) + num;
    }else if(face == 'O'){
        x = rectGetX(quadra->retangulo); + rectGetW(quadra->retangulo);
        y = rectGetY(quadra->retangulo) + num;
    }

    return createPoint(x,y);
}

// SETTERS
void quadraInserirMorador(Quadra q, Generic morador){
    quadra_tad *quadra = (quadra_tad*) q;
    listInsert(quadra->moradores,morador);
}

void quadraRemoverMorador(Quadra q, char cpf[]){
    quadra_tad *quadra = (quadra_tad*) q;

    Node node = listGetById(quadra->moradores,cpf,genericGetId);
    if(node == NULL) return;
    listRemoveNode(quadra->moradores,node);
}

void quadraSetCorSombra(Quadra q, char corSombra[]){
    quadra_tad *quadra = (quadra_tad*) q;
    quadra->corSombra = malloc(sizeof(char)*strlen(corSombra)+1);
    strcpy(quadra->corSombra,corSombra);
}

void quadraSetCorBorda(Quadra q, char corBorda[]){
    quadra_tad *quadra = (quadra_tad*) q;
    rectSetCorBorda(quadra->retangulo, corBorda);
}

void quadraSetCorPreench(Quadra q, char corPreench[]){
    quadra_tad *quadra = (quadra_tad*) q;
    rectSetCorPreench(quadra->retangulo, corPreench);
}

void freeQuadra(Quadra q){
    quadra_tad *quadra = (quadra_tad*)q;

    freeRect(quadra->retangulo);
    freeLista2(quadra->moradores);
    if(quadra->corSombra != NULL) free(quadra->corSombra);
    
    free(quadra);
}