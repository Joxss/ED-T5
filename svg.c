#include "svg.h"
#include "estabelecimento.h"

double _maior(double n1, double n2){
    return n1>n2 ? n1 : n2;
}

double _menor(double n1, double n2){
    return n1<n2 ? n1 : n2;
}

void _svgPrintFilter(FILE *svg, char *shadowColor, char *filterId){
    fprintf(svg, "<filter id=\"%s\">\n",filterId);
    fprintf(svg, "<feOffset dx=\"5\" dy=\"5\" result=\"offsetblur\"/>\n");
    fprintf(svg, "<feFlood flood-color=\"%s\"/>\n", shadowColor);
    fprintf(svg, "<feComposite in2=\"offsetblur\" operator=\"in\"/>\n");
    fprintf(svg, "<feMerge>\n");
    fprintf(svg, "<feMergeNode/>\n");
    fprintf(svg, "<feMergeNode in=\"SourceGraphic\"/>\n");
    fprintf(svg," </feMerge>\n");
    fprintf(svg, "</filter>\n");
}

void svgOpenTag(char path[]){
    FILE *svg = fopen(path,"w");
    fprintf(svg,"<svg>\n");
    fprintf(svg,"<defs>\n");
    _svgPrintFilter(svg,"#FFFF00","shadow1");
    _svgPrintFilter(svg,"#FF9955","shadow2");
    _svgPrintFilter(svg,"#FF0000","shadow3");
    _svgPrintFilter(svg,"#FF00CC","shadow4");
    _svgPrintFilter(svg,"#6600ff","shadow5");
    _svgPrintFilter(svg,"#A02C5A","shadow6");
    fprintf(svg,"</defs>\n");
    fclose(svg);
}

void svgCloseTag(char path[]){
    FILE *svg = fopen(path,"a");
    fprintf(svg,"</svg>");
    fclose(svg);
}

void svgPrintCircle(FILE *svg, Circ circ){
    double x = circGetX(circ);
    double y = circGetY(circ);
    double r = circGetR(circ);

    char borda[20], corBorda[20], corPreench[20];

    strcpy(borda,circGetBorda(circ));
    strcpy(corBorda,circGetCorBorda(circ));
    strcpy(corPreench,circGetCorPreench(circ));

    fprintf(svg,"<circle id=\"%s\" r=\"%lf\" cx=\"%lf\" cy=\"%lf\" stroke-width=\"%s\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.7\"/>\n",circGetId(circ),r,x,y,borda,corBorda,corPreench);
}

void svgPrintRing(FILE *svg, Circ ring, int boolean){
    double x = circGetX(ring);
    double y = circGetY(ring);
    double r = circGetR(ring);

    char borda[20], corBorda[20];

    strcpy(borda,circGetBorda(ring));
    strcpy(corBorda,circGetCorBorda(ring));

    if(boolean) fprintf(svg,"<circle id=\"%s\" r=\"%lf\" cx=\"%lf\" cy=\"%lf\" stroke-width=\"%s\" stroke=\"%s\" fill=\"white\" fill-opacity=\"0\"/>\n",circGetId(ring),r,x,y,borda,corBorda);
    else{
        char corPreench[20];
        strcpy(corPreench,circGetCorPreench(ring));
        fprintf(svg,"<circle id=\"%s\" r=\"%lf\" cx=\"%lf\" cy=\"%lf\" stroke-width=\"%s\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.5\"/>\n",circGetId(ring),r,x,y,borda,corBorda,corPreench);
    }
}

void svgPrintRect(FILE *svg, Rect rect){
    double x = rectGetX(rect);
    double y = rectGetY(rect);
    double w = rectGetW(rect);
    double h = rectGetH(rect);

    char borda[20], corBorda[20], corPreench[20];

    strcpy(borda,rectGetBorda(rect));
    strcpy(corBorda,rectGetCorBorda(rect));
    strcpy(corPreench,rectGetCorPreench(rect));

    fprintf(svg,"<rect id=\"%s\" width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke-width=\"%s\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"0.7\"/>\n",rectGetId(rect),w,h,x,y,borda,corBorda,corPreench);   
}

void svgPrintRectTrac(FILE *svg, Rect rect, int boolean){
    double x = rectGetX(rect);
    double y = rectGetY(rect);
    double w = rectGetW(rect);
    double h = rectGetH(rect);
    if(boolean){
        fprintf(svg,"<rect id=\"%s\" width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke-width=\"1\" stroke=\"black\" fill=\"white\" stroke-dasharray=\"5\" fill-opacity=\"0\"/>\n",rectGetId(rect),w,h,x,y);   
    }else{
        fprintf(svg,"<rect id=\"%s\" width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke-width=\"1\" stroke=\"black\" fill=\"white\" fill-opacity=\"0\"/>\n",rectGetId(rect),w,h,x,y);
    }
}

void svgPrintQuadra(FILE *svg, Quadra quadra, int rounded){
    double x = quadraGetX(quadra);
    double y = quadraGetY(quadra);
    double w = quadraGetW(quadra);
    double h = quadraGetH(quadra);
    double xC = quadraGetXc(quadra);
    double yC = quadraGetYc(quadra);

    char borda[20];
    strcpy(borda,quadraGetBorda(quadra));

    if(!rounded){
        char corBorda[20], corPreench[20];
        strcpy(corBorda,quadraGetCorBorda(quadra));
        strcpy(corPreench,quadraGetCorPreench(quadra));
        if(quadraGetCorSombra(quadra) == NULL){
            fprintf(svg,"<rect id=\"%s\" width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke-width=\"%s\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"1\"/>\n",quadraGetCep(quadra),w,h,x,y,borda,corBorda,corPreench);   
        }else{
            fprintf(svg,"<rect id=\"%s\" width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke-width=\"%s\" stroke=\"%s\" fill=\"%s\" fill-opacity=\"1\" filter=\"url(#%s)\"/>\n",quadraGetCep(quadra),w,h,x,y,borda,corBorda,corPreench,quadraGetCorSombra(quadra));
        }
    }else{
        double rx = 10;
        fprintf(svg,"<rect id=\"%s\" width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke-width=\"%s\" stroke=\"olive\" fill=\"beige\" rx=\"%lf\" fill-opacity=\"0.7\"/>\n",quadraGetCep(quadra),w,h,x,y,borda,rx);
    } 

}

void svgPrintLine(FILE *svg, Line line, int tracejado){
    double x1 = lineGetX1(line);
    double y1 = lineGetY1(line);
    double x2 = lineGetX2(line);
    double y2 = lineGetY2(line);
    char cor[20];

    strcpy(cor,lineGetCorBorda(line));
    if(tracejado){
        fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\" stroke-dasharray=\"5,5\"/>\n",x1,y1,x2,y2,cor);
    }else{
        fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\"/>\n",x1,y1,x2,y2,cor);
    }
}

void svgPrintText(FILE *svg, Text text, int boolean){
    double x = textGetX(text);
    double y = textGetY(text);

    char txt[200], corBorda[20], corPreench[20];

    strcpy(txt,textGetTxt(text));
    strcpy(corBorda,textGetCorBorda(text));
    strcpy(corPreench,textGetCorPreench(text));
    if(boolean){
        fprintf(svg,"<text id=\"%s\" x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill=\"%s\" font-size=\"8\">%s</text>\n",textGetId(text),x,y,corBorda,corPreench,txt);
    }else{
        fprintf(svg,"<text id=\"%s\" x=\"%lf\" y=\"%lf\" stroke=\"%s\" fill=\"%s\" text-anchor=\"middle\" font-size=\"8\">%s</text>\n",textGetId(text),x,y,corBorda,corPreench,txt);
    }
}

void svgPrintPonto(FILE *svg, Ponto p, double raio, char cor[]){
    double x = pontoGetX(p);
    double y = pontoGetY(p);
    fprintf(svg,"<circle id=\"posto-saude\" r=\"%lf\" cx=\"%lf\" cy=\"%lf\" fill=\"%s\" fill-opacity=\"1\"/>\n",raio,x,y,cor);
}

void svgPrintCv(FILE *svg, Quad q){
    int n = quadGetN(q);
    int qtdAlgarismos = getQtdAlgarismos(n);
    double xTexto, yTexto;

    xTexto = quadGetX(q) + quadGetH(q)/2;
    yTexto = quadGetY(q) + 7 + 3*(qtdAlgarismos-1);

    fprintf(svg,"<rect id=\"quadrado-cv\" width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" fill=\"orange\" fill-opacity=\"0.7\"/>\n",quadGetW(q),quadGetH(q),quadGetX(q),quadGetY(q));
    fprintf(svg,"<text id=\"casos-%d\" x=\"%lf\" y=\"%lf\" stroke=\"white\" fill=\"white\" text-anchor=\"middle\" font-size=\"8\">%d</text>\n",n,xTexto,yTexto,n);
}

void svgPrintSoc(FILE *svg, Quad q){
    fprintf(svg,"<rect id=\"quadrado-soc\" width=\"%lf\" height=\"%lf\" x=\"%lf\" y=\"%lf\" stroke-width=\"1px\" stroke=\"white\" fill=\"blue\" fill-opacity=\"0.7\"/>\n",quadGetW(q),quadGetH(q),quadGetX(q),quadGetY(q));
}

void svgPrintPoligono(FILE *svg, Poligono p){
    
    double *x = poligGetArrayX(p), *y = poligGetArrayY(p);
    int len = poligGetQtd(p); 
    
    fprintf(svg,"<polygon points=\"");

    for(int i=0;i<len;i++){
        if(i!=len-1)
            fprintf(svg,"%lf,%lf ",x[i],y[i]);
        else
            fprintf(svg,"%lf,%lf\" ",x[i],y[i]);

    }

    fprintf(svg,"fill=\"%s\" stroke=\"red\" stroke-width=\"3\" fill-opacity=\"0.5\"/>\n",poligGetCor(p));
}

void svgPrintEc(FILE *svg, Estabelecimento est){
    Ponto p = estabelecimentoGetCoord(est);
    double x = pontoGetX(p);
    double y = pontoGetY(p);
    fprintf(svg,"<circle r=\"4\" cx=\"%lf\" cy=\"%lf\" stroke-width=\"1\" stroke=\"yellow\" fill=\"black\" fill-opacity=\"0.7\"/>\n",x,y);
}

void svgSelectTag(Generic elemento, void *file){
    FILE *svg = (FILE*)file;
    char *tipo = genericGetTipo(elemento);
    if(!strcmp(tipo,"circulo")){
        svgPrintCircle(svg, genericGetValores(elemento));
    }else if(!strcmp(tipo,"anel")){
        svgPrintRing(svg,genericGetValores(elemento),1);
    }else if(!strcmp(tipo,"anel2")){
        svgPrintRing(svg,genericGetValores(elemento),0);
    }else if(!strcmp(tipo,"retangulo")){
        svgPrintRect(svg, genericGetValores(elemento));
    }else if(!strcmp(tipo,"texto")){
        svgPrintText(svg, genericGetValores(elemento),1);
    }else if(!strcmp(tipo,"txtcenter")){
        svgPrintText(svg, genericGetValores(elemento),0);
    }else if(!strcmp(tipo,"rtrac")){
        svgPrintRectTrac(svg,genericGetValores(elemento),1);
    }else if(!strcmp(tipo,"rntrac")){
        svgPrintRectTrac(svg,genericGetValores(elemento),0);
    }else if(!strcmp(tipo,"linha")){
        svgPrintLine(svg,genericGetValores(elemento), 0);
    }else if(!strcmp(tipo,"quadra")){
        svgPrintQuadra(svg,genericGetValores(elemento),0);
    }else if(!strcmp(tipo,"qround")){
        svgPrintQuadra(svg,genericGetValores(elemento),1);
    }else if(!strcmp(tipo,"ponto")){
        svgPrintPonto(svg,genericGetValores(elemento),5.0,"black");
    }else if(!strcmp(tipo,"cv")){
        svgPrintCv(svg,genericGetValores(elemento));
    }else if(!strcmp(tipo, "poligono")){
        svgPrintPoligono(svg, genericGetValores(elemento));
    }else if(!strcmp(tipo, "quadrado-soc")){
        svgPrintSoc(svg, genericGetValores(elemento));
    }else if(!strcmp(tipo, "linhatrac")){
        svgPrintLine(svg, genericGetValores(elemento), 1);
    }else if(!strcmp(tipo,"ec")){
        svgPrintEc(svg,genericGetValores(elemento));
    }
}

void svgPrintList(List l, char file[]){
    FILE *svg = fopen(file,"a");

    Node node = listGetFirst(l);

    while(node != NULL){
        Generic elemento = nodeGetData(node);
        svgSelectTag(elemento,(void*)svg);
        node = nodeGetNext(node);
    }
    
    fclose(svg);
}

void _svgPrintNodeQuadTree(FILE *svg, Generic elemento, Generic pai, char * corAtual){
    Ponto pFilho = NULL;
    Ponto pPai = NULL;
    char *id = NULL;
    
    if(!strcmp(genericGetTipo(elemento),"quadra")){
        Quadra quadra = genericGetValores(elemento);
        pFilho = quadraGetPonto(quadra);
        id = quadraGetCep(quadra);
    }
    else if(!strcmp(genericGetTipo(elemento),"circulo")){
        Circ equipamento = genericGetValores(elemento);
        pFilho = circGetPonto(equipamento);
        id = circGetId(equipamento);
    }
    if(pFilho == NULL || id == NULL) return;

    //criando a linha que faz a ligação entre o pai e o filho
    if(pai != NULL){
        if(!strcmp(genericGetTipo(pai),"quadra")){
            Quadra quadra = genericGetValores(pai);
            pPai = quadraGetPonto(quadra);
        }else if(!strcmp(genericGetTipo(pai),"circulo")){
            Circ equipamento = genericGetValores(pai);
            pPai = circGetPonto(equipamento);
        }
        
        if(!strcmp(genericGetTipo(elemento),"quadra")){
            fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\"/>\n",pontoGetX(pFilho)+50,pontoGetY(pFilho)+25,pontoGetX(pPai)+50,pontoGetY(pPai)+25);
        }else if(!strcmp(genericGetTipo(elemento),"circulo")){
            fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"black\"/>\n",pontoGetX(pFilho),pontoGetY(pFilho),pontoGetX(pPai),pontoGetY(pPai));
        }
    }

    //criando o retangulo que contem as informações e posicionamento do node
    double x = pontoGetX(pFilho);
    double y = pontoGetY(pFilho);
    double xC = x + 50;
    double yC = y + 20;
    if(!strcmp(genericGetTipo(elemento),"quadra")){
        fprintf(svg,"<rect id=\"box-info\" width=\"100\" height=\"50\" x=\"%lf\" y=\"%lf\" fill=\"%s\" fill-opacity=\"1\"/>\n",x,y,corAtual);
        fprintf(svg,"\t<text text-anchor=\"middle\" x=\"%.4lf\" y=\"%.4lf\" stroke=\"black\" fill=\"black\" font-size=\"7px\">x=%.2lf y= %.2lf</text>\n",xC,yC,x,y);
        fprintf(svg,"\t<text text-anchor=\"middle\" x=\"%.4lf\" y=\"%.4lf\" stroke=\"black\" fill=\"black\" font-size=\"8px\">%s</text>\n", xC, yC + 10, id);
    }else if(!strcmp(genericGetTipo(elemento),"circulo")){
        fprintf(svg,"<circle id=\"box-info\" r=\"3\" cx=\"%lf\" cy=\"%lf\" fill=\"%s\" fill-opacity=\"1\"/>\n",x,y,corAtual);
        fprintf(svg,"\t<text text-anchor=\"middle\" x=\"%.4lf\" y=\"%.4lf\" fill=\"black\" font-size=\"2px\">x=%.0lf y= %.0lf</text>\n",x,y+4,x,y);
        fprintf(svg,"\t<text text-anchor=\"middle\" x=\"%.4lf\" y=\"%.4lf\" fill=\"black\" font-size=\"2px\">%s</text>\n", x, y + 8, id);
    }
    
}

void _svgPrintTreeState(QuadNode tree, FILE *svg, int cor){
    if(tree == NULL) return;

    Generic elemento = QtGetInfo(NULL,tree);
    QuadNode qtPai = QtGetParent(tree);
    if(qtPai != NULL){
        Generic pai = QtGetInfo(NULL,qtPai);
        if(cor==1) _svgPrintNodeQuadTree(svg,elemento,pai,"#0000ff");
        else _svgPrintNodeQuadTree(svg,elemento,pai,"#00bcff");
    } else{
        _svgPrintNodeQuadTree(svg,elemento,NULL,"red");
    }
    
    if(cor==1) cor++;
    else cor--;
    
    _svgPrintTreeState(QtGetSE(tree),svg,cor);
    _svgPrintTreeState(QtGetSW(tree),svg,cor);
    _svgPrintTreeState(QtGetNE(tree),svg,cor);
    _svgPrintTreeState(QtGetNW(tree),svg,cor);
}

void svgPrintTreeState(QuadTree tree, char *path){

    QuadNode root = QtGetRoot(tree);
    svgOpenTag(path);
    FILE *svg = fopen(path,"a");
    // fprintf(svg,"<text text-anchor=\"middle\" x=\"-10\" y=\"-45\" stroke=\"black\" fill=\"black\" font-size=\"8px\">SE</text>\n");
    fprintf(svg,"<line x1=\"-40\" y1=\"-10\" x2=\"20\" y2=\"-10\" stroke=\"black\"/>\n");
    fprintf(svg,"<line x1=\"-10\" y1=\"-40\" x2=\"-10\" y2=\"20\" stroke=\"black\"/>\n");

    fprintf(svg,"<text text-anchor=\"middle\" x=\"-10\" y=\"-45\" fill=\"black\" font-size=\"8px\">SE</text>\n");
    fprintf(svg,"<text text-anchor=\"middle\" x=\"-10\" y=\"30\" fill=\"black\" font-size=\"8px\">NW</text>\n");
    fprintf(svg,"<text text-anchor=\"middle\" x=\"-50\" y=\"-7\" fill=\"black\" font-size=\"8px\">NE</text>\n");
    fprintf(svg,"<text text-anchor=\"middle\" x=\"30\" y=\"-7\" fill=\"black\" font-size=\"8px\">SW</text>\n");

    fprintf(svg,"<text text-anchor=\"middle\" x=\"-25\" y=\"-25\" fill=\"black\" font-size=\"8px\">SE</text>\n");
    fprintf(svg,"<text text-anchor=\"middle\" x=\"5\" y=\"-25\" fill=\"black\" font-size=\"8px\">NW</text>\n");
    fprintf(svg,"<text text-anchor=\"middle\" x=\"-25\" y=\"5\" fill=\"black\" font-size=\"8px\">NE</text>\n");
    fprintf(svg,"<text text-anchor=\"middle\" x=\"5\" y=\"5\" fill=\"black\" font-size=\"8px\">SW</text>\n");


    _svgPrintTreeState(root,svg,1);
    fclose(svg);

    svgCloseTag(path);
}

int _getOrientacao(Ponto inicio, Ponto fim){
    double x1 = pontoGetX(inicio), y1 = pontoGetY(inicio);
    double x2 = pontoGetX(fim), y2 = pontoGetY(fim);

    if(x1 == x2 && y1 > y2){ // PRA CIMA
        return 1;
    }else if(x1 == x2 && y2 > y1){ // PRA BAIXO
        return 2;
    }else if(x1 > x2 && y1 == y2){ // PRA ESQUERDA
        return 3;
    }else if(x2 > x1 && y1 == y2){ // PRA DIREITA
        return 4;
    }
    return 5;
}

void _printAresta(FILE *svg, Ponto inicio, Ponto fim, char cor[]){
    double x1 = pontoGetX(inicio), y1 = pontoGetY(inicio);
    double x2 = pontoGetX(fim), y2 = pontoGetY(fim);
    int orientacao = _getOrientacao(inicio,fim);
    if(orientacao == 1){
        fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\"/>\n",x1,y1,x2,y2,cor);
        double menor = _menor(y1,y2);
        fprintf(svg,"<polygon points=\"%lf,%lf %lf,%lf %lf,%lf\" fill=\"%s\"/>",x1,menor+1.5,x1-2,menor+2+1.5,x1+2,menor+2+1.5,cor);
    }
    else if (orientacao == 2){
        fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\"/>\n",x1,y1,x2,y2,cor);
        // x1p = x1-1.25(point radius);     y1p = |y2-y1|/2 + y1 + 1
        // x2p = x1 -1 -1.25(point radius); y2p = |y2-y1|/2 - y2 - 1
        // x3p = x1 +1 -1.25(point radius); y3p = 
        double maior = _maior(y1,y2);
        fprintf(svg,"<polygon points=\"%lf,%lf %lf,%lf %lf,%lf\" fill=\"%s\"/>",x1,maior-1.5,x1-2,maior-2-1.5,x1+2,maior-2-1.5,cor); 
    }
    else if(orientacao == 3){
        fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\"/>\n",x1,y1,x2,y2,cor);
        double menor = _menor(x1,x2);
        fprintf(svg,"<polygon points=\"%lf,%lf %lf,%lf %lf,%lf\" fill=\"%s\"/>",menor+1.5,y1,menor+1.5+2,y1-2,menor+1.5+2,y1+2,cor); 
    }
    else if (orientacao == 4){
        fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\"/>\n",x1,y1,x2,y2,cor);
        double maior = _maior(x1,x2);
        fprintf(svg,"<polygon points=\"%lf,%lf %lf,%lf %lf,%lf\" fill=\"%s\"/>",maior-1.5,y1,maior-1.5-2,y1-2,maior-1.5-2,y1+2,cor); 
    }
    else{
        fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\"/>\n",x1,y1,x2,y2,cor);
    }
}

void svgPrintGrafo(FILE *svg, Grafo grafo, int ehDirecionado){
    int qtdVertices = grafoGetQtdVertices(grafo);
    Vertice *vertices = grafoGetVertices(grafo);

    for(int i=0; i<qtdVertices; i++){
        List arestas = grafoVerticeGetAdjacencias(vertices[i]);
        Ponto inicio = grafoVerticeGetData(vertices[i]);
        Node aux = listGetFirst(arestas);
        while(aux){
            Aresta aresta = nodeGetData(aux);
            Vertice destino = grafoArestaGetFim(aresta);
            Ponto fim = grafoVerticeGetData(destino);
            
            if(ehDirecionado)
                _printAresta(svg,inicio,fim,"red");
            else
                _printAresta(svg,inicio,fim,"black");

            aux = nodeGetNext(aux);
        }
    }
    
    for(int i = 0; i<qtdVertices; i++){
        //printa o grafo com um raio de 10px
        Ponto ponto = grafoVerticeGetData(vertices[i]);
        svgPrintPonto(svg, ponto, 2.5,"#333333");
    }
    
}

void _printCaminho(FILE *svg, Ponto inicio, Ponto fim, char cor[], int ehMaisCurto){
    double x1 = pontoGetX(inicio), y1 = pontoGetY(inicio);
    double x2 = pontoGetX(fim), y2 = pontoGetY(fim);
    int orientacao = _getOrientacao(inicio,fim);

    if(ehMaisCurto)
            fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\"/>\n",x1+1.5,y1+1.5,x2+1.5,y2+1.5,cor);
        else
            fprintf(svg,"<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" stroke=\"%s\"/>\n",x1-1.5,y1-1.5,x2-1.5,y2-1.5,cor);
}

void svgPrintCaminho(FILE *svg, List caminho, char *cor, int ehMaisCurto){
    Node nodeProximo = listGetFirst(caminho);
    Node nodeAnterior;
    Ponto inicio, fim;

    while(nodeProximo){
        nodeAnterior = nodeProximo;
        nodeProximo = nodeGetNext(nodeProximo);
        if(nodeProximo == NULL) break;
        
        inicio = grafoVerticeGetData(nodeGetData(nodeAnterior)); // retorna um ponto armazenado no vertice
        fim = grafoVerticeGetData(nodeGetData(nodeProximo));

        _printCaminho(svg,inicio,fim, cor, ehMaisCurto);
    }
}













