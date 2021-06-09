#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ler_file.h"
#include "args.h"
#include "svg.h"
#include "qry.h"
#include "convexHull.h"
#include "morador.h"
#include "grafo.h"
#include "rua.h"


// int main(int argc, char *argv[]){
//     // Diretorios dir = defineArgs(argc,argv);
//     // if(getPathVia(dir) != NULL){
//     //     printf("DIRETORIO DO MAPA VIARIO: %s\n",getPathVia(dir));
//     //     printf("quantidade de vertices: %d\n\n",getQtdVerticesVia(getPathVia(dir)));
//     // }

//     Quadra quadra = createQuadra("id",0.0,0.0,0.0,0.0,"2px","blacl","black");

//     Grafo g = createGrafo(10);

//     Ponto p = createPoint(0,100);
//     grafoInsereVertice(g,"vertice0",p);

//     p = createPoint(125,0);
//     grafoInsereVertice(g,"vertice1",p);

//     p = createPoint(250,0);
//     grafoInsereVertice(g,"vertice2",p);

//     p = createPoint(375,0);
//     grafoInsereVertice(g,"vertice3",p);

//     p = createPoint(500,100);
//     grafoInsereVertice(g,"vertice4",p);

//     p = createPoint(375,200);
//     grafoInsereVertice(g,"vertice5",p);

//     p = createPoint(250,200);
//     grafoInsereVertice(g,"vertice6",p);

//     p = createPoint(125,200);
//     grafoInsereVertice(g,"vertice7",p);

//     p = createPoint(250,100);
//     grafoInsereVertice(g,"vertice8",p);

//     Rua r = createRua("nomedarua",quadra,quadra,4.5,4.5);
//     grafoInsereAresta(g,"vertice0","vertice1",r);
//     // r = createRua("nomedarua",quadra,quadra,4.5,4.5);
//     // grafoInsereAresta(g,"vertice1","vertice0",r);
    
//     r = createRua("nomedarua",quadra,quadra,8.5,8.5);
//     grafoInsereAresta(g,"vertice0","vertice7",r);
//     // r = createRua("nomedarua",quadra,quadra,8.5,8.5);
//     // grafoInsereAresta(g,"vertice7","vertice0",r);

//     r = createRua("nomedarua",quadra,quadra,11.5,11.5);
//     grafoInsereAresta(g,"vertice1","vertice7",r);
//     // r = createRua("nomedarua",quadra,quadra,11.5,11.5);
//     // grafoInsereAresta(g,"vertice7","vertice1",r);
    
//     r = createRua("nomedarua",quadra,quadra,8.5,8.5);
//     grafoInsereAresta(g,"vertice1","vertice2",r);
//     // r = createRua("nomedarua",quadra,quadra,8.5,8.5);
//     // grafoInsereAresta(g,"vertice2","vertice1",r);

//     r = createRua("nomedarua",quadra,quadra,7.5,7.5);
//     grafoInsereAresta(g,"vertice2","vertice3",r);
//     // r = createRua("nomedarua",quadra,quadra,7.5,7.5);
//     // grafoInsereAresta(g,"vertice3","vertice2",r);
    
//     r = createRua("nomedarua",quadra,quadra,4.5,4.5);
//     grafoInsereAresta(g,"vertice2","vertice5",r);
//     // r = createRua("nomedarua",quadra,quadra,4.5,4.5);
//     // grafoInsereAresta(g,"vertice5","vertice2",r);
    
//     r = createRua("nomedarua",quadra,quadra,2.5,2.5);
//     grafoInsereAresta(g,"vertice2","vertice8",r);
//     // r = createRua("nomedarua",quadra,quadra,2.5,2.5);
//     // grafoInsereAresta(g,"vertice8","vertice2",r);
    
//     r = createRua("nomedarua",quadra,quadra,9.5,9.5);
//     grafoInsereAresta(g,"vertice3","vertice4",r);
//     // r = createRua("nomedarua",quadra,quadra,9.5,9.5);
//     // grafoInsereAresta(g,"vertice4","vertice3",r);
    
//     r = createRua("nomedarua",quadra,quadra,14.5,14.5);
//     grafoInsereAresta(g,"vertice3","vertice5",r);
//     // r = createRua("nomedarua",quadra,quadra,14.5,14.5);
//     // grafoInsereAresta(g,"vertice5","vertice3",r);

//     r = createRua("nomedarua",quadra,quadra,10.5,10.5);
//     grafoInsereAresta(g,"vertice4","vertice5",r);
//     // r = createRua("nomedarua",quadra,quadra,10.5,10.5);
//     // grafoInsereAresta(g,"vertice5","vertice4",r);

//     r = createRua("nomedarua",quadra,quadra,2.5,2.5);
//     grafoInsereAresta(g,"vertice5","vertice6",r);
//     // r = createRua("nomedarua",quadra,quadra,2.5,2.5);
//     // grafoInsereAresta(g,"vertice6","vertice5",r);

//     r = createRua("nomedarua",quadra,quadra,1.5,1.5);
//     grafoInsereAresta(g,"vertice6","vertice7",r);
//     // r = createRua("nomedarua",quadra,quadra,1.5,1.5);
//     // grafoInsereAresta(g,"vertice7","vertice6",r);
    
//     r = createRua("nomedarua",quadra,quadra,6.5,6.5);
//     grafoInsereAresta(g,"vertice6","vertice8",r);
//     // r = createRua("nomedarua",quadra,quadra,6.5,6.5);
//     // grafoInsereAresta(g,"vertice8","vertice6",r);

//     r = createRua("nomedarua",quadra,quadra,7.5,7.5);
//     grafoInsereAresta(g,"vertice7","vertice8",r);
//     // r = createRua("nomedarua",quadra,quadra,7.5,7.5);
//     // grafoInsereAresta(g,"vertice8","vertice7",r);

//     //printGrafo(g);

//     //printf("%d\n",grafoExisteAresta(g,"vertice7","vertice8"));
//     //grafoRemoveAresta(g,"vertice0","vertice7",freePonto);
//     //printGrafo(g);
//     //getIndexes(g);

//     // double *dist = dijkstra(g,"vertice3",ruaGetVelocidadeMedia);
//     // for(int i=0; i<9; i++){
//     //     printf("%d até %d: %lf\n",3,i, dist[i]);
//     // }
//     // free(dist);
//     Grafo naoDirecioado = copiaParaNaoDirecionado(g);
//     Grafo mst = primMST(g,ruaGetDistancia);

//     FILE *svg = fopen("./casos-teste/testes-svg/grafo-teste.svg","w");
//     fprintf(svg,"<svg>\n");
//     svgPrintGrafo(svg, g, 0);
//     svgPrintGrafo(svg, mst, 1);
//     fprintf(svg,"</svg>");
//     fclose(svg);

//     // printGrafo(mst);

//     freeGrafo(g,freePonto,freeRua);
//     freeMST(naoDirecioado);
//     freeMST(mst);
//     freeQuadra(quadra);


//     //deleteDir(dir);
    
// }

int main(int argc, char *argv[]){

    Diretorios dir = defineArgs(argc,argv);

    Htable tipoXdescricao = createHashTable(100);
    Htable cpfXpessoa = createHashTable(100);
    Htable cpfXcep = createHashTable(100);
    Htable cepXquadra = createHashTable(100);

    Grafo ruas = createGrafo(getQtdVerticesVia(getPathVia(dir)));
    QuadTree vertices = createQuadTree(verticeGetId);

    QuadTree trees[12];

    trees[0] = createQuadTree(circGetId); //circulos
    trees[1] = createQuadTree(rectGetId); //retangulos
    trees[2] = createQuadTree(textGetId); //textos
    trees[3] = createQuadTree(quadraGetCep); //quadras
    trees[4] = createQuadTree(circGetId); //hidrantes
    trees[5] = createQuadTree(circGetId); //semaforos
    trees[6] = createQuadTree(circGetId); //radios
    trees[7] = createQuadTree(QuadGetId); //postos
    trees[8] = createQuadTree(QuadGetId); //densidades
    trees[9] = createQuadTree(QuadGetId); //casosCv
    trees[10] = createQuadTree(moradorGetCpf); //moradores
    trees[11] = createQuadTree(estabelecimentoGetCnpj); //estabelecimentos

    leGeo(trees, cepXquadra, getPathGeo(dir));

    if(getPathPM(dir) != NULL){
        lePm(trees[3], trees[10], cpfXpessoa, cpfXcep, getPathPM(dir));
        
        if(getPathEC(dir) != NULL){ 
            leEc(trees[3], trees[11],tipoXdescricao, getPathEC(dir));
        }
    }

    if(getPathVia(dir) != NULL){
        leVia(cepXquadra,vertices,ruas,getPathVia(dir));
    }

    // // printf("%s",getPathSvg(dir));
    svgOpenTag(getPathSvg(dir));
    FILE *svg = fopen(getPathSvg(dir),"a");

    QtPercorreProfundidade(trees[0],svgSelectTag,(void*)svg);
    QtPercorreProfundidade(trees[1],svgSelectTag,(void*)svg);
    QtPercorreProfundidade(trees[2],svgSelectTag,(void*)svg);
    QtPercorreProfundidade(trees[3],svgSelectTag,(void*)svg);
    QtPercorreProfundidade(trees[4],svgSelectTag,(void*)svg);
    QtPercorreProfundidade(trees[5],svgSelectTag,(void*)svg);
    QtPercorreProfundidade(trees[6],svgSelectTag,(void*)svg);
    QtPercorreProfundidade(trees[7],svgSelectTag,(void*)svg);
    fclose(svg);
    
    svgCloseTag(getPathSvg(dir));


    if(getPathQry(dir)!=NULL){
        List qryFigures = createLista();

        leQry(ruas, trees, qryFigures, cpfXpessoa, tipoXdescricao, cpfXcep, cepXquadra, dir);

        svgOpenTag(getPathSvgQry(dir));

        FILE *svgQry = fopen(getPathSvgQry(dir),"a");
        QtPercorreProfundidade(trees[0],svgSelectTag,(void*)svgQry);
        QtPercorreProfundidade(trees[1],svgSelectTag,(void*)svgQry);
        QtPercorreProfundidade(trees[2],svgSelectTag,(void*)svgQry);
        QtPercorreProfundidade(trees[3],svgSelectTag,(void*)svgQry);
        QtPercorreProfundidade(trees[4],svgSelectTag,(void*)svgQry);
        QtPercorreProfundidade(trees[5],svgSelectTag,(void*)svgQry);
        QtPercorreProfundidade(trees[6],svgSelectTag,(void*)svgQry);
        QtPercorreProfundidade(trees[7],svgSelectTag,(void*)svgQry);
        QtPercorreProfundidade(trees[9],svgSelectTag,(void*)svgQry);
        fclose(svgQry);
        svgPrintList(qryFigures, getPathSvgQry(dir));

        svgCloseTag(getPathSvgQry(dir));

        freeLista(qryFigures,freeGeneric);
    }

    freeHashTable(tipoXdescricao,free);
    freeHashTable(cpfXpessoa,freePessoa);
    freeHashTable(cpfXcep,free);
    freeHashTable2(cepXquadra);

    freeQt(trees[0],freeGeneric);
    freeQt(trees[1],freeGeneric);
    freeQt(trees[2],freeGeneric);
    freeQt(trees[3],freeGeneric);
    freeQt(trees[4],freeGeneric);
    freeQt(trees[5],freeGeneric);
    freeQt(trees[6],freeGeneric);
    freeQt(trees[7],freeGeneric);
    freeQt(trees[8],freeGeneric);
    freeQt(trees[9],freeGeneric);
    freeQt(trees[10],freeGeneric);
    freeQt(trees[11],freeGeneric);

    printf("asdasdasdasdasd   -- - - --  %d\n",QtGetLenght(vertices));

    freeGrafo(ruas,freePonto,freeRua);
    freeQt2(vertices);

    deleteDir(dir);
}