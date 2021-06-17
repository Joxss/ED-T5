#include "qry.h"
#include "txt.h"
#include "calculos.h"
#include "convexHull.h"
#include "hashTable.h"
#include "svg.h"
#include <time.h>
#include "rua.h"

//************ T1 ************//
void qryPnt(FILE *txt, QuadTree circulos, QuadTree retangulos, QuadTree textos, int id, char corBorda[], char corPreench[]){
    char stringId[20];
    sprintf(stringId,"%d",id);

    Generic data = NULL;

    QuadNode node = QtGetById(circulos,stringId);
    if(node != NULL) {
        data = QtGetInfo(circulos,node);
        txtPntQry(txt,data);
        genericSetCores(data,corBorda,corPreench);
        return;
    }
    
    node = QtGetById(retangulos,stringId);
    if(node != NULL) {
        data = QtGetInfo(retangulos,node);
        txtPntQry(txt,data);
        genericSetCores(data,corBorda,corPreench);
        return;
    }

    node = QtGetById(textos,stringId);
    if(node != NULL) {
        data = QtGetInfo(textos,node);
        txtPntQry(txt,data);
        genericSetCores(data,corBorda,corPreench);
        return;
    }

    return;
}

void qryPntAll(FILE *txt, QuadTree circulos, QuadTree retangulos, QuadTree textos, int inicio, int fim, char corBorda[], char corPreench[]){
    for(int i=inicio; i<=fim; i++){
        qryPnt(txt,circulos,retangulos,textos,i,corBorda,corPreench);
    }
}

void qryDelf(FILE *txt, QuadTree circulos, QuadTree retangulos, QuadTree textos, int id){
    char stringId[20];
    sprintf(stringId,"%d",id);

    Generic data = NULL;

    QuadNode node = QtGetById(circulos, stringId);
    if(node != NULL){
        data = QtGetInfo(circulos,node);
        txtDelfQry(txt,data);
        Generic removed = QtRemoveNode(circulos,node); 
        return;
    }

    node = QtGetById(retangulos, stringId);
    if(node != NULL){
        data = QtGetInfo(retangulos,node);
        txtDelfQry(txt,data);
        Generic removed = QtRemoveNode(retangulos,node);
        return;
    }

    node = QtGetById(textos, stringId);
    if(node != NULL){
        data = QtGetInfo(textos,node);
        txtDelfQry(txt,data);
        Generic removed = QtRemoveNode(textos,node);
        return;
    }

    return;
}

void qryDelfAll(FILE *txt, QuadTree circulos, QuadTree retangulos, QuadTree textos, int inicio, int fim){
    for(int i=inicio; i<=fim; i++){
        qryDelf(txt,circulos,retangulos,textos,i);
    }
}

void iQry(FILE *txt, QuadTree circulos, QuadTree retangulos, List qryFigures,int id, double x, double y){
    char stringId[20];
    char cor[20];
    int boolean;
    double xCenter, yCenter;
    sprintf(stringId,"%d",id);

    QuadNode node = QtGetById(circulos, stringId);
    if(node == NULL){
        node = QtGetById(retangulos,stringId);
    }
    if(node == NULL) return;

    Generic data = QtGetInfo(NULL,node);
    
    if(checaInterno(data,x,y)){
        boolean = 1;
        strcpy(cor,"blue");
    }else{
        boolean = 0;
        strcpy(cor,"magenta");
    }

    if(!strcmp(genericGetTipo(data),"circulo")){
        xCenter = circGetX(genericGetValores(data));
        yCenter = circGetY(genericGetValores(data));
    }else{
        xCenter = rectGetXc(genericGetValores(data));
        yCenter = rectGetYc(genericGetValores(data));
    }

    Generic elemento;

    Circ ponto = createCircle("circ-qry-i", x, y, 2, "0px", cor, cor);
    elemento = createGeneric("circulo", ponto,freeCircle, circGetPonto);
    listInsert(qryFigures,elemento);

    Line line = createLine(x, y, xCenter, yCenter, "1px", cor);
    elemento = createGeneric("linha",line,freeLine, NULL);
    listInsert(qryFigures,elemento);

    txtInsQry(txt,data,boolean);
}

void oQry(FILE *txt, QuadTree circulos, QuadTree retangulos, List qryFigures, int id1, int id2){
    double x, y, w, h;
    char stringId1[20], stringId2[20];
    int boolean;
    sprintf(stringId1,"%d",id1);
    sprintf(stringId2,"%d",id2);// TALVEZ SEJA UTIL

    QuadNode node1 = QtGetById(circulos,stringId1);
    if(node1 == NULL) node1 = QtGetById(retangulos,stringId1);

    Node node2 = QtGetById(circulos,stringId2);
    if(node2 == NULL) node2 = QtGetById(retangulos,stringId2);

    if(node1 == NULL || node2 == NULL) return;

    Generic data1 = QtGetInfo(NULL,node1);
    Generic data2 = QtGetInfo(NULL,node2);

    if(checaColisao(data1,data2)){
        boolean = 1;
    }else{
        boolean = 0;
    }
    
    calculaValoresRect(&x,&y,&w,&h, data1, data2);
    
    Generic elemento;
    Rect rect = createRect("rect-qry-o",x,y,w,h,"1px","black","white");
    if(boolean){
        //borda tracejada (-) = tracejado
        elemento = createGeneric("rtrac",rect,freeRect,rectGetPonto);
    }else{
        //borda lisa (+) = não tracejado
        elemento = createGeneric("rntrac",rect,freeRect,rectGetPonto);
    }

    listInsert(qryFigures,elemento);

    txtOverQry(txt, data1,data2,boolean);
}

//************ T2 ************//

void qryDq(FILE *txt, Htable cepXquadra, QuadTree quadras, QuadTree hidrantes, QuadTree semaforos, QuadTree radios, List qryFigures, char id[], double r, int opcional){
    double xCenter=0, yCenter=0;
    int boolean = 0;
    char tipo[20];
    QuadNode equipamento;
    Node nodeQuadra, aux;
    Generic data;
    
    //verifica se o elemento esta na lista de  HIDRANTES
    equipamento = QtGetById(hidrantes,id);
    if(equipamento != NULL){
        boolean = 1;
        strcpy(tipo,"hidrante");
    }

    //verifica se o elemento esta na lista de  SEMAFORO
    if(!boolean) equipamento = QtGetById(semaforos,id);
    if(equipamento != NULL && !boolean){
        boolean = 1;
        strcpy(tipo,"semaforo");
    }

    //verifica se o elemento esta na lista de  RADIOS
    if(!boolean) equipamento = QtGetById(radios,id);
    if(equipamento != NULL && !boolean){
        boolean = 1;
        strcpy(tipo,"radio");
    }

    if(!boolean) return;

    data = QtGetInfo(NULL,equipamento);
    Circ equip = genericGetValores(data);
    xCenter = circGetX(equip);
    yCenter = circGetY(equip);
    List quadrasInside = QtNosDentroCirculo(quadras,xCenter,yCenter,r);

    nodeQuadra = listGetFirst(quadrasInside);
    
    while(nodeQuadra != NULL){  // Iterar por todos os elementos da lista quadras
        data = nodeGetData(nodeQuadra);
        Quadra quadra = genericGetValores(data);
        
        aux = nodeGetNext(nodeQuadra);
        
        txtCepQuadra(txt, quadra);
        
        if(opcional){
            Quadra quadraNova = createQuadra(quadraGetCep(quadra),quadraGetX(quadra),quadraGetY(quadra),quadraGetW(quadra),quadraGetH(quadra),quadraGetBorda(quadra),quadraGetBorda(quadra),quadraGetCorPreench(quadra));
            Generic elementoQuadra = createGeneric("qround",quadraNova,freeQuadra,quadraGetPonto);
            listInsert(qryFigures,elementoQuadra);    
        }

        char *idQuadra = quadraGetCep(quadra);
        hashRemoveKey(cepXquadra,idQuadra);

        Ponto pQuadra = quadraGetPonto(quadra);
        QuadNode removed = QtGetNode(quadras,pontoGetX(pQuadra),pontoGetY(pQuadra));
        Generic removedQuadra = QtRemoveNode(quadras,removed);

        nodeQuadra = aux;
    }

    Generic elemento;
    Circ anel;
    anel = createCircle("raioDeBusca", xCenter,yCenter, r,"1px","black","white");
    elemento = createGeneric("anel",anel,freeCircle,circGetPonto);
    listInsert(qryFigures, elemento);

    anel = createCircle("PrimeiroAnel", xCenter,yCenter, 2.5, "1px","green","transparent"); //ADICIONA O PRIMEIRO ANEL EM VOLTA DO EQUIPAMENTO SELECIONADO
    elemento = createGeneric("anel",anel,freeCircle,circGetPonto);
    listInsert(qryFigures,elemento);

    anel = createCircle("SegundoAnel", xCenter,yCenter, 3.5, "1px","orange","transparent");//ADICIONA O SEGUNDO ANEL EM VOLTA DO EQUIPAMENTO SELECIONADO
    elemento = createGeneric("anel",anel,freeCircle,circGetPonto);
    listInsert(qryFigures,elemento);
    
    txtDetalhes(txt,equip,tipo); //printar o equipamento urbano
    freeLista2(quadrasInside);
}

void qryDel(FILE *txt, Htable cepXquadra, QuadTree quadras, QuadTree hidrantes, QuadTree semaforos, QuadTree radios, List qryFigures, char id[]){
    double xCenter=0, yCenter=0;
    int boolean = 0;
    QuadNode node;
    
    node = QtGetById(quadras, id);
    if(node != NULL){
        boolean = 1;
        Generic data = QtGetInfo(quadras,node);
        txtDetalhes(txt,genericGetValores(data),"quadra");
        xCenter = quadraGetXc(genericGetValores(data));
        yCenter = quadraGetYc(genericGetValores(data));
        
        Generic removed = QtRemoveNode(quadras,node);
        hashRemoveKey(cepXquadra,id);
    }
    //verifica se o elemento esta na lista de  HIDRANTES
    node = (boolean) ? NULL : QtGetById(hidrantes, id);

    if(node != NULL){
        boolean = 1;
        Generic data = QtGetInfo(hidrantes,node);
        txtDetalhes(txt,genericGetValores(data),"hidrante");
        xCenter = circGetX(genericGetValores(data));
        yCenter = circGetY(genericGetValores(data));

        Generic removed = QtRemoveNode(hidrantes,node);
    }

    //verifica se o elemento esta na lista de  SEMAFORO
    node = (boolean) ? NULL : QtGetById(semaforos, id);
    if(node != NULL){
        boolean = 1;
        Generic data = QtGetInfo(semaforos,node);
        txtDetalhes(txt,genericGetValores(data),"semaforo");
        xCenter = circGetX(genericGetValores(data));
        yCenter = circGetY(genericGetValores(data));

        Generic removed = QtRemoveNode(semaforos,node);
    }

    //verifica se o elemento esta na lista de  RADIOS
    node = (boolean) ? NULL : QtGetById(radios, id);
    if(node != NULL){
        boolean = 1;
        Generic data = QtGetInfo(radios,node);
        txtDetalhes(txt,genericGetValores(data),"radio");
        xCenter = circGetX(genericGetValores(data));
        yCenter = circGetY(genericGetValores(data));
        
        Generic removed = QtRemoveNode(radios,node);
    }

    if(boolean){
        Generic elemento;

        Line line = createLine(xCenter,yCenter,xCenter, 0,"1px","black");
        elemento = createGeneric("linha",line,freeLine, NULL);
        listInsert(qryFigures,elemento);

        Text text = createText("VandaoGod",xCenter+2,0,"black","black",id);
        elemento = createGeneric("texto",text,freeText, textGetPonto);
        listInsert(qryFigures,elemento);
    }
}

void qryCbq(FILE *txt, QuadTree quadras, double x, double y, double r, char corBorda[], List qryFigures){
    List quadrasInside = QtNosDentroCirculo(quadras,x,y,r);

    Node node = listGetFirst(quadrasInside);
    Generic data;

    while(node != NULL){
        data = nodeGetData(node);
        Quadra quadra = genericGetValores(data);
        quadraSetCorBorda(quadra,corBorda);
        txtCepQuadra(txt,quadra);
        node = nodeGetNext(node);
    }

    // Generic elemento;
    // Circ anel;
    // anel = createCircle("raioDeBusca-cbq", x,y, r,"1px","black","white");
    // elemento = createGeneric("anel",anel,freeCircle);
    // listInsert(qryFigures, elemento);

    freeLista2(quadrasInside);
}

void qryCrd(FILE *txt, QuadTree quadras, QuadTree hidrantes, QuadTree semaforos, QuadTree radios, char id[]){
    QuadNode node = NULL;
    
    //verifica se o elemento esta na lista de  QUADRAS
    node = QtGetById(quadras, id);
    if(node != NULL){
        Generic data = QtGetInfo(quadras,node);
        txtCrdQry(txt, genericGetValores(data), "quadra");
        return;
    }
    
    //verifica se o elemento esta na lista de  HIDRANTES
    node = QtGetById(hidrantes, id);
    if(node != NULL){
        Generic data = QtGetInfo(hidrantes,node);
        txtCrdQry(txt, genericGetValores(data), "hidrante");
        return;
    }

    //verifica se o elemento esta na lista de  SEMAFORO
    node = QtGetById(semaforos, id);
    if(node != NULL){
        Generic data = QtGetInfo(semaforos,node);
        txtCrdQry(txt,genericGetValores(data),"semaforo");
        return;
    }

    //verifica se o elemento esta na lista de  RADIOS
    node = QtGetById(radios, id);
    if(node != NULL){
        Generic data = QtGetInfo(radios,node);
        txtCrdQry(txt,genericGetValores(data),"radio");
        return;
    }

    return;
}

void qryCar(FILE *txt, QuadTree quadras, List qryFigures, double x, double y, double w, double h){
    double areaTotal = 0;
    char buffer[30];
    List quadrasInside = QtNosDentroRetangulo(quadras,x,y,x+w,y+h);
    Node node = listGetFirst(quadrasInside);
    Generic data;
    Generic elemento;

    while(node != NULL){
        data = nodeGetData(node);
        Quadra quadra = genericGetValores(data);
        double area = quadraGetW(quadra) * quadraGetH(quadra);

        sprintf(buffer,"%lf",area);
        areaTotal += area;

        Text areaTexto = createText("area-quadra",quadraGetXc(quadra),quadraGetYc(quadra),"black","black",buffer);
        elemento = createGeneric("txtcenter",areaTexto,freeText,textGetPonto);
        listInsert(qryFigures,elemento);

        txtAreaQuadra(txt, buffer, quadraGetCep(quadra));
        node = nodeGetNext(node);
    }

    Rect rect = createRect("retangulo-busca",x,y,w,h,"1px","black","white");
    elemento = createGeneric("rntrac",rect,freeRect,rectGetPonto);
    listInsert(qryFigures,elemento);

    Line line = createLine(rectGetX(rect),rectGetY(rect),rectGetX(rect),0,"1px","black");
    elemento = createGeneric("linha",line,freeLine, NULL);
    listInsert(qryFigures,elemento);

    sprintf(buffer,"%lf",areaTotal);
    Text text = createText("vandaoGod",rectGetX(rect)+2,0,"black","black",buffer);
    elemento = createGeneric("texto",text,freeText, textGetPonto);
    listInsert(qryFigures,elemento);

    txtAreaTotal(txt,buffer);
    freeLista2(quadrasInside);
}

//************ T3 ************//

void qryCv(QuadTree casosCv, Htable cepXquadra, int n, char id[], char face, double num){
    double x, y, w, h;
    // QuadNode node = QtGetById(quadras,id);
    // if(node == NULL) return;
    // Generic quadra = QtGetInfo(quadras,node);
    Quadra quadra = hashGetKey(cepXquadra,id);
    
    //calcula os valores para o quadrado que contem o numero de casos de covid na quadra
    if(quadra == NULL){
        printf("cep %s inexistente krl q merda em vandao\n",id);
    }
    quadraAddCasos(quadra, face, n);
    setCv(&x, &y, &w, &h, n,quadra,face,num);
    Quad q = createQuad(x,y,w,h,n);
    quadSetFace(q,face);
    Ponto p = quadGetPonto(q);
    Generic elemento = createGeneric("cv",q,freeQuad,quadGetPonto);
    
    QtInsert(casosCv,p,elemento);
}

//alterar para encontrar a regiao de densidade correta
double _getDensidade(QuadNode densidades, Poligono polig){

    if(densidades == NULL) return -1;

    Generic elemento = QtGetInfo(NULL,densidades);
    if(elemento != NULL){ // ELEMENTO FOI DELETADO PELA FUNÇÃO QtRemoveNode
        Quad densidade = genericGetValores(elemento);

        if(checkPoligInsideRect(polig,densidade)){
            return quadGetN(densidade);
        }
    }

    double valor = _getDensidade(QtGetNW(densidades),polig);
    if(valor != -1) return valor;

    valor = _getDensidade(QtGetNE(densidades),polig);
    if(valor != -1) return valor;

    valor = _getDensidade(QtGetSW(densidades),polig);
    if(valor != -1) return valor;

    valor = _getDensidade(QtGetSE(densidades),polig);
    if(valor != -1) return valor;

    return -1;
}

char _incidenciaPoligono(QuadTree postos, Poligono poli, int totalCasos, double densidade, double area){
    int qtdHabitantes = area * densidade;
    double casosPor100K = totalCasos * (100000/(double)qtdHabitantes);
    //setando a cor do poligono conforme a incidencia
    if(casosPor100K<0.1){
        poligSetCor(poli,"#00FFFF");
        return 'A';
    }else if(casosPor100K < 0.5){
        poligSetCor(poli,"#008080");
        return 'B';
    }else if(casosPor100K < 10){
        poligSetCor(poli,"#FFFF00");
        return 'C';    
    }else if(casosPor100K < 20){
        poligSetCor(poli,"#FF0000");
        return 'D';
    }else{
        poligSetCor(poli,"#800080");
        if(!postosSaudeInsPolig(QtGetRoot(postos),poli)){
            //cria um ps no centroide
            Ponto centro = createPoint(poligGetXc(poli),poligGetYc(poli));
            Generic g = createGeneric("ponto",centro,freePonto,pontoGetPonto);
            QtInsert(postos,centro,g);
        }
        return 'E';

    }
}

void qryCi(FILE *txt, QuadTree postos, QuadTree casosCv, QuadTree densidades, List qryFigures, double x, double y, double r){
    //cria o circulo do ci
    Circ c = createCircle("raio-ci",x,y,r,"3px","green","white");
    Generic circ = createGeneric("anel",c,freeCircle,circGetPonto);
    listInsert(qryFigures,circ);
    
    Node node;
    Generic g;
    Ponto p;

    int totalCasos = 0;

    List postosInside = QtNosDentroCirculo(casosCv,x,y,r);
    List pontosInside = createLista();

    node = listGetFirst(postosInside);
    while(node != NULL){
        double x, y;
        g = nodeGetData(node);
        Quad q = genericGetValores(g);
        if(quadGetFace(q)=='N'){
            x = quadGetXc(q);
            y = quadGetY(q)+quadGetH(q);
        }else if(quadGetFace(q)=='S'){
            x = quadGetXc(q);
            y = quadGetY(q);
        }else if(quadGetFace(q)=='L'){
            x = quadGetX(q);
            y = quadGetYc(q);
        }else if(quadGetFace(q)=='O'){
            x = quadGetX(q) + quadGetW(q);
            y = quadGetYc(q);
        }

        Ponto ponto = createPoint(x,y);
        Generic pontoElemento = createGeneric("ponto",ponto,freePonto,pontoGetPonto);
        listInsert(pontosInside,pontoElemento);

        totalCasos += quadGetN(q);
        txtCoordenadas(txt,quadGetXc(q), quadGetYc(q));
        node = nodeGetNext(node);
    }
    int count = listLenght(pontosInside);
    Generic *convex = convexHull(pontosInside,&count);

    if(convex == NULL){
        fprintf(txt,"Não foi possivel formar a envoltoria convexa\n");
        freeLista(pontosInside,freeGeneric);
        freeLista2(postosInside);
        return;
    }

    //cria duas lista de coordenadas x e y
    double *xPoli = malloc(sizeof(double)*count);
    double *yPoli = malloc(sizeof(double)*count);

    for(int i=0;i<count; i++){

        g = convex[i];
        p = genericGetPonto(g);

        xPoli[i] = pontoGetX(p);
        yPoli[i] = pontoGetY(p);
    }
    Poligono poli = createPoligono(count,xPoli,yPoli);

    double densidade = _getDensidade(QtGetRoot(densidades), poli);

    if(densidade == -1){ 
        printf("Não foi possivel encontrar a densidade da região\n");
        free(convex);
        freePolig(poli);
        freeLista(pontosInside,freeGeneric);
        freeLista2(postosInside);
        return;
    }

    double area = poligGetArea(poli);
    area /= 1000000; // TRANSFORMAR AREA EM M2 PARA KM2
    char incidencia = _incidenciaPoligono(postos,poli, totalCasos,densidade, area);
    
    txtCiQry(txt,totalCasos,area,incidencia);

    g = createGeneric("poligono",poli,freePolig, NULL);
    listInsert(qryFigures,g);

    freeLista2(postosInside);
    freeLista(pontosInside,freeGeneric);
    free(convex);
}

void qrySoc(FILE *txt, QuadTree postos, Htable cepXquadra, List qryFigures, int k, char * cep, char face, double num){
    double x, y, w, h, xPonto, yPonto;
    Quadra quadra = hashGetKey(cepXquadra,cep);
    
    setCv(&x, &y, &w, &h, 1 ,quadra,face,num);
    Quad q = createQuad(x,y,w,h,k);
    quadSetFace(q,face);

    Generic elemento = createGeneric("quadrado-soc",q,freeQuad, quadGetPonto);
    listInsert(qryFigures,elemento);

    if(quadGetFace(q)=='N'){
        xPonto = quadGetXc(q);
        yPonto = quadGetY(q)+quadGetH(q);
    }else if(quadGetFace(q)=='S'){
        xPonto = quadGetXc(q);
        yPonto = quadGetY(q);
    }else if(quadGetFace(q)=='L'){
        xPonto = quadGetX(q);
        yPonto = quadGetYc(q);
    }else if(quadGetFace(q)=='O'){
        xPonto = quadGetX(q) + quadGetW(q);
        yPonto = quadGetYc(q);
    }

    Ponto endereco = createPoint(xPonto,yPonto);
    int n;
    Ponto * menores = shellSortParcial(postos, k, endereco, &n);
    
    if(menores != NULL){

        for(int i=0; i<n; i++){
            txtCoordenadas(txt,pontoGetX(menores[i]),pontoGetY(menores[i]));
            
            Line l = createLine(pontoGetX(endereco),pontoGetY(endereco),pontoGetX(menores[i]),pontoGetY(menores[i]),"red","red");
            Generic g = createGeneric("linhatrac",l,freeLine, NULL);
            listInsert(qryFigures,g);
        }
        
        freeArray(menores,n);
    }

    free(endereco);
}

//************ T4 ************//

void qryM(FILE *txt, Htable pessoas, Htable quadras, char *cep){
    Quadra quadra = hashGetKey(quadras,cep);
    if(quadra == NULL){
        fprintf(txt,"ERRO - QUADRA INEXISTENTE\n");
        return;
    }
    List moradores = quadraGetMoradores(quadra);
    Node node = listGetFirst(moradores);
    Generic morador;
    Pessoa pessoa;
    
    while(node != NULL){
        morador = nodeGetData(node);
        pessoa = hashGetKey(pessoas, moradorGetCpf(genericGetValores(morador)));

        if(pessoa != NULL) txtMQry(txt,genericGetValores(morador), pessoa);
        
        node = nodeGetNext(node);
    }
}

void qryDm(FILE *txt, List qryFigures, QuadTree moradores, Htable cpfXpessoa, char *cpf){
    Pessoa pessoa = hashGetKey(cpfXpessoa,cpf);
    if(pessoa == NULL){
        fprintf(txt,"Morador inexistente\n");
        return;
    }

    QuadNode nodeMorador = QtGetById(moradores,cpf);
    if(nodeMorador == NULL) {
        fprintf(txt,"Morador inexistente\n");
        return;
    }
    Generic elementoMorador = QtGetInfo(moradores,nodeMorador);
    Morador morador = genericGetValores(elementoMorador);
    Ponto coord = moradorGetPonto(morador);

    Line line = createLine(pontoGetX(coord), pontoGetY(coord), pontoGetX(coord), 0, "1px", "blue");
    Generic elemento = createGeneric("linha",line,freeLine, NULL);
    listInsert(qryFigures,elemento);

    char buffer[500];
    //cpf,
    //nome
    //endereço do morador
    sprintf(buffer,"%s %s %s %c %d %s", cpf, pessoaGetNome(pessoa), moradorGetCep(morador), moradorGetFace(morador), moradorGetNum(morador), moradorGetCompl(morador));
    Text text = createText("vandaoGod",pontoGetX(coord)+2,0,"black","black",buffer);
    elemento = createGeneric("texto",text,freeText, textGetPonto);
    listInsert(qryFigures,elemento);

    txtDmQry(txt, morador, pessoa);
}

void qryDe(FILE *txt, QuadTree estabelecimentos, Htable cpfXpessoa, char *cnpj){
    QuadNode nodeEstabelecimento = QtGetById(estabelecimentos,cnpj);
    if(nodeEstabelecimento == NULL) {
        fprintf(txt,"Estabelecimento inexistente\n");
        return;
    }
    Generic elementoEstabelecimento = QtGetInfo(estabelecimentos,nodeEstabelecimento);
    Estabelecimento estabelecimento = genericGetValores(elementoEstabelecimento);

    Pessoa pessoa = hashGetKey(cpfXpessoa,estabelecimentoGetCpf(estabelecimento));
    if(pessoa == NULL){
        fprintf(txt,"Proprietario do estabelecimento inexistente\n");
        return;
    }

    txtDeQry(txt, estabelecimento, pessoa);
}

void qryMud(FILE *txt, QuadTree moradores, Htable cepXquadra, Htable cpfXpessoa, Htable cpfXcep, List qryFigures, char *cpf, char *cep, char face, int num,char *compl){
    Generic elemento;
    Quadra quadraNova = hashGetKey(cepXquadra,cep);
    if(quadraNova == NULL){
        fprintf(txt,"Cep não existe\n");
        return;
    }

    QuadNode nodeMorador = QtGetById(moradores,cpf);
    if(nodeMorador == NULL){
        fprintf(txt,"CPF não existe\n");
        return;
    }
    Generic elementoMorador = QtGetInfo(moradores,nodeMorador);
    if(elementoMorador == NULL){
        printf("morador nulo\n");
        return;
    }

    Morador morador = genericGetValores(elementoMorador);

    Pessoa pessoa = hashGetKey(cpfXpessoa,cpf);
    if(pessoa == NULL){
        printf("pessoa nula\n");
    }

    char *cepNovo = malloc(sizeof(char)*strlen(cep)+1);
    strcpy(cepNovo,cep);
    char *cepRetornado = hashUpdateKey(cpfXcep,cpf,cepNovo);
    free(cepRetornado);

    char cepAntigo[30], complAntigo[30];
    char faceAntiga = moradorGetFace(morador);
    int numAntigo = moradorGetNum(morador);
    
    strcpy(cepAntigo,moradorGetCep(morador));
    strcpy(complAntigo,moradorGetCompl(morador));

    if(strcmp(cepNovo,cepAntigo) != 0){
        quadraInserirMorador(quadraNova,elementoMorador);
        Quadra quadraAntiga = hashGetKey(cepXquadra,cepAntigo);
        if(quadraAntiga != NULL){
            quadraRemoverMorador(quadraAntiga,cpf);
        }
    }

    Ponto coord = moradorGetPonto(morador);
    double xAntigo = pontoGetX(coord), yAntigo = pontoGetY(coord);

    moradorSetEndereco(morador,quadraNova,face,num,compl);

    double xNovo = pontoGetX(coord), yNovo = pontoGetY(coord);

    Line linha = createLine(xAntigo, yAntigo, xNovo, yNovo, "3px","red");
    elemento = createGeneric("linha",linha,freeLine, NULL);
    listInsert(qryFigures,elemento);

    Circ circ = createCircle("xablau",xAntigo,yAntigo,3,"2px","white","red"); //circulo antigo
    elemento = createGeneric("circulo",circ,freeCircle, circGetPonto);
    listInsert(qryFigures, elemento);

    circ = createCircle("xablau",xNovo,yNovo,3,"2px","white","blue"); //circulo antigo
    elemento = createGeneric("circulo",circ,freeCircle, circGetPonto);
    listInsert(qryFigures, elemento);

    txtMudQry(txt,pessoa,morador,cepAntigo,faceAntiga,numAntigo,complAntigo);
}

void qryDmprbt(QuadTree tree, char *path){
    if(QtGetQtdRemovidos(tree) != 0){
        QtRefazArvore(tree);
    }

    svgPrintTreeState(tree,path);
}

void qryEplg(FILE *txt, QuadTree estabelecimentos, Htable tipoXdescricao, Htable cpfXpessoa ,List qryFigures, double x, double y, double w, double h, char *tipo){
    char *descricao = NULL;
    if(tipo != NULL){
        char *descricao = hashGetKey(tipoXdescricao,tipo);
        if(descricao == NULL){
            fprintf(txt,"Tipo inexistente\n");
            return;
        }
    }

    List estabelecimentosInside = QtNosDentroRetangulo(estabelecimentos,x,y,x+w,y+h);

    Rect rect = createRect("retangulo-busca",x,y,w,h,"1px","black","white");
    Generic elemento = elemento = createGeneric("rntrac",rect,freeRect, rectGetPonto);
    listInsert(qryFigures,elemento);

    int tipoEspecifico;
    Node node = listGetFirst(estabelecimentosInside);
    while(node != NULL){
        tipoEspecifico = 0;
        elemento = nodeGetData(node);
        Estabelecimento est = genericGetValores(elemento);
        if(tipo == NULL) tipoEspecifico = 1;
        else if(!strcmp(descricao,estabelecimentoGetDescricao(est))) tipoEspecifico = 1;

        if(tipoEspecifico){
            Pessoa pessoa = hashGetKey(cpfXpessoa,estabelecimentoGetCpf(est));

            Ponto p = estabelecimentoGetCoord(est);

            Circ circ = createCircle("destaque-est",pontoGetX(p),pontoGetY(p),5,"1px","black","white");
            Generic g = createGeneric("circulo",circ,freeCircle, circGetPonto);
            listInsert(qryFigures,g);

            txtEplgQry(txt,pessoa,est);
        }
        node = nodeGetNext(node);
    }
    freeLista2(estabelecimentosInside);
}

void _qryCatac(FILE *txt, QuadTree arvore, List lista){
    Node node = listGetFirst(lista);
    double x, y;
    QuadNode qNode;
    Ponto p;
    while(node != NULL){
        Generic elemento = nodeGetData(node);
        Ponto p = genericGetPonto(elemento);
        x = pontoGetX(p);
        y = pontoGetY(p);

        txtCatacQry(txt, elemento);

        qNode = QtGetNode(arvore,x,y);
        QtRemoveNode(arvore,qNode);
        node = nodeGetNext(node);
    }
}

void qryCatac(FILE *txt, QuadTree quadras, QuadTree hidrantes, QuadTree semaforos, QuadTree radios, QuadTree moradores, QuadTree estabelecimentos, List qryFigures, double x, double y, double r){
    Circ circ = createCircle("raio-busca",x,y,r,"1px","#6C6753","#CCFF00");
    Generic elemento = createGeneric("anel2",circ,freeCircle, circGetPonto);
    listInsert(qryFigures,elemento);
    
    List quadrasInside = QtNosDentroCirculo(quadras,x,y,r);
    List hidrantesInside = QtNosDentroCirculo(hidrantes,x,y,r);
    List semaforosInside = QtNosDentroCirculo(semaforos,x,y,r);
    List radiosInside = QtNosDentroCirculo(radios,x,y,r);
    List moradoresInside = QtNosDentroCirculo(moradores,x,y,r);
    List estabelecimentosInside = QtNosDentroCirculo(estabelecimentos,x,y,r);

    _qryCatac(txt,quadras,quadrasInside);
    _qryCatac(txt,hidrantes,hidrantesInside);
    _qryCatac(txt,semaforos,semaforosInside);
    _qryCatac(txt,radios,radiosInside);
    _qryCatac(txt,moradores,moradoresInside);
    _qryCatac(txt,estabelecimentos,estabelecimentosInside);

    freeLista2(quadrasInside);
    freeLista2(hidrantesInside);
    freeLista2(semaforosInside);
    freeLista2(radiosInside);
    freeLista2(moradoresInside);
    freeLista2(estabelecimentosInside);
}

//************ T5 ************//

void qryCCV(QuadTree trees[], Grafo ruas, char path[]){
    FILE *svg = fopen(path,"w");
    Grafo ciclovias = grafoCopiaParaNaoDirecionado(ruas);
    Grafo agm = primMST(ciclovias,ruaGetDistancia);
    fprintf(svg,"<svg>\n");

    QtPercorreProfundidade(trees[0],svgSelectTag,(void*)svg);
    QtPercorreProfundidade(trees[1],svgSelectTag,(void*)svg);
    QtPercorreProfundidade(trees[2],svgSelectTag,(void*)svg);
    QtPercorreProfundidade(trees[3],svgSelectTag,(void*)svg);
    QtPercorreProfundidade(trees[4],svgSelectTag,(void*)svg);
    QtPercorreProfundidade(trees[5],svgSelectTag,(void*)svg);
    QtPercorreProfundidade(trees[6],svgSelectTag,(void*)svg);
    QtPercorreProfundidade(trees[7],svgSelectTag,(void*)svg);

    //svgPrintGrafo(svg,ruas,0);
    svgPrintGrafo(svg,ciclovias,0);
    svgPrintGrafo(svg,agm,1);
    fprintf(svg,"</svg>\n");

    freeMST(ciclovias);
    freeMST(agm);
    fclose(svg);
}

void qryP(QuadTree trees[], Grafo ruas, Ponto inicio, Ponto destino, char corCurto[], char corRapido[], char pathSvg[], FILE *pathTxt){
    Vertice vInicio = grafoVerticeMaisProximo(inicio,ruas);
    Vertice vFim = grafoVerticeMaisProximo(destino,ruas);
    Ponto pInicio = grafoVerticeGetData(vInicio);
    Ponto pFim = grafoVerticeGetData(vFim);
    fprintf(pathTxt,"Caminho mais curto: ");
    List caminhoMaisCurto = melhorCaminho(ruas,vInicio,vFim,ruaGetDistancia,pathTxt);

    fprintf(pathTxt,"Caminho mais rapido: ");
    List caminhoMaisRapido = melhorCaminho(ruas,vInicio,vFim,ruaGetTempo,pathTxt);
    if(caminhoMaisRapido == NULL){
        printf("caminhomaisrapido nulo\n");
    }
    if(caminhoMaisCurto == NULL || caminhoMaisRapido == NULL){
        printf("dois caminhos nulos");
        return;
    }

    FILE *svg = fopen(pathSvg,"a");

    //verifica se o arquivo esta vazio
    if (svg != NULL) {
        fseek (svg, 0, SEEK_END);
        long size = ftell(svg);

        if (size == 0) {
            fprintf(svg,"<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n");
            fprintf(svg,"<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\">\n");
            svgPrintFilter(svg);
            QtPercorreProfundidade(trees[0],svgSelectTag,(void*)svg);
            QtPercorreProfundidade(trees[1],svgSelectTag,(void*)svg);
            QtPercorreProfundidade(trees[2],svgSelectTag,(void*)svg);
            QtPercorreProfundidade(trees[3],svgSelectTag,(void*)svg);
            QtPercorreProfundidade(trees[4],svgSelectTag,(void*)svg);
            QtPercorreProfundidade(trees[5],svgSelectTag,(void*)svg);
            QtPercorreProfundidade(trees[6],svgSelectTag,(void*)svg);
            QtPercorreProfundidade(trees[7],svgSelectTag,(void*)svg);

        }
    }

    fprintf(svg,"<circle id=\"inicio\" r=\"7\" cx=\"%lf\" cy=\"%lf\" stroke-width=\"1px\" stroke=\"black\" fill=\"black\" fill-opacity=\"0.7\"/>\n",pontoGetX(inicio),pontoGetY(inicio));
    fprintf(svg,"<text id=\"inicio-t\" x=\"%lf\" y=\"%lf\" stroke=\"white\" fill=\"white\" text-anchor=\"middle\" alignment-baseline=\"middle\" font-size=\"8\">I</text>\n",pontoGetX(inicio),pontoGetY(inicio));
    svgPrintCaminho2(svg,caminhoMaisCurto, corCurto, 1);
    svgPrintCaminho2(svg,caminhoMaisRapido, corRapido, 0);

    fprintf(svg,"<circle id=\"fim\" r=\"7\" cx=\"%lf\" cy=\"%lf\" stroke-width=\"1px\" stroke=\"black\" fill=\"black\" fill-opacity=\"0.7\"/>\n",pontoGetX(destino),pontoGetY(destino));
    fprintf(svg,"<text id=\"inicio-t\" x=\"%lf\" y=\"%lf\" stroke=\"white\" fill=\"white\" text-anchor=\"middle\" alignment-baseline=\"middle\" font-size=\"8\">F</text>\n",pontoGetX(destino),pontoGetY(destino));
    fclose(svg);
    freeLista2(caminhoMaisCurto);
    freeLista2(caminhoMaisRapido);
}

void qryPb(QuadTree trees[], Grafo ruas, Ponto inicio, Ponto destino, char corCurto[], char pathSvg[], FILE *pathTxt){
    Grafo ciclovias = grafoCopiaParaNaoDirecionado(ruas);
    Grafo agm = primMST(ciclovias,ruaGetDistancia);

    Vertice vInicio = grafoVerticeMaisProximo(inicio,agm);
    Vertice vFim = grafoVerticeMaisProximo(destino,agm);
    Ponto pInicio = grafoVerticeGetData(vInicio);
    Ponto pFim = grafoVerticeGetData(vFim);
    fprintf(pathTxt,"Caminho mais curto: ");
    List caminhoMaisCurto = melhorCaminho(agm,vInicio,vFim,ruaGetDistancia,pathTxt);

    if(caminhoMaisCurto == NULL) return;

    FILE *svg = fopen(pathSvg,"a");

    //verifica se o arquivo esta vazio
    if (svg != NULL) {
        fseek (svg, 0, SEEK_END);
        long size = ftell(svg);

        if (size == 0) {
            fprintf(svg,"<svg>\n");
            QtPercorreProfundidade(trees[0],svgSelectTag,(void*)svg);
            QtPercorreProfundidade(trees[1],svgSelectTag,(void*)svg);
            QtPercorreProfundidade(trees[2],svgSelectTag,(void*)svg);
            QtPercorreProfundidade(trees[3],svgSelectTag,(void*)svg);
            QtPercorreProfundidade(trees[4],svgSelectTag,(void*)svg);
            QtPercorreProfundidade(trees[5],svgSelectTag,(void*)svg);
            QtPercorreProfundidade(trees[6],svgSelectTag,(void*)svg);
            QtPercorreProfundidade(trees[7],svgSelectTag,(void*)svg);

        }
    }

    fprintf(svg,"<circle id=\"inicio\" r=\"7\" cx=\"%lf\" cy=\"%lf\" stroke-width=\"1px\" stroke=\"black\" fill=\"black\" fill-opacity=\"0.7\"/>\n",pontoGetX(inicio),pontoGetY(inicio));
    fprintf(svg,"<text id=\"inicio-t\" x=\"%lf\" y=\"%lf\" stroke=\"white\" fill=\"white\" text-anchor=\"middle\" alignment-baseline=\"middle\" font-size=\"8\">I</text>\n",pontoGetX(inicio),pontoGetY(inicio));
    svgPrintCaminho(svg,caminhoMaisCurto, corCurto, 1);

    fprintf(svg,"<circle id=\"fim\" r=\"7\" cx=\"%lf\" cy=\"%lf\" stroke-width=\"1px\" stroke=\"black\" fill=\"black\" fill-opacity=\"0.7\"/>\n",pontoGetX(destino),pontoGetY(destino));
    fprintf(svg,"<text id=\"inicio-t\" x=\"%lf\" y=\"%lf\" stroke=\"white\" fill=\"white\" text-anchor=\"middle\" alignment-baseline=\"middle\" font-size=\"8\">F</text>\n",pontoGetX(destino),pontoGetY(destino));
    fclose(svg);
    freeLista2(caminhoMaisCurto);
    freeMST(ciclovias);
    freeMST(agm);
}

void _qryBf(Grafo ruas, List qryFigures, FILE *txt, Vertice origem, Vertice destino, Quadra quadra, char face, int qtd){
    double x = quadraGetX(quadra), y = quadraGetY(quadra), w = quadraGetW(quadra), h = quadraGetH(quadra);
    Line line;
    Generic generic;

    // Cria a linha que indica qual a face da quadra que passou do limite
    if(face == 'S'){
        line = createLine(x,y-3,x+w,y-3,"1px","red");
        generic = createGeneric("linha",line,freeLine,NULL);
        listInsert(qryFigures,generic);
    }else if(face == 'N'){
        line = createLine(x,y+h+3,x+w,y+h+3,"1px","red");
        generic = createGeneric("linha",line,freeLine,NULL);
        listInsert(qryFigures,generic);

    }else if(face =='L'){
        line = createLine(x-3,y,x-3,y+h,"1px","red");
        generic = createGeneric("linha",line,freeLine,NULL);
        listInsert(qryFigures,generic);

    }else if(face == 'O'){
        line = createLine(x+w+3,y,x+w+3,y+h,"1px","red");
        generic = createGeneric("linha",line,freeLine,NULL);
        listInsert(qryFigures,generic);
    }

    grafoRemoveAresta(ruas,grafoVerticeGetId(origem),grafoVerticeGetId(destino),freeRua);

}

void qryBf(Grafo ruas, int max, List qryFigures, FILE *txt){
    int qtdVertices = grafoGetQtdVertices(ruas);
    Vertice *vertices = grafoGetVertices(ruas);

    Quadra quadraDireita, quadraEsquerda;
    List arestas;
    Node aux;
    Vertice v1, v2;
    Aresta aresta;
    Rua rua;
    int orientacao;
    int casosLadoDireito, casosLadoEsquerdo;
    
    for(int i=0; i<qtdVertices; i++){
        arestas =  grafoVerticeGetAdjacencias(vertices[i]);
        aux = listGetFirst(arestas);

        while(aux){
            aresta = nodeGetData(aux);
            rua = grafoArestaGetData(aresta);
            orientacao = grafoArestaGetOrientacao(aresta);

            quadraDireita = ruaGetQuadraDireita(rua);
            quadraEsquerda = ruaGetQuadraEsquerda(rua);
            v1 = grafoArestaGetInicio(aresta);
            v2 = grafoArestaGetFim(aresta);
            casosLadoDireito = 0;
            casosLadoEsquerdo = 0;

            aux = nodeGetNext(aux);

            if(orientacao == 1){ // sul
                if(quadraDireita != NULL) casosLadoDireito = quadraGetCasos(quadraDireita, 'L');

                if(quadraEsquerda != NULL) casosLadoEsquerdo = quadraGetCasos(quadraEsquerda, 'O');

                if(casosLadoDireito > max) _qryBf(ruas,qryFigures,txt,v1,v2,quadraDireita,'L',casosLadoDireito);
                if(casosLadoEsquerdo > max) _qryBf(ruas,qryFigures,txt,v1,v2,quadraEsquerda,'O',casosLadoEsquerdo);

            }else if(orientacao == 2){ // norte
                if(quadraDireita != NULL) casosLadoDireito = quadraGetCasos(quadraDireita, 'O');

                if(quadraEsquerda != NULL) casosLadoEsquerdo = quadraGetCasos(quadraEsquerda, 'L');
                
                if(casosLadoDireito > max) _qryBf(ruas,qryFigures,txt,v1,v2,quadraDireita,'O',casosLadoDireito);
                if(casosLadoEsquerdo > max) _qryBf(ruas,qryFigures,txt,v1,v2,quadraEsquerda,'L',casosLadoEsquerdo);

            }else if(orientacao == 3){ // leste
                if(quadraDireita != NULL) casosLadoDireito = quadraGetCasos(quadraDireita, 'N');
                
                if(quadraEsquerda != NULL) casosLadoEsquerdo = quadraGetCasos(quadraEsquerda, 'S');

                if(casosLadoDireito > max) _qryBf(ruas,qryFigures,txt,v1,v2,quadraDireita,'N',casosLadoDireito);
                if(casosLadoEsquerdo > max) _qryBf(ruas,qryFigures,txt,v1,v2,quadraEsquerda,'S',casosLadoEsquerdo);

            }else if(orientacao == 4){ // oeste
                if(quadraDireita != NULL) casosLadoDireito = quadraGetCasos(quadraDireita, 'S');

                if(quadraEsquerda != NULL) casosLadoEsquerdo = quadraGetCasos(quadraEsquerda, 'N');

                if(casosLadoDireito > max) _qryBf(ruas,qryFigures,txt,v1,v2,quadraDireita,'S',casosLadoDireito);
                if(casosLadoEsquerdo > max) _qryBf(ruas,qryFigures,txt,v1,v2,quadraEsquerda,'N',casosLadoEsquerdo);

            }
        }
    }
}



