#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ler_file.h"
#include "args.h"
#include "svg.h"
#include "qry.h"
#include "convexHull.h"
#include "morador.h"
#include <time.h>


// int main(int argc, char *argv[]){
//     char *string = malloc(sizeof(char)*7);
//     strcpy(string,"XABLAU");
//     Generic g = createGeneric("tipoEst",(void*)string,free);
//     printf("tipo: %s, string: %s",genericGetTipo(g),(char*)genericGetValores(g));
//     freeGeneric(g);
// }

int main(int argc, char *argv[]){

    Diretorios dir = defineArgs(argc,argv);

    Htable tipoXdescricao = createHashTable(100);
    Htable cpfXpessoa = createHashTable(100);
    Htable cpfXcep = createHashTable(100);
    Htable cepXquadra = createHashTable(100);

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

        leQry(trees, qryFigures, cpfXpessoa, tipoXdescricao, cpfXcep, cepXquadra, dir);

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

    freeHashTable(tipoXdescricao,freeGeneric);
    freeHashTable(cpfXpessoa,freeGeneric);
    freeHashTable(cpfXcep,freeGeneric);
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

    deleteDir(dir);
}