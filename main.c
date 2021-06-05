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


int main(int argc, char *argv[]){
    Grafo g = createGrafo(10);

    Ponto p = createPoint(21,21);
    grafoInsereVertice(g,"vertice0",p);

    p = createPoint(1,1);
    grafoInsereVertice(g,"vertice1",p);

    p = createPoint(21,21);
    grafoInsereVertice(g,"vertice2",p);

    p = createPoint(21,21);
    grafoInsereVertice(g,"vertice3",p);

    p = createPoint(21,21);
    grafoInsereVertice(g,"vertice4",p);

    p = createPoint(21,21);
    grafoInsereVertice(g,"vertice5",p);

    p = createPoint(21,21);
    grafoInsereVertice(g,"vertice6",p);

    p = createPoint(21,21);
    grafoInsereVertice(g,"vertice7",p);

    p = createPoint(21,21);
    grafoInsereVertice(g,"vertice8",p);

    Rua r = createRua("nomedarua","cepdireita","cepesquerda",4.5,4.5);
    grafoInsereAresta(g,"vertice0","vertice1",r,4.5,4.5);
    r = createRua("nomedarua","cepdireita","cepesquerda",8.5,8.5);
    grafoInsereAresta(g,"vertice0","vertice7",r,8.5,8.5);

    r = createRua("nomedarua","cepdireita","cepesquerda",11.5,11.5);
    grafoInsereAresta(g,"vertice1","vertice7",r,11.5,11.5);
    r = createRua("nomedarua","cepdireita","cepesquerda",8.5,8.5);
    grafoInsereAresta(g,"vertice1","vertice2",r,8.5,8.5);

    r = createRua("nomedarua","cepdireita","cepesquerda",7.5,7.5);
    grafoInsereAresta(g,"vertice2","vertice3",r,7.5,7.5);
    r = createRua("nomedarua","cepdireita","cepesquerda",4.5,4.5);
    grafoInsereAresta(g,"vertice2","vertice5",r,4.5,4.5);
    r = createRua("nomedarua","cepdireita","cepesquerda",2.5,2.5);
    grafoInsereAresta(g,"vertice2","vertice8",r,2.5,2.5);
    
    r = createRua("nomedarua","cepdireita","cepesquerda",9.5,9.5);
    grafoInsereAresta(g,"vertice3","vertice4",r,9.5,9.5);
    r = createRua("nomedarua","cepdireita","cepesquerda",14.5,14.5);
    grafoInsereAresta(g,"vertice3","vertice5",r,14.5,14.5);

    r = createRua("nomedarua","cepdireita","cepesquerda",10.5,10.5);
    grafoInsereAresta(g,"vertice4","vertice5",r,10.5,10.5);

    r = createRua("nomedarua","cepdireita","cepesquerda",2.5,2.5);
    grafoInsereAresta(g,"vertice5","vertice6",r,2.5,2.5);

    r = createRua("nomedarua","cepdireita","cepesquerda",1.5,1.5);
    grafoInsereAresta(g,"vertice6","vertice7",r,1.5,1.5);
    r = createRua("nomedarua","cepdireita","cepesquerda",6.5,6.5);
    grafoInsereAresta(g,"vertice6","vertice8",r,6.5,6.5);

    r = createRua("nomedarua","cepdireita","cepesquerda",7.5,7.5);
    grafoInsereAresta(g,"vertice7","vertice8",r,7.5,7.5);

    //printf("%d\n",grafoExisteAresta(g,"vertice7","vertice8"));
    //grafoRemoveAresta(g,"vertice0","vertice7",freePonto);
    //printGrafo(g);
    //getIndexes(g);

    double *dist = dijkstra(g,"vertice3",ruaGetVelocidadeMedia);
    for(int i=0; i<9; i++){
        printf("%d até %d: %lf\n",3,i, dist[i]);
    }
    free(dist);

    freeGrafo(g,freePonto,freeRua);
    
}

// int main(int argc, char *argv[]){

//     Diretorios dir = defineArgs(argc,argv);

//     Htable tipoXdescricao = createHashTable(100);
//     Htable cpfXpessoa = createHashTable(100);
//     Htable cpfXcep = createHashTable(100);
//     Htable cepXquadra = createHashTable(100);

//     QuadTree trees[12];

//     trees[0] = createQuadTree(circGetId); //circulos
//     trees[1] = createQuadTree(rectGetId); //retangulos
//     trees[2] = createQuadTree(textGetId); //textos
    
//     trees[3] = createQuadTree(quadraGetCep); //quadras
//     trees[4] = createQuadTree(circGetId); //hidrantes
//     trees[5] = createQuadTree(circGetId); //semaforos
//     trees[6] = createQuadTree(circGetId); //radios
//     trees[7] = createQuadTree(QuadGetId); //postos
//     trees[8] = createQuadTree(QuadGetId); //densidades
//     trees[9] = createQuadTree(QuadGetId); //casosCv
//     trees[10] = createQuadTree(moradorGetCpf); //moradores
//     trees[11] = createQuadTree(estabelecimentoGetCnpj); //estabelecimentos

//     leGeo(trees, cepXquadra, getPathGeo(dir));

//     if(getPathPM(dir) != NULL){
//         lePm(trees[3], trees[10], cpfXpessoa, cpfXcep, getPathPM(dir));
        
//         if(getPathEC(dir) != NULL){ 
//             leEc(trees[3], trees[11],tipoXdescricao, getPathEC(dir));
//         }
//     }

//     // // printf("%s",getPathSvg(dir));
//     svgOpenTag(getPathSvg(dir));
//     FILE *svg = fopen(getPathSvg(dir),"a");

//     QtPercorreProfundidade(trees[0],svgSelectTag,(void*)svg);
//     QtPercorreProfundidade(trees[1],svgSelectTag,(void*)svg);
//     QtPercorreProfundidade(trees[2],svgSelectTag,(void*)svg);
//     QtPercorreProfundidade(trees[3],svgSelectTag,(void*)svg);
//     QtPercorreProfundidade(trees[4],svgSelectTag,(void*)svg);
//     QtPercorreProfundidade(trees[5],svgSelectTag,(void*)svg);
//     QtPercorreProfundidade(trees[6],svgSelectTag,(void*)svg);
//     QtPercorreProfundidade(trees[7],svgSelectTag,(void*)svg);
//     fclose(svg);
    
//     svgCloseTag(getPathSvg(dir));


//     if(getPathQry(dir)!=NULL){
//         List qryFigures = createLista();

//         leQry(trees, qryFigures, cpfXpessoa, tipoXdescricao, cpfXcep, cepXquadra, dir);

//         svgOpenTag(getPathSvgQry(dir));

//         FILE *svgQry = fopen(getPathSvgQry(dir),"a");
//         QtPercorreProfundidade(trees[0],svgSelectTag,(void*)svgQry);
//         QtPercorreProfundidade(trees[1],svgSelectTag,(void*)svgQry);
//         QtPercorreProfundidade(trees[2],svgSelectTag,(void*)svgQry);
//         QtPercorreProfundidade(trees[3],svgSelectTag,(void*)svgQry);
//         QtPercorreProfundidade(trees[4],svgSelectTag,(void*)svgQry);
//         QtPercorreProfundidade(trees[5],svgSelectTag,(void*)svgQry);
//         QtPercorreProfundidade(trees[6],svgSelectTag,(void*)svgQry);
//         QtPercorreProfundidade(trees[7],svgSelectTag,(void*)svgQry);
//         QtPercorreProfundidade(trees[9],svgSelectTag,(void*)svgQry);
//         fclose(svgQry);
//         svgPrintList(qryFigures, getPathSvgQry(dir));

//         svgCloseTag(getPathSvgQry(dir));

//         freeLista(qryFigures,freeGeneric);
//     }

//     freeHashTable(tipoXdescricao,free);
//     freeHashTable(cpfXpessoa,freePessoa);
//     freeHashTable(cpfXcep,free);
//     freeHashTable2(cepXquadra);

//     freeQt(trees[0],freeGeneric);
//     freeQt(trees[1],freeGeneric);
//     freeQt(trees[2],freeGeneric);
//     freeQt(trees[3],freeGeneric);
//     freeQt(trees[4],freeGeneric);
//     freeQt(trees[5],freeGeneric);
//     freeQt(trees[6],freeGeneric);
//     freeQt(trees[7],freeGeneric);
//     freeQt(trees[8],freeGeneric);
//     freeQt(trees[9],freeGeneric);
//     freeQt(trees[10],freeGeneric);
//     freeQt(trees[11],freeGeneric);

//     deleteDir(dir);
// }