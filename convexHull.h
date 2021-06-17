/* 
    Esse header possui funções que auxiliam na realização das qrys ci e soc definidas na terceira parte do trabalho.
*/

#ifndef _H_CONVEXHULL
#define _H_CONVEXHULL

#include "list.h"
#include "QuadTree.h"

/* Desaloca a memória de um array
*  Parâmetros: Recebe um ponteiro para o começo do array e a quantidade de elementos do array
*  Retorno: Não possui retorno. */ 
void freeArray(Ponto arr[], int n);

/* Calcula a envoltória convexa de uma lista de elementos que possuem coordenadas.
*  Parâmetros: Recebe uma lista com os elementos e a quantidade de elementos nessa lista por referencia.
               A variavel que representa a quantidade de elementos é alterada durante a execucao da funcao para representar a quantidade de elementos do vetor retornado.
*  Retorno: Retorna um vetor contendo apenas os elementos que formam a envoltoria convexa se possivel, caso contrario retorna NULL.
            O vetor retornado deve apenas desalocar a memória do vetor, sem desalocar a memoria de elementos dentro dele */ 
Generic *convexHull(List l, int* arraySize);

/* Checa se um posto esta contido em um poligono. A funcao opera recursivamento ate achar um posto que esteja contido ou acabarem os postos.
*  Parâmetros: Recebe um elemento do tipo QuadNode que contem o posto e um ponteiro para uma estrutura que representa o poligono
*  Retorno: Retorna 1 se a funcao encontrar um posto dentro do poligono e 0 caso contrario. */ 
int postosSaudeInsPolig(QuadNode covid, Poligono polig);

/* Encontra os k pontos mais proximos de um determinado ponto
*  Parâmetros: Recebe uma Quadtree contendo os postos e um inteiro que representa a quantidade k postos a serem ordenados,
               o ponto referência e um endereço de um inteiro n que representa a quantidade de pontos selecionados.
*  Retorno: Se houverem pontos na quadtree retorna um vetor de pontos com os n pontos mais proximos, caso contrário retorna NULL. */ 
Ponto * shellSortParcial(QuadTree postos, int k, Ponto endereco, int *n);

int pointInsPolig(Poligono polig, Ponto p);

#endif