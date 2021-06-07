/* 
    Esse header especifica um TAD que representa um retângulo e possui funções para criação e acesso das variáveis desse TAD.
*/

#ifndef _H_RECT
#define _H_RECT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto.h"

typedef void *Rect;

/* Inicializa um novo retângulo. O ponteiro retornado deve ter sua memoria desalocada utilizando a funcao freeRect.
*  Parâmetros: recebe uma string contendo o id, variáveis double contendo x, y, w e r e strings contendo a expressura da borda, a cor da borda e a cor do preenchimento (as string precisam ter tamanho <= 20).
*  Retorno: Retorna um ponteiro para o retângulo criado. */
Rect createRect(char id[], double x, double y, double w, double h, char borda[], char corBorda[], char corPreench[]);

/* Obtém um ponteiro de um Ponto contendo as coordenada xy do retangulo.
*  Parâmetros: Recebe um ponteiro não nulo para o retângulo.
*  Retorno: Retorna uma ponteiro para o Ponto. 
*/
Ponto rectGetPonto(Rect r);

/* Obtem o id de um retângulo.
*  Parâmetros: Recebe um ponteiro não nulo para o retângulo.
*  Retorno: Retorna uma string contendo o id do retângulo. */
char *rectGetId(Rect r);

/* Obtem a expressura da borda de um retângulo.
*  Parâmetros: Recebe um ponteiro não nulo para o retângulo.
*  Retorno: Retorna uma string contendo a expressura da borda do retângulo. */
char *rectGetBorda(Rect r);

/* Obtem a cor da borda de um retângulo.
*  Parâmetros: Recebe um ponteiro não nulo para o retângulo.
*  Retorno: Retorna uma string contendo a cor da borda do retângulo. */
char *rectGetCorBorda(Rect r);

/* Obtem a cor de preenchimento de um retângulo.
*  Parâmetros: Recebe um ponteiro não nulo para o retângulo.
*  Retorno: Retorna uma string contendo a cor de preenchimento do retângulo. */
char *rectGetCorPreench(Rect r);

/* Obtem a coordenada x do retângulo especificado
*  Parâmetros: Recebe um ponteiro não nulo para o retângulo.
*  Retorno: retorna um double representando a coordenada x do retângulo. */
double rectGetX(Rect r);

/* Obtem a coordenada y do retângulo especificado
*  Parâmetros: Recebe um ponteiro não nulo para o retângulo.
*  Retorno: retorna um double representando a coordenada y do retângulo. */
double rectGetY(Rect r);

/* Obtem a largura do retângulo especificado
*  Parâmetros: Recebe um ponteiro não nulo para o retângulo.
*  Retorno: retorna um double representando a largura do retângulo. */ 
double rectGetW(Rect r);

/* Obtem a altura do retângulo especificado
*  Parâmetros: Recebe um ponteiro não nulo para o retângulo.
*  Retorno: retorna um double representando a altura do retângulo. */ 
double rectGetH(Rect r);


/* Obtem a coordenada x do centro de massa do retângulo especificado.
*  Parâmetros: Recebe ponteiro não nulo para o retângulo.
*  Retorno: Retorna um double com o valor da coordenada x do centro de massa. */ 
double rectGetXc(Rect r);


/* Obtem a coordenada y do centro de massa do retângulo especificado.
*  Parâmetros: Recebe ponteiro não nulo para o retângulo.
*  Retorno: Retorna um double com o valor da coordenada y do centro de massa. */ 
double rectGetYc(Rect r);

/* Define a cor da borda para o retângulo especificado.
*  Parâmetros: Recebe ponteiro não nulo para o retângulo e uma string para a cor da borda.
*  Retorno: Não possui retorno */ 
void rectSetCorBorda(Rect r, char corBorda[]);

/* Define a cor do preenchimento para o retângulo especificado.
*  Parâmetros: Recebe ponteiro não nulo para o retângulo e uma string para a cor do preenchimento.
*  Retorno: Não possui retorno */
void rectSetCorPreench(Rect r, char corPreench[]);

/* Desaloca a memória de um retângulo
*  Parâmetros: Recebe um ponteiro não nulo para o retângulo
*  Retorno: Não possui retorno*/
void freeRect(Rect r);

#endif