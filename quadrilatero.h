/* 
    Esse header especifica um TAD que representa um quadrilatero regular e possui funções para criação e acesso das variáveis desse TAD.
*/

#ifndef _H_QUADRILATERO
#define _H_QUADRILATERO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ponto.h"

typedef void *Quad;

/* Inicializa um novo quadrilatero. O ponteiro retornado deve ter sua memoria desalocada utilizando a funcao freeQuad.
*  Parâmetros: Recebe 5 doubles representando os valores de x, y, w, h  e n.
*  Retorno: retorna um ponteiro para o ponto criado. */
Quad createQuad(double x, double y, double w, double h, double n);

/* Obtem as coordenadas do Quadrilatero q.
*  Parâmetros: Recebe o void pointer de q.
*  Retorno: Retorna um ponteiro de Ponto contendo as coordenadas xy de q. */
Ponto quadGetPonto(Quad q);

/* Obtem a coordenada x do Quadrilátero q.
*  Parâmetros: Recebe o void pointer de q.
*  Retorno: Retorna um double. */
double quadGetX(Quad q);

/* Obtem a coordenada y do Quadrilátero q.
*  Parâmetros: Recebe o void pointer de q.
*  Retorno: Retorna um double. */
double quadGetY(Quad q);

/* Obtem a largura W do Quadrilátero q.
*  Parâmetros: Recebe o void pointer de q.
*  Retorno: Retorna um double. */
double quadGetW(Quad q);

/* Obtem a altura H do Quadrilátero q.
*  Parâmetros: Recebe o void pointer de q.
*  Retorno: Retorna um double. */
double quadGetH(Quad q);

/* Obtem o valor n do Quadrilátero q.
*  Parâmetros: Recebe o void pointer de q.
*  Retorno: Retorna um double. */
double quadGetN(Quad q);

/* Obtem a coordenada x do centro do Quadrilátero q.
*  Parâmetros: Recebe o void pointer de q.
*  Retorno: Retorna um double. */
double quadGetXc(Quad q);

/* Obtem a coordenada y do centro do Quadrilátero q.
*  Parâmetros: Recebe o void pointer de q.
*  Retorno: Retorna um double. */
double quadGetYc(Quad q);

/* Obtem a face relativa a quadra de um quadrilatero.
*  Parâmetros: Recebe o void pointer de q.
*  Retorno: um char representando a face. */
char quadGetFace(Quad q);

/* Altera a coordenada x do Quadrilátero q.
*  Parâmetrps: Recebe o void pointer de q e um double representando o valor de x.
*  Retorno: Não possui retorno. */
void quadSetX(Quad q, double x);

/* Altera a coordenada y do Quadrilátero q.
*  Parâmetrps: Recebe o void pointer de q e um double representando o valor de y.
*  Retorno: Não possui retorno. */
void quadSetY(Quad q, double y);

/* Altera a largura w do Quadrilátero q.
*  Parâmetrps: Recebe o void pointer de q e um double representando o valor de w.
*  Retorno: Não possui retorno. */
void quadSetW(Quad q, double w);

/* Altera a altura h do Quadrilátero q.
*  Parâmetrps: Recebe o void pointer de q e um double representando o valor de h.
*  Retorno: Não possui retorno. */
void quadSetH(Quad q, double h);

/* Altera o valor n do Quadrilátero q.
*  Parâmetrps: Recebe o void pointer de q e um double representando o valor de n.
*  Retorno: Não possui retorno. */
void quadSetN(Quad q, double n);

/* Altera o valor da face do Quadrilatero q.
 * Parametros: Recebe um ponteiro não nulo para o Quadrilatero e um char para a face. 
 * Retorno: Nao possui retorno. */
void quadSetFace(Quad q, char face);

/* Desaloca a memória de um quadrilatero
*  Parâmetros: Recebe um ponteiro não nulo para o quadrilatero
*  Retorno: Não possui retorno*/
void freeQuad(Quad q);

/* Função apenas para se encaixar no padrão definido pelo .h da QuadTree.
*  Parâmetros: Recebe um ponteiro não nulo para o quadrilatero.
*  Retorno: Retorna uma string constante*/
char *QuadGetId(Quad q);
#endif
