#ifndef _H_ESTABELECIMENTO
#define _H_ESTABELECIMENTO

/* 
    Esse header especifica um TAD que representa um estabelecimento comercial e possui funcoes para criacao, desalocamento e acesso das variaveis desse TAD.
*/

#include "quadra.h"
#include "ponto.h"

typedef void *Estabelecimento;

/* Inicializa um elemento do tipo Estabelecimento. O ponteiro retornado deve ter sua memoria deslocada utilizando a funcao freeEstabelecimento.
*  Parâmetros: Uma string cnpj do estabelecimento, uma string cpf do dono, uma string contendo a descricao do estabelecimento,
               um ponteiro não nulo para a quadra do estabelcimento, um char para a face, um int para o num e uma string para o nome do estabelecimento;
*  Retorno: Retorna um ponteiro para um elemento do tipo estabelecimento. */
Estabelecimento createEstabelecimento(char *cnpj, char *cpf, char *descricao, Quadra quadra, char face, int num, char *nome);

/* Atualiza o endereco de um estabelecimento.
*  Parâmetros: Recebe um ponteiro não nulo para o estabelecimento, um ponteiro não nulo para a nova quadra do endereco um char para a nova face e um int para o novo numero.
*  Retorno: Nao possui retorno. */
void EstSetEndereco(Estabelecimento e, Quadra quadra, char face, int num);

/* Obtem o cnpj de um estabelecimento.
*  Parâmetros: Ponteiro não nulo para o estabelecimento.
*  Retorno: Retorna uma string contendo o cnpj. */
char * estabelecimentoGetCnpj(Estabelecimento e);

/* Obtem o cpf do dono de um estabelecimento.
*  Parâmetros: Ponteiro não nulo para o estabelecimento.
*  Retorno: Retorna uma string contendo o cpf. */
char * estabelecimentoGetCpf(Estabelecimento e);

/* Obtem a descricao de um estabelecimento.
*  Parâmetros: Ponteiro não nulo para o estabelecimento.
*  Retorno: Retorna uma string contendo a descricao do estabelecimento. */
char * estabelecimentoGetDescricao(Estabelecimento e);

/* Obtem o cep de um estabelecimento.
*  Parâmetros: Ponteiro não nulo para o estabelecimento.
*  Retorno: Retorna uma string contendo cep. */
char * estabelecimentoGetCep(Estabelecimento e);

/* Obtem a face relativa a quadra de um estabelecimento.
*  Parâmetros: Ponteiro não nulo para o estabelecimento.
*  Retorno: Retorna um char contendo a face. */
char estabelecimentoGetFace(Estabelecimento e);

/* Obtem o numero de um estabelecimento.
*  Parâmetros: Ponteiro não nulo para o estabelecimento.
*  Retorno: Retorna uma int contendo o numero. */
int estabelecimentoGetNum(Estabelecimento e);

/* Obtem o valor do nome de um Estabelecimento.
*  Parâmetros: Ponteiro não nulo para o Estabelecimento.
*  Retorno: Retorna uma string contendo o nome. */
char * estabelecimentoGetNome(Estabelecimento e);

/* Obtem o valor da coordenada do estabelecimento representada por um objeto do tipo Ponto.
*  Parâmetros: Ponteiro não nulo para o Estabelecimento.
*  Retorno: Retorna um ponto contendo a coordenada do estabelecimento */
Ponto estabelecimentoGetCoord(Estabelecimento e);

/* Desaloca a memoria de um elemento do tipo morador.
*  Parâmetros: Ponteiro não nulo para o morador.
*  Retorno: Não possui retorno */
void freeEstabelecimento(Estabelecimento e);



#endif