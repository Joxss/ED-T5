/* 
    Esse header especifica um TAD que representa um polígono e possui funções para criação, acesso das variáveis e liberação de memória desse TAD.
*/

#ifndef _H_POLIGONO
#define _H_POLIGONO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Poligono;

/* Inicializa um novo polígono. O ponteiro retornado deve ter sua memoria desalocada utilizando a funcao freePolig.
*  Parâmetros: Recebe a quantidade de pontos, e dois vetores de double representandos os valores das coordenadas x e y respectivamente
*  Retorno: Retorna o endereço do polígono criado. */ 
Poligono createPoligono(int qtd, double *x, double *y);

/* Obtem os valores x das coordenadas dos pontos de um polígono.
*  Parâmetros: Recebe um endereço não nulo para o poligono.
*  Retorno: Retorna um array de double contendo os valores de x. */
double * poligGetArrayX(Poligono p);

/* Obtem os valores y das coordenadas dos pontos de um polígono.
*  Parâmetros: Recebe um endereço não nulo para o poligono.
*  Retorno: Retorna um array de double contendo os valores de x. */
double * poligGetArrayY(Poligono p);

/* Obtem o valor x da coordenada do centroide de um polígono.
*  Parâmetros: Recebe um endereço não nulo para o poligono.
*  Retorno: Retorna um double contendo o valor x do centroide. */
double poligGetXc(Poligono p);

/* Obtem o valor y da coordenada do centroide de um polígono.
*  Parâmetros: Recebe um endereço não nulo para o poligono.
*  Retorno: Retorna um double contendo o valor y do centroide. */
double poligGetYc(Poligono p);

/* Obtem a área de um polígono.
*  Parâmetros: Recebe um endereço não nulo para o poligono.
*  Retorno: Retorna um double contendo a área. */
double poligGetArea(Poligono p);

/* Obtem a quantidade de pontos de um polígono.
*  Parâmetros: Recebe um endereço não nulo para o poligono.
*  Retorno: Retorna um inteiro contendo a quantidade de pontos. */
int poligGetQtd(Poligono p);

/* Obtem a cor de um polígono.
*  Parâmetros: Recebe um endereço não nulo para o poligono.
*  Retorno: Retorna uma string contendo a cor do polígono. */
char * poligGetCor(Poligono p);

/* Atualiza a cor de um polígono.
*  Parâmetros: Recebe um endereço não nulo para o poligono e uma string contendo a cor desejada.
*  Retorno: Não possui retorno. */
void poligSetCor(Poligono p, char *preench);

/* Desaloca a memória de um polígono.
*  Parâmetros: Recebe um endereço não nulo para o poligono.
*  Retorno: Não possui retorno. */
void freePolig(Poligono p);

#endif