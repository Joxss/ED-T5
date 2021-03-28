/* 
    Esse header especifica um TAD que representa um texto e possui funções para criação e acesso das variáveis desse TAD.
*/

#ifndef _H_TEXTO
#define _H_TEXTO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto.h"

typedef void *Text;

/* Inicializa um novo texto. O ponteiro retornado deve ter sua memoria desalocada utilizando a funcao freeText.
*  Parâmetros: recebe uma string contendo o id, variáveis double contendo x, y, e r, 
               e strings contendo a cor da borda e a cor do preenchimento e seu conteúdo(as string da cor precisam ter tamanho <=20 e o conteudo tamanho <= 200).
*  Retorno: retorna um tipo Text para o texto criado. */
Text createText(char id[], double x, double y, char corBorda[], char corPreench[], char str[]);

/* Obtem o id de um texto.
*  Parâmetros: Recebe um ponteiro não nulo para o texto.
*  Retorno: Retorna uma string contendo o id do texto. */
char *textGetId(Text t);

/* Obtem a cor da borda de um texto.
*  Parâmetros: Recebe um ponteiro não nulo para o texto.
*  Retorno: Retorna uma string contendo a cor da borda do texto. */
char *textGetCorBorda(Text t);

/* Obtem a cor de preenchimento de um texto.
*  Parâmetros: Recebe um ponteiro não nulo para o texto.
*  Retorno: Retorna uma string contendo a cor de preenchimento do texto. */
char *textGetCorPreench(Text t);

/* Obtem um ponteiro de um Ponto contendo as coordenada xy da texto.
*  Parâmetros: Recebe um ponteiro não nulo para o texto.
*  Retorno: Retorna um ponteiro para o elemento do tipo Ponto que guarda a coordenada do texto. */
Ponto textGetPonto(Text t);

/* Obtem a coordenada x de um texto.
*  Parâmetros: Recebe um ponteiro não nulo para o texto.
*  Retorno: Retorna um double representando a coordenada x do texto. */
double textGetX(Text t);

/* Obtem a coordenada y do texto especificado
*  Parâmetros: Recebe um ponteiro não nulo para o texto.
*  Retorno: Retorna um double representando a coordenada y do texto. */ 
double textGetY(Text t);

/* Obtem conteúdo de texto do texto especificado
*  Parâmetros: Recebe um ponteiro não nulo para o texto.
*  Retorno: Retorna um ponteiro de char para o conteúdo do texto, pode retornar NULL. */ 
char *textGetTxt(Text t);

/* Define a cor da borda do texto especificado.
*  Parâmetros: Recebe um ponteiro não nulo para o texto e uma string contendo a cor da borda.
*  Retorno: Não possui retorno. */
void textSetCorBorda(Text text, char borda[]);

/* Define a cor de preenchimento do texto especificado.
*  Parâmetros: Recebe um ponteiro não nulo para o texto e uma string contendo a cor de preenchimento.
*  Retorno: Não possui retorno. */
void textSetCorPreench(Text text, char preench[]);

/* Desaloca a memória de um texto
*  Parâmetros: Recebe um ponteiro não nulo para o texto
*  Retorno: Não possui retorno*/
void freeText(Text r);

#endif