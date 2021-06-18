#include "calculos.h"
#include "generico.h"
#include "morador.h"
#include <math.h>
#include "estabelecimento.h"

double Min(double a, double b){ // RETORNA O MENOR NUMERO ENTRE DOIS NUMEROS
    if(a>=b) return b;
    else return a;
}

double Max(double a, double b){ // RETORNA O MAIOR NUMERO ENTRE DOIS NUMEROS
    if(a>b) return a;
    else return b;
}

int getQtdAlgarismos(int n){
    int qtd = 0;
    while(n != 0 ){
        n /= 10;
        qtd++;
    }
    return qtd;
}

int checaInterno(Generic elemento, double xPonto, double yPonto){ //CHECA SE UM PONTO É INTERNO A UM OBJETO DO ARQUIVO .GEO
    double xPolig, yPolig, n1, n2;
    char *tipo = genericGetTipo(elemento);

    if(!strcmp(tipo,"circulo") || !strcmp(tipo,"anel")){
        Circ circ = genericGetValores(elemento);
        double r = circGetR(circ);
        xPolig = circGetX(circ);
        yPolig = circGetY(circ);
        n1 = (xPonto-xPolig)*(xPonto-xPolig);
        n2 = (yPonto-yPolig)*(yPonto-yPolig);
        if(n1 + n2 <= r * r) return 1;
    }
    else if(!strcmp(tipo,"retangulo")){
        Rect rect = genericGetValores(elemento);
        double w = rectGetW(rect);
        double h = rectGetH(rect);
        xPolig = rectGetX(rect);
        yPolig = rectGetY(rect);
        n1 = xPolig+w;
        n2 = yPolig+h;
        if(xPonto>=xPolig && xPonto<=n1 && yPonto>=yPolig && yPonto<=n2) return 1; 
    }
    
    return 0;
}

int checkInsideCirc(Generic elemento, double xCirc, double yCirc, double rCirc){ // NÃO FUNCIONA PARA OS ELEMENTOS DO TIPO TEXTO E DENSIDADE
    char *tipo = genericGetTipo(elemento);
    if(!strcmp(tipo,"retangulo")){
        Rect quadra = genericGetValores(elemento);
        double dx = Max(xCirc - rectGetX(quadra), (rectGetX(quadra) + rectGetW(quadra)) - xCirc);
        double dy = Max(yCirc - rectGetY(quadra), (rectGetY(quadra) + rectGetH(quadra)) - yCirc);

        return rCirc * rCirc >= (dx*dx + dy*dy);
    }else if(!strcmp(tipo,"quadra")){
        Quadra quadra = genericGetValores(elemento);
        double dx = Max(xCirc - quadraGetX(quadra), (quadraGetX(quadra) + quadraGetW(quadra)) - xCirc);
        double dy = Max(yCirc - quadraGetY(quadra), (quadraGetY(quadra) + quadraGetH(quadra)) - yCirc);

        return rCirc * rCirc >= (dx*dx + dy*dy);
    }else if(!strcmp(tipo,"circulo")){
        Circ circ = genericGetValores(elemento);
        double x = circGetX(circ);
        double y = circGetY(circ);
        double r = circGetR(circ);
        double dist = (x-xCirc) * (x-xCirc) + (y-yCirc) * (y-yCirc);
        dist = sqrt(dist);
        return ((dist + r) <= rCirc);
    }else if(!strcmp(tipo,"ponto")){
        Ponto p = genericGetValores(elemento);
        double x = pontoGetX(p);
        double y = pontoGetY(p);
        double n1 = (x-xCirc)*(x-xCirc);
        double n2 = (y-yCirc)*(y-yCirc);
        return (n1+n2 <= rCirc*rCirc);
    }else if(!strcmp(tipo,"cv")){
        Quad cv = genericGetValores(elemento);
        double x;
        double y;
        if(quadGetFace(cv)=='N'){
            x = quadGetXc(cv);
            y = quadGetY(cv)+quadGetH(cv);
        }else if(quadGetFace(cv)=='S'){
            x = quadGetXc(cv);
            y = quadGetY(cv);
        }else if(quadGetFace(cv)=='L'){
            x = quadGetX(cv);
            y = quadGetYc(cv);
        }else if(quadGetFace(cv)=='O'){
            x = quadGetX(cv) + quadGetW(cv);
            y = quadGetYc(cv);
        }

        double n1 = (x-xCirc)*(x-xCirc);
        double n2 = (y-yCirc)*(y-yCirc);
        // if((n1+n2 <= rCirc*rCirc)){
        //     //printf("%lf\n",quadGetN(cv));
        // }
        return (n1+n2 <= rCirc*rCirc);
    }else if(!strcmp(tipo,"morador")){
        Morador morador = genericGetValores(elemento);
        Ponto p = moradorGetPonto(morador);
        double x = pontoGetX(p);
        double y = pontoGetY(p);
        double n1 = (x-xCirc)*(x-xCirc);
        double n2 = (y-yCirc)*(y-yCirc);
        return (n1+n2 <= rCirc*rCirc);
    }else if(!strcmp(tipo,"ec")){
        Estabelecimento esta = genericGetValores(elemento);
        Ponto p = estabelecimentoGetCoord(esta);
        double x = pontoGetX(p);
        double y = pontoGetY(p);
        double n1 = (x-xCirc)*(x-xCirc);
        double n2 = (y-yCirc)*(y-yCirc);
        return (n1+n2 <= rCirc*rCirc);
    }
    else if(!strcmp(tipo,"vertice")){
        Ponto p = genericGetPonto(elemento);
        double x = pontoGetX(p);
        double y = pontoGetY(p);
        double n1 = (x-xCirc)*(x-xCirc);
        double n2 = (y-yCirc)*(y-yCirc);
        return (n1+n2 <= rCirc*rCirc);
    }

    return 0;
}

int checkRectInsideRect(Generic elemento, double x, double y, double w, double h){ // NÃO FUNCIONA PARA ELEMENTO DO TIPO TEXTO DENSIDADE E CIRCULO
    char *tipo = genericGetTipo(elemento);
    if(!strcmp(tipo,"retangulo")){
        Rect quadra = genericGetValores(elemento);
        double xO = rectGetX(quadra), yO = rectGetY(quadra);
        double xF = rectGetX(quadra) + rectGetW(quadra), yF = rectGetY(quadra) + rectGetH(quadra);

        return (xO >= x && yO >= y && xF <= x+w  && yF <= y+h);
    }else if(!strcmp(tipo,"quadra")){
        Quadra quadra = genericGetValores(elemento);
        
        double xO = quadraGetX(quadra), yO = quadraGetY(quadra);
        double xF = quadraGetX(quadra) + quadraGetW(quadra), yF = quadraGetY(quadra) + quadraGetH(quadra);

        return (xO >= x && yO >= y && xF <= x+w  && yF <= y+h);
    }else if(!strcmp(tipo,"ponto")){
        Ponto p = genericGetValores(elemento);
        double xP = pontoGetX(p);
        double yP = pontoGetY(p);
        return (xP >= x && xP <= x+w && yP >= y && yP <= y+h);
    }else if(!strcmp(tipo,"cv")){
        Quad cv = genericGetValores(elemento);
        double xP = quadGetXc(cv);
        double yP = quadGetYc(cv);
        return (xP >= x && xP <= x+w && yP >= y && yP <= y+h);
    }else if(!strcmp(tipo,"ec")){
        Estabelecimento ec = genericGetValores(elemento);
        Ponto p = estabelecimentoGetCoord(ec);
        double xP = pontoGetX(p);
        double yP = pontoGetY(p);
        return (xP >= x && xP <= x+w && yP >= y && yP <= y+h);
    }
    return 0; 
}

void calculaValoresRect(double *x, double *y, double *w, double *h, Generic fig1, Generic fig2){
    double fig1_startX, fig2_startX, rectT_startX; 
    double fig1_startY, fig2_startY, rectT_startY; 
    double fig1_endX, fig2_endX, rectT_endX; 
    double fig1_endY, fig2_endY, rectT_endY;
    char *tipo1 = genericGetTipo(fig1), *tipo2 = genericGetTipo(fig2);

    if(!strcmp(tipo1,"circulo")){ // FIGURA 1
        Circ circ = genericGetValores(fig1);
        fig1_startX = circGetX(circ) - circGetR(circ);
        fig1_startY = circGetY(circ) - circGetR(circ);
        fig1_endX = circGetX(circ) + circGetR(circ);
        fig1_endY = circGetY(circ) + circGetR(circ);
    }else{
        Rect rect = genericGetValores(fig1);
        fig1_startX = rectGetX(rect);
        fig1_startY = rectGetY(rect);
        fig1_endX = rectGetX(rect) + rectGetW(rect);
        fig1_endY = rectGetY(rect) + rectGetH(rect);
    }
    
    if(!strcmp(tipo2,"circulo")){ // FIGURA 2
        Circ circ = genericGetValores(fig2);
        fig2_startX = circGetX(circ) - circGetR(circ);
        fig2_startY = circGetY(circ) - circGetR(circ);
        fig2_endX = circGetX(circ) + circGetR(circ);
        fig2_endY = circGetY(circ) + circGetR(circ);
    }else{
        Rect rect = genericGetValores(fig2);
        fig2_startX = rectGetX(rect);
        fig2_startY = rectGetY(rect);
        fig2_endX = rectGetX(rect) + rectGetW(rect);
        fig2_endY = rectGetY(rect) + rectGetH(rect);
    }

    rectT_startX = Min(fig1_startX,fig2_startX);
    rectT_startY = Min(fig1_startY,fig2_startY);
    rectT_endX = Max(fig1_endX,fig2_endX);
    rectT_endY = Max(fig1_endY,fig2_endY);

    *x = rectT_startX;
    *y = rectT_startY;
    *w = rectT_endX - rectT_startX;
    *h = rectT_endY - rectT_startY;

    return;
}

int CircRect(Circ circ, Rect rect){ // CHECA SE HÁ SOBREPOSIÇÃO ENTRE DOIS OBEJTO DO TIPO CIRCULO E RETANGULO
    double deltaX, deltaY;

    deltaX = circGetX(circ) - Max(rectGetX(rect), Min(circGetX(circ), rectGetX(rect) + rectGetW(rect)));
    deltaY = circGetY(circ) - Max(rectGetY(rect), Min(circGetY(circ), rectGetY(rect) + rectGetH(rect)));

    if((deltaX * deltaX + deltaY * deltaY) <= (circGetR(circ) * circGetR(circ))){
        return 1;
    }
    else{
       return 0;
    }
}

int RectRect(Rect rect1, Rect rect2){ // CHECA SE HÁ SOBREPOSIÇÃO ENTRE DOIS OBEJTO DO TIPO RETANGULO
    double rect1X = rectGetX(rect1);
    double rect1Y = rectGetY(rect1);
    double rect1W = rectGetW(rect1);
    double rect1H = rectGetH(rect1);
    
    double rect2X = rectGetX(rect2);
    double rect2Y = rectGetY(rect2);
    double rect2W = rectGetW(rect2);
    double rect2H = rectGetH(rect2);

    if(!((rect1X + rect1W) < rect2X || (rect1Y + rect1H) < rect2Y || rect1X > (rect2X + rect2W) || rect1Y > (rect2Y + rect2H))){
        return 1;
    }
    else{
        return 0;
    }
}
 
int CircCirc(Circ circ1, Circ circ2){ // CHECA SE HÁ SOBREPOSIÇÃO ENTRE DOIS OBEJTO DO TIPO CIRCULO
    double deltaX = circGetX(circ2) - circGetX(circ1);
    double deltaY = circGetY(circ2) - circGetY(circ1);
    double raio = circGetR(circ1) + circGetR(circ2);//circ1->raio + circ2->raio;
    
    if(deltaX*deltaX + deltaY*deltaY <= raio*raio){
        return 1;
    }
    else{
        return 0;
    }

}

int checaColisao(Generic polig1, Generic polig2){ // CHECA QUAL SÃO OS TIPOS DOS DOIS OBJETOS SELECIONADOS
    
    char *tipo1 = genericGetTipo(polig1);
    char *tipo2 = genericGetTipo(polig2);
    int boolean;
    
    if(!strcmp(tipo1,"circulo") && !strcmp(tipo2,"circulo")){
        Circ circ1 = genericGetValores(polig1);
        Circ circ2 = genericGetValores(polig2);
        boolean = CircCirc(circ1,circ2);
    }
    else if(!strcmp(tipo1,"retangulo") && !strcmp(tipo2,"retangulo")){
        Rect rect1 = genericGetValores(polig1);
        Rect rect2 = genericGetValores(polig2);
        boolean = RectRect(rect1,rect2);
    }
    else{
        if(!strcmp(tipo1,"circulo")){
            Circ circ = genericGetValores(polig1);
            Rect rect = genericGetValores(polig2);
            boolean = CircRect(circ,rect);
        }
        else{
            Rect rect = genericGetValores(polig1);
            Circ circ = genericGetValores(polig2);
            boolean = CircRect(circ,rect);
        }
    }
    return boolean;
}

void setCv(double *x, double *y, double *w, double *h, int n, Quadra quadra, char face, double num){
    double xQuadra = quadraGetX(quadra), yQuadra = quadraGetY(quadra), wQuadra = quadraGetW(quadra), hQuadra = quadraGetH(quadra);
    int qtdAlgarismos = getQtdAlgarismos(n);

    //calculo de ajuste de algarismo dentro do retangulo
    double l = 8 + 6*(qtdAlgarismos-1);
    *w = l;
    *h = l;
    switch(face){
        case 'S':
            *x = xQuadra + num - l/2;
            *y = yQuadra;
            break;
        case 'N':
            *x = xQuadra + num - l/2;
            *y = yQuadra + hQuadra - l;
            break;
        case 'L':
            *x = xQuadra;
            *y = yQuadra + num - l/2;
            break;
        case 'O':
            *x = xQuadra + wQuadra - l;
            *y = yQuadra + num - l/2;
            break;
    }
}

int checkPoligInsideRect(Poligono polig, Quad rect){
    double *xizes = poligGetArrayX(polig);
    double *ypsilons = poligGetArrayY(polig);

    double xMin = xizes[0], xMax = xizes[0], yMin = ypsilons[0], yMax = ypsilons[0];
    int qtd = poligGetQtd(polig);

    for(int i=0; i<qtd; i++){
        //printf("x %lf y %lf\n",xizes[i],ypsilons[i]);
        if(xizes[i] > xMax) xMax = xizes[i];
        if(xizes[i] < xMin) xMin = xizes[i];
        if(ypsilons[i] > yMax) yMax = ypsilons[i];
        if(ypsilons[i] < yMax) yMin = ypsilons[i];
    }
    //printf(".....................\n");
    double xRect = quadGetX(rect);
    double yRect = quadGetY(rect);
    double wRect = quadGetW(rect);
    double hRect = quadGetH(rect);
    //printf("xrect %lf yrect %lf wrect %lf hrect %lf\n",xRect,yRect,wRect,hRect);
    //printf("xMin %lf yMin %lf xMax %lf yMax %lf\n",xMin,yMin,xMax,yMax);
    return (xMin >= xRect && xMax <= xRect+wRect && yMin >= yRect && yMax <= yRect+hRect);
}



//