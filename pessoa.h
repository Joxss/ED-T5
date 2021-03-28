#ifndef _H_PESSOA
#define _H_PESSOA

/* 
    Esse header especifica um TAD que representa uma pessoa e possui funçoes para criacao, desalocamento e acesso das variáveis desse TAD.
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef void *Pessoa;

/* Inicializa um elemento do tipo pessoa. O ponteiro retornado deve ter sua memoria desalocada utilizando a funcao freePessoa.
*  Parâmetros: Uma string cpf da pessoa, 
               uma string representando o nome, uma string representando o sobrenome, um char representando o sexo, e uma string representando a data de nascimento.
*  Retorno: Retorna um ponteiro para um elemento do tipo morador. */
Pessoa createPessoa(char *cpf, char *nome, char *sobrenome, char sexo, char *nascimento);

/* Obtem o cpf de uma pessoa.
*  Parâmetros: Ponteiro não nulo para a pessoa.
*  Retorno: Retorna uma string contendo o cpf da pessoa.*/
char * pessoaGetCpf(Pessoa p);

/* Obtem o nome de uma pessoa.
*  Parâmetros: Ponteiro não nulo para a pessoa.
*  Retorno: Retorna uma string contendo o nome da pessoa.*/
char * pessoaGetNome(Pessoa p);

/* Obtem o sobrenome de uma pessoa.
*  Parâmetros: Ponteiro não nulo para a pessoa.
*  Retorno: Retorna uma string contendo o sobrenome da pessoa.*/
char * pessoaGetSobrenome(Pessoa p);

/* Obtem o sexo de uma pessoa.
*  Parâmetros: Ponteiro não nulo para a pessoa.
*  Retorno: Retorna um char contendo o sexo da pessoa.*/
char pessoaGetSexo(Pessoa p);

/* Obtem a data de nascimento de uma pessoa.
*  Parâmetros: Ponteiro não nulo para a pessoa.
*  Retorno: Retorna uma string contendo a data de nascimento da pessoa.*/
char * pessoaGetNascimento(Pessoa p);

/* Desaloca a memoria de um elemento do tipo Pessoa.
*  Parâmetros: Ponteiro não nulo para o Pessoa.
*  Retorno: Não possui retorno */
void freePessoa(Pessoa p);

#endif