#ifndef _H_RUA
#define _H_RUA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quadra.h"

typedef void* Rua;

/* Inicializa uma nova rua. O ponteiro retornado deve ter sua memoria desalocada utilizando a funcao freeRua.
*  Parâmetros: recebe uma string contendo o nome (tam<=100), ponteiros para as quadras do lado direito e esquerdo (podem ser NULL)
               e variáveis double contendo a distancia daquela rua e a velocidade média naquela rua.
*  Retorno: Retorna um ponteiro para a rua criada. */
Rua createRua(char nome[], Quadra quadraDireita, Quadra quadraEsquerda, double distancia, double velocidadeMedia);

/* Obtém o nome de uma rua.
*  Parâmetros: Recebe um ponteiro não nulo para a rua.
*  Retorno: Retorna uma string contendo o nome da rua. 
*/
char *ruaGetNome(Rua r);

/* Obtém a quadra do lado direito de uma rua. O ponteiro retornado não deve ter sua memória desalocada.
*  Parâmetros: Recebe um ponteiro não nulo para a rua.
*  Retorno: Retorna um ponteiro para a quadra do lado direito da rua caso existir, caso contrario returna NULL. 
*/
Quadra ruaGetQuadraDireita(Rua r);

/* Obtém a quadra do lado esquerdo de uma rua. O ponteiro retornado não deve ter sua memória desalocada.
*  Parâmetros: Recebe um ponteiro não nulo para a rua.
*  Retorno: Retorna um ponteiro para a quadra do lado esquerdo da rua caso existir, caso contrario returna NULL. 
*/
Quadra ruaGetQuadraEsquerda(Rua r);

/* Obtém o cep da quadra ao lado direito de uma rua.
*  Parâmetros: Recebe um ponteiro não nulo para a rua.
*  Retorno: Retorna uma string contendo o o cep da quadra ao lado direito da rua. 
*/
char *ruaGetCepDireito(Rua r);

/* Obtém o o cep da quadra ao lado esquerdo de uma rua.
*  Parâmetros: Recebe um ponteiro não nulo para a rua.
*  Retorno: Retorna uma string contendo o o cep da quadra ao lado esquerdo da rua. 
*/
char *ruaGetCepEsquerdo(Rua r);

/* Obtém a distancia de uma rua.
*  Parâmetros: Recebe um ponteiro não nulo para a rua.
*  Retorno: Retorna um double representando a distancia da rua. 
*/
double ruaGetDistancia(Rua r);

/* Obtém a velocidade média de uma rua.
*  Parâmetros: Recebe um ponteiro não nulo para a rua.
*  Retorno: Retorna um double representando a velocidade média da rua. 
*/
double ruaGetVelocidadeMedia(Rua r);

/* Obtém o tempo para para transitar por uma rua.
*  Parâmetros: Recebe um ponteiro não nulo para a rua.
*  Retorno: Retorna um double representando o tempo da rua. 
*/
double ruaGetTempo(Rua r);

/* Desaloca a memória de uma rua. Não desaloca a memória dos ponteiros das quadras do lado direito e esquerdo
*  Parâmetros: Recebe um ponteiro não nulo para a rua.
*  Retorno: Não possui retorno.
*/
void freeRua(Rua r);

#endif