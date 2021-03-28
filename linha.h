/* 
    Esse header especifica um TAD que representa uma linha e possui funções para criação e acesso das variáveis desse TAD.
*/

#ifndef LINHA_H
#define LINHA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto.h"


typedef void *Line;

/* Inicializa uma nova linha. O ponteiro retornado deve ter sua memoria desalocada utilizando a funcao freeLine
*  Parâmetros: Recebe variáveis double contendo x1, y1, x2, y2, e strings contendo a expressura da borda, a cor da borda (as string precisam ter tamanho <= 20).
*  Retorno: retorna um ponteiro para a linha criada. */
Line createLine(double x1, double y1, double x2, double y2, char borda[], char corBorda[]);

/* Obtém um ponteiro de um Ponto p1 contendo as coordenada xy da linha.
*  Parâmetros: Recebe um ponteiro não nulo para a linha.
*  Retorno: Retorna uma ponteiro para o Ponto p1. 
*/
Ponto lineGetP1(Line l);

/* Obtém um ponteiro de um Ponto p2 contendo as coordenada xy da linha.
*  Parâmetros: Recebe um ponteiro não nulo para a linha.
*  Retorno: Retorna uma ponteiro para o Ponto p2. 
*/
Ponto lineGetP2(Line l);

/* Obtem a coordenada x1 da linha especificada.
*  Parâmetros: Recebe um ponteiro não nulo para a linha.
*  Retorno: Retorna um double contendo o valor da coordenada x1.*/
double lineGetX1(Line l);

/* Obtem a coordenada x2 da linha especificada.
*  Parâmetros: Recebe um ponteiro não nulo para a linha.
*  Retorno: Retorna um double contendo o valor da coordenada x2.*/
double lineGetX2(Line l);

/* Obtem a coordenada y1 da linha especificada.
*  Parâmetros: Recebe um ponteiro não nulo para a linha.
*  Retorno: Retorna um double contendo o valor da coordenada y1.*/
double lineGetY1(Line l);

/* Obtem a coordenada y2 da linha especificada.
*  Parâmetros: Recebe um ponteiro não nulo para a linha.
*  Retorno: Retorna um double contendo o valor da coordenada y2.*/
double lineGetY2(Line l);

/* Obtem a cor da borda da linha especificada.
*  Parâmetros: Recebe um ponteiro não nulo para a linha.
*  Retorno: Retorna uma string contendo a espessura da borda da linha*/
char *lineGetBorda(Line l);

/* Obtem a coordenada y2 da linha especificada.
*  Parâmetros: Recebe um ponteiro não nulo para a linha.
*  Retorno: Retorna uma string contendo a cor da borda da linha*/
char *lineGetCorBorda(Line l);

/* Desaloca a memória de uma linha
*  Parâmetros: Recebe um ponteiro não nulo para a linha
*  Retorno: Não possui retorno*/
void freeLine(Line l);

#endif