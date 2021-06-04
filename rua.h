#ifndef _H_RUA
#define _H_RUA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void* Rua;

/* Inicializa uma nova rua. O ponteiro retornado deve ter sua memoria desalocada utilizando a funcao freeRua.
*  Parâmetros: recebe strings contendo o nome (tam<=100), id da quadra ao lado direito e id da quadra ao lado esquerdo (tam<=50)
               e variáveis double contendo a distancia daquela rua e a velocidade média naquela rua.
*  Retorno: Retorna um ponteiro para a rua criada. */
Rua createRua(char nome[], char cepLadoDireito[], char cepLadoEsquerdo[], double distancia, double velocidadeMedia);

/* Obtém o nome de uma rua.
*  Parâmetros: Recebe um ponteiro não nulo para a rua.
*  Retorno: Retorna uma string contendo o nome da rua. 
*/
char *ruaGetNome(Rua r);

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

#endif