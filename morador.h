#ifndef _H_MORADOR
#define _H_MORADOR

/* 
    Esse header especifica um TAD que representa um morador e possui funçoes para criacao, desalocamento e acesso das variáveis desse TAD.
*/

#include "quadra.h"
#include "ponto.h"


typedef void * Morador;

/* Inicializa um elemento do tipo Morador. O ponteiro retornado deve ter sua memoria desalocada utilizando a funcao freeMorador.
*  Parâmetros: Uma string cpf do morador, 
               um ponteiro não nulo para a quadra do morador, um char para a face, um int para o num e uma string para o complemento do endereco do morador;
*  Retorno: Retorna um ponteiro para um elemento do tipo morador. */
Morador createMorador(char * cpf, Quadra quadra, char face, int num, char *compl);

/* Atualiza o endereco de um morador.
*  Parâmetros: Recebe um ponteiro não nulo para o morador, um ponteiro não nulo para a nova quadra do endereco um char para a nova face e um int para o novo numero.
*  Retorno: Nao possui retorno. */
void moradorSetEndereco(Morador m, Quadra quadra, char face, int num, char *compl);

/* Obtem o valor da coordenada do morador representada por um objeto do tipo Ponto.
*  Parâmetros: Ponteiro não nulo para o morador.
*  Retorno: Retorna um ponto contendo a coordenada do morador*/
Ponto moradorGetPonto(Morador m);

/* Obtem o cep de um morador.
*  Parâmetros: Ponteiro não nulo para o morador.
*  Retorno: Retorna uma string contendo cep. */
char * moradorGetCep(Morador m);

/* Obtem o cpf do dono de um morador.
*  Parâmetros: Ponteiro não nulo para o morador.
*  Retorno: Retorna uma string contendo o cpf. */
char * moradorGetCpf(Morador m);

/* Obtem a face relativa a quadra de um morador.
*  Parâmetros: Ponteiro não nulo para o morador.
*  Retorno: Retorna um char contendo a face. */
char moradorGetFace(Morador m);

/* Obtem o numero de um morador.
*  Parâmetros: Ponteiro não nulo para o morador.
*  Retorno: Retorna uma int contendo o numero. */
int moradorGetNum(Morador m);

/* Obtem o complemento do endereco de um morador.
*  Parâmetros: Ponteiro não nulo para o morador.
*  Retorno: Retorna uma string contendo o complemento do endereco. */
char * moradorGetCompl(Morador m);

/* Desaloca a memoria de um elemento do tipo Morador.
*  Parâmetros: Ponteiro não nulo para o Estabelecimento.
*  Retorno: Não possui retorno */
void freeMorador(Morador m);

#endif //_H_MORADOR