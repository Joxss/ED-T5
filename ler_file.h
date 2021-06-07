/* 
    Esse header possui duas funções que lidam respectivamente com a leitura do arquivo .geo e .qry.
*/

#ifndef _H_LER_FILE
#define _H_LER_FILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "list.h"
#include "qry.h"
#include "QuadTree.h"
#include "hashTable.h"
#include "chaveXvalor.h"
#include "grafo.h"

/* Lê todas as linhas de um arquivo .geo e armazena cada elemento em sua respectiva quadtree.
*  Parâmetros: Recebe um vetor de quadtrees contendo ponteiros nao nulos para as quadtrees: circulos, retangulos, textos, quadras, hidrantes, semaforos, radios, postos, regioes, 
               e um ponteiro nao nulo para a hashtable cepXquadra
               Recebe também uma string contendo o diretório do arquivo .geo.
*  Retorno: Não possui retorno. */
void leGeo(QuadTree *trees, Htable cepXQuadra,char input[]);

/* Lê todas as linhas de um arquivo .qry e executa as funções respectivas de cada qry.
*  Parâmetros: Recebe um vetor de quadtrees contendo ponteiros nao nulos para as quadtrees: circulos, retangulos, textos, quadras, hidrantes, semaforos, radios, postos, regioes, 
               um ponteiro nao nulo para a lista de elemento criados por qrys, 
               e ponteiros nao nulos para as hash tables cpfXpessoa, tipoXdescricao, cpfXcep, cepXquadra, 
               Recebe tambem um ponteiro nao nulo para os diretorios dos arquivos de entrada e saida.
*  Retorno: Não possui retorno. */
void leQry(QuadTree *trees, List qryFigures, Htable cpfXpessoa, Htable tipoXdescricao, Htable cpfXcep, Htable cepXquadra, Diretorios dir);

/* Lê todas as linhas de um arquivo .ec e armazena cada elemento em sua respectiva quadtree.
*  Parâmetros: Recebe ponteiros não nulos para as quadtrees de quadras e estabelecimentos, um ponteiro nao nulo para a hash table tipoXdescricao dos estabelecimentos. 
               Recebe também uma string contendo o diretorio do arquivo .ec.
*  Retorno: Não possui retorno. */
void leEc(QuadTree quadras, QuadTree estabelecimentos, Htable tipoXdescricao, char input[]);

/* Lê todas as linhas de um arquivo .pm e armazena cada elemento em sua respectiva quadtree
*  Parâmetros: Recebe ponteiros não nulos para as quadtrees de quadras e moradores, e ponteiros nao nulos para as hash tables de cpfXpessoa e cpfXcep. 
               Recebe também uma string contendo o diretorio do arquivo .pm.
*  Retorno: Não possui retorno. */
void lePm(QuadTree quadras, QuadTree moradores, Htable cpfXpessoa, Htable cpfXcep, char input[]);

void leVia(Htable cepXquadra, QuadTree vertices, Grafo ruas, char input[]);

int getQtdVerticesVia(char input[]);

#endif