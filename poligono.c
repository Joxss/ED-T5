#include "poligono.h"

typedef struct pol{
    int qtd;
    double *x;
    double *y;
    char cor[20];
    double area;
    double xC;
    double yC;
}poligono;

double * poligGetArrayX(Poligono p){
    poligono *poli = (poligono*)p;
    return poli->x;
}

double * poligGetArrayY(Poligono p){
    poligono *poli = (poligono*)p;
    return poli->y;
}

double poligGetXc(Poligono p){
    poligono *poli = (poligono*)p;
    return poli->xC;
}

double poligGetYc(Poligono p){
    poligono *poli = (poligono*)p;
    return poli->yC;
}

double poligGetArea(Poligono p){
    poligono *poli = (poligono*)p;
    return poli->area; 
}

int poligGetQtd(Poligono p){
    poligono *poli = (poligono*)p;
    return poli->qtd;
}

char * poligGetCor(Poligono p){
    poligono *poli = (poligono*)p;
    return poli->cor;
}

void poligSetCor(Poligono p, char *preench){
    poligono *poli = (poligono*)p;
    strcpy(poli->cor,preench);
}

//FUNÇÕES DE CONTROLE

void _poligSetArea(Poligono p){
    poligono *poli = (poligono*)p;
    
    double *x = poli->x, *y = poli->y;
    int n = poli->qtd;

    poli->area = 0;

    for(int i = 0; i < n; i++){

        if(i == (n - 1)){
            poli->area += x[i] * y[0] - y[i] * x[0]; 
        }else{
            poli->area += x[i] * y[i+1] - y[i] * x[i+1];
        }
    }
    
    poli->area /= 2;

}

void _poligSetCentroide(Poligono p){
    poligono *poli = (poligono*)p;

    double area = poligGetArea(p);
    int n = poli->qtd;
    double *x = poli->x, *y = poli->y;

    poli->xC = 0, poli->yC = 0;
    
    for(int i = 0; i < n; i++){

        if(i == (n - 1)){
            poli->xC += (x[i] * y[0] - y[i] * x[0]) * (x[i] + x[0]);
            poli->yC += (x[i] * y[0] - y[i] * x[0]) * (y[i] + y[0]);
        }else{

            poli->xC += (x[i] * y[i+1] - y[i] * x[i+1]) * (x[i] + x[i+1]);      
            poli->yC += (x[i] * y[i+1] - y[i] * x[i+1]) * (y[i] + y[i+1]);
        }
    }

    //set
    poli->xC /= (6*area);
    poli->yC /= (6*area);
}

void freePolig(Poligono p){
    poligono *poli = (poligono*)p;
    free(poli->x);
    free(poli->y);
    free(poli);
}

Poligono createPoligono(int qtd, double *x, double *y){
    poligono *p = (poligono*)malloc(sizeof(poligono));
    p->qtd = qtd;
    p->x = x;
    p->y = y;
    _poligSetArea(p);
    _poligSetCentroide(p);

    return p;
}

//