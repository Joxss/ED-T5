/* 
    Esse header especifica um TAD que representa um círculo e possui funçoes para criacao, desalocamento e acesso das variáveis desse TAD.
*/

#ifndef _H_CIRCULO
#define _H_CIRCULO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto.h"

typedef void *Circ;

/* Inicializa um novo círculo. O ponteiro retornado deve ter sua memoria desalocada utilizando a funcao freeCircle.
*  Parâmetros: recebe uma string contendo o id, variáveis double contendo x, y, e r, e strings contendo a expressura da borda, a cor da borda e a cor do preenchimento (as string precisam ter tamanho <= 20).
*  Retorno: retorna um ponteiro para o circulo criado. */
Circ createCircle(char id[], double x, double y, double r, char borda[], char corBorda[], char corPreench[]);

/* Obtem o id de um círculo.
*  Parâmetros: Recebe um ponteiro não nulo para o círculo.
*  Retorno: Retorna uma string contendo o id do círculo. */
char *circGetId(Circ c);

/* Obtem a expressura da borda de um círculo.
*  Parâmetros: Recebe um ponteiro não nulo para o círculo.
*  Retorno: Retorna uma string contendo a expressura da borda do círculo. */
char *circGetBorda(Circ c);

/* Obtem a cor da borda de um círculo.
*  Parâmetros: Recebe um ponteiro não nulo para o círculo.
*  Retorno: Retorna uma string contendo a cor da borda do círculo. */
char *circGetCorBorda(Circ c);

/* Obtem a cor de preenchimento de um círculo.
*  Parâmetros: Recebe um ponteiro não nulo para o círculo.
*  Retorno: Retorna uma string contendo a cor de preenchimento do círculo. */
char *circGetCorPreench(Circ c);

/* Obtém um ponteiro de um Ponto contendo as coordenada xy do círculo.
*  Parâmetros: Recebe um ponteiro não nulo para o círculo.
*  Retorno: Retorna uma ponteiro para o Ponto. */
Ponto circGetPonto(Circ c);

/* Obtem a coordenada x do circulo especificado
*  Parâmetros: Recebe um ponteiro não nulo para um círculo
*  Retorno: Retorna um double representando a coordenada x do círculo. */ 
double circGetX(Circ c);

/* Obtem a coordenada y do circulo especificado
*  Parâmetros: Recebe um ponteiro não nulo para um círculo
*  Retorno: retorna um double representando a coordenada y do círculo. */ 
double circGetY(Circ c);

/* Obtem o raio do circulo especificado
*  Parâmetros: Recebe um ponteiro não nulo para um círculo
*  Retorno: retorna um double representando o raio do círculo. */ 
double circGetR(Circ c);

/* Define a cor da borda do circulo especificado
*  Parâmetros: Recebe um ponteiro não nulo para um circulo e uma string de tamanho para a cor da borda
*  Retorno: Não possui retorno */ 
void circSetCorBorda(Circ c, char corBorda[]);

/* Define a cor do preenchimento do circulo especificado
*  Parâmetros: Recebe um ponteiro não nulo para um circulo e uma string de tamanho para a cor do preenchimento
*  Retorno: Não possui retorno */  
void circSetCorPreench(Circ c, char corPreench[]);

/* Desaloca a memória de um circulo
*  Parâmetros: Recebe um ponteiro não nulo para o circulo
*  Retorno: Nao possui retorno*/
void freeCircle(Circ c);

#endif