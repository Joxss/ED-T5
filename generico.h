/* 
    Esse header especifica um TAD usado para armazenar qualquer elemento e possui funções para obter o tipo do elemento armazenado, remover o elemento, e acessar ou modificar seus valores.
*/

#ifndef _H_GENERIC
#define _H_GENERIC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "circulo.h"
#include "retangulo.h"
#include "texto.h"
#include "linha.h"
#include "ponto.h"
#include "quadrilatero.h"
#include "poligono.h"
#include "chaveXvalor.h"
#include "pessoa.h"


typedef void *Generic;

/* Inicializa um novo genérico. O ponteiro retornado deve ter sua memoria desalocada utilizando a funcao freeGeneric.
*  Parâmetros: recebe o tipo, um ponteiro não nulo contendo as informações do elemento, 
               um ponteiro para a funcao que desaloca a memoria do elemento armazenado e um ponteiro para a funcao que retorna a coordenada do elemento armazenado.
*  Retorno: retorna um ponteiro para o genérico criado. */
Generic createGeneric(char tipo[], void *valor, void(*func)(void*), Ponto(*getPonto)(void*));


/* Obtem o ponto do elemento armazenado dentro do Generic.
*  Parâmetros: Recebe um ponteiro não nulo para o genérico.
*  Retorno: Retorna um ponteiro para um elemento do tipo Ponto contendo a coordenada do elemento que o genérico armazena. */
Ponto genericGetPonto(Generic g);

/* Obtem o tipo do genérico especificado.
*  Parâmetros: Recebe um ponteiro não nulo para o genérico.
*  Retorno: Retorna um char contendo o tipo de elemento que o genérico armazena. */
char* genericGetTipo(Generic g);

/* Obtem o elemento armazenado.
*  Parâmetros: Recebe um ponteiro não nulo para o genérico.
*  Retorno: retorna um ponteiro para as informações do elemento que o genérico armazena. */
void *genericGetValores(Generic g);

/* Obtem o id do elemento armazenado no genérico especificado.
*  Parâmetros: Recebe um ponteiro não nulo para o genérico.
*  Retorno: Retorna uma string contendo o id do elemento armazenado no genérico. */
char *genericGetId(Generic g);

/* Define a cor da borda e de preenchimento para o elemento armazendo no genérico especificado.
*  Parâmetros: Um ponteiro não nulo para o genérico, uma string para a cor da borda e um string para a cor do preenchimento.
*  Retorno: Não possui retorno */
void genericSetCores(Generic g, char corBorda[], char corPreench[]);

/* Atualiza um tipo para o genérico especificado.
*  Parâmetros: Um ponteiro não nulo para o genérico e um char que define o tipo.
*  Retorno: Não possui retorno */
void genericSetTipo(Generic g, char tipo[]);

/* Desaloca o espaço alocado para um genérico e o elemento armazenado dentro dele.
*  Parâmetros: Um ponteiro não nulo para o genérico
*  Retorno: Não possui retorno */
void freeGeneric(Generic g);

#endif