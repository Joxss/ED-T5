/* 
    Esse header possui funções que lidam com diversos cálculos necessários para as funções do header qry.
*/

#ifndef _H_CALCULOS
#define _H_CALCULOS

#include <stdlib.h>
#include <stdio.h>
#include "generico.h"

/* Pega a quantidade de algarismos de um inteiro
*  Parametros: Recebe um inteiro como paramentro
*  Retorno: Retorna a quantidade de algarismos que compõe o inteiro. */ 
int getQtdAlgarismos(int n);

/* Checa se um ponto é interno a uma circunferência ou retangulo
*  Parametros: Um ponteiro não nulo para as informações do elemento desejado, um double para a coordenada x do ponto e um double para a coordenada y do ponto.
*  Retorno: Caso o ponto seja interna ao elemento, retorna 1, caso contrário retorna 0. */
int checaInterno(Generic elemento, double xPonto, double yPonto);

/* Checa se ocorre uma colisão entre dois elementos
*  Parâmetros: Um ponteiro não nulo para as informações do elemento1 e outro ponteiro não nulo para as informações do elemento2.
*  Retorno: Caso o ponto seja interna ao elemento, retorna 1, caso contrário retorna 0. */
int checaColisao(Generic polig1, Generic polig2);

/* Calcula as coordenadas de um retângulo que envolve dois elementos específicos.
*  Parâmetros: Um ponteiro não nulo para variáveis x, y, w e h do retângulo a ser calculado, um ponteiro não nulo para o primeiro elemento e um ponteiro não nulo para o segundo elemento.
*  Retorno: Não possui retorno. */
void calculaValoresRect(double *x, double *y, double *w, double *h, Generic fig1, Generic fig2);

/* Checa se um elemento do tipo circulo retangulo ou ponto é interno a um círculo;
*  Parâmetros: Um ponteiro não nulo para o elemento, um double para a coordenada x do centro do circulo, um double para a coordenada y do centro do circulo e um double para o raio do círculo.
*  Retorno: Caso o elemento seja interno ao círculo, retorna 1, caso contrário retorna 0. */
int checkInsideCirc(Generic elemento, double xCirc, double yCirc, double rCirc);

/* Checa se um retangulo ou ponto é interno a outro retângulo;
*  Parâmetros: Um ponteiro não nulo para o elemento, um double para as coordenadas x, y, w e h do retângulo.
*  Retorno: Caso o elemento seja interno ao retângulo, retorna 1, caso contrário retorna 0. */
int checkRectInsideRect(Generic elemento, double x, double y, double w, double h);

/* Calcula os valores de um quadrado no endereço cep face num.
*  Parâmetros: Ponteiros para os valores x y w h do quadrado a serem modificados, um inteiro n que define o tamanho ,uma quadra, a face dessa quadra e o numero relativo a face.
*  Retorno: Não possui retorno. */
void setCv(double *x, double *y, double *w, double *h, int n, Rect quadra, char face, double num);

/* Checa se um poligono convexo esta completamente dentro de um retangulo;
 * Parâmetros: Um ponteiro nao nulo para o poligono, e um ponteiro nao nulo para um elemento do tipo Quad representando o retangulo.
 * Retorno: Retorna um inteiro 1 se estiver dentro ou 0 se estiver fora. */
int checkPoligInsideRect(Poligono polig, Quad rect);

#endif