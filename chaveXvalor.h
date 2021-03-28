#ifndef _H_ChaveXvalor
#define _H_ChaveXvalor

/* 
    Esse header especifica um TAD que representa um conjunto de strings chave e valor e possui funcoes para criacao, desalocamento e acesso das variaveis desse TAD.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef void * ChaveXValor;

/* Inicializa um elemento do tipo chaveXvalor. O ponteiro retornado deve ter sua memoria deslocada utilizando a funcao freeChaveXvalor.
*  Parâmetros: uma string contendo a chave e outra string contendo o valor.
*  Retorno: Retorna um ponteiro para um elemento do tipo chaveXvalor. */
ChaveXValor createChaveValor(char *chave, char *valor);

/* Obtem o valor armazenado como chave em um elemento do tipo chaveXvalor.
*  Parâmetros: Ponteiro não nulo para a ChaveXValor.
*  Retorno: Retorna uma string contendo a chave. */
char *chaveXvalorGetChave(ChaveXValor chaveValor);

/* Obtem o valor armazenado em um elemento do tipo chaveXvalor.
*  Parâmetros: Ponteiro nao nulo para um elemento do tipo chaveXvalor.
*  Retorno: Retorna uma string contendo o valor. */
char *chaveXvalorGetValor(ChaveXValor chaveValor);

/* Atualiza o valor de um elemento do tipo chaveXvalor.
*  Parâmetros: Ponteiro nao nulo para um elemento do tipo chaveXvalor e uma string contendo o novo valor.
*  Retorno: Não possui retorno. */
void chaveXvalorSetValor(ChaveXValor chaveValor, char *valor);

/* Desaloca a memoria de um elemento do tipo chaveXvalor.
*  Parâmetros: Ponteiro não nulo para a ChaveXValor.
*  Retorno: Não possui retorno */
void freeChaveXvalor(ChaveXValor chaveValor);

#endif
