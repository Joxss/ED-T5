/* 
    Esse header possui funções que lidam com a escrita em arquivos txt necessárias para as funções do header qry.
*/

#ifndef _H_TXT
#define _H_TXT

#include "list.h"
#include "morador.h"
#include "quadra.h"
#include "pessoa.h"
#include "estabelecimento.h"

/* Grava no arquivo txt as informações da qry pnt.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt e um ponteiro não nulo para as informações do elemento específico.
*  Retorno: Não possui retorno. */
void txtPntQry(FILE *txt, Generic data);

/* Grava no arquivo txt as informações da qry delf.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt e um ponteiro não nulo para as informações do elemento específico.
*  Retorno: Não possui retorno. */
void txtDelfQry(FILE *txt, Generic data);

/* Grava no arquivo txt as informações da qry i?.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, um ponteiro não nulo para as informações do elemento específico 
               e um inteiro que representa se o ponto checado pela qry é interno ou não.
*  Retorno: Não possui retorno. */
void txtInsQry(FILE *txt, Generic data, int boolean);

/* Grava no arquivo txt as informações da qry o?.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, um ponteiro não nulo para as informações do primeiro elemento, 
               um ponteiro não nulo para as informações do segundo elemento e um inteiro que representa se os dois elementos se sobrepoem.
*  Retorno: Não possui retorno. */
void txtOverQry(FILE *txt, Generic data1, Generic data2, int boolean);

/* Grava no arquivo txt as informações de um elemento específico.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt e um ponteiro não nulo para as informações do elemento específico.
*  Retorno: Não possui retorno. */
void txtDetalhes(FILE *txt, void * data, char tipo[]);

/* Grava no arquivo txt o CEP de uma quadra específica.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt e um ponteiro não nulo para as informações do quadra específica.
*  Retorno: Não possui retorno. */
void txtCepQuadra(FILE *txt, Quadra quadra);

/* Grava no arquivo txt as informações da qry crd.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt e um ponteiro não nulo para as informações do elemento específicado e um char informando o tipo do elemento.
*  Retorno: Não possui retorno. */
void txtCrdQry(FILE *txt, void * data, char tipo[]);

/* Grava no arquivo txt as informações da area de uma quadra.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt e duas string contendo a área e o cep da quadra.
*  Retorno: Não possui retorno. */
void txtAreaQuadra(FILE *txt, char area[], char cep[]);

/* Grava no arquivo txt as informações da área total das quadras.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt e uma string contendo a área total.
*  Retorno: Não possui retorno. */
void txtAreaTotal(FILE *txt, char area[]);

/* Grava no arquivo txt um par de coordenadas
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt e os valores x e y das coordenadas
*  Retorno: Não possui retorno*/
void txtCoordenadas(FILE *txt, double x, double y);

/* Grava no arquivo txt as informações da qry ci
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt e os valores do total de casos na area, 
               a area da envoltoria convexa calculada, e a categoria de incidencia da região.
*  Retorno: Não possui retorno*/
void txtCiQry(FILE *txt, int totalCasos, double area, char incidencia);

/* Grava no arquivo txt as informações da qry M
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, um ponteiro nao nula para o morador e um ponteiro nao nulo para a pessoa;
*  Retorno: Não possui retorno*/
void txtMQry(FILE *txt, Morador morador, Pessoa pessoa);

/* Grava no arquivo txt as informações da qry Dm?
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, um ponteiro nao nula para o morador e um ponteiro nao nulo para a pessoa;
*  Retorno: Não possui retorno*/
void txtDmQry(FILE *txt, Morador morador, Pessoa pessoa);

/* Grava no arquivo txt as informações da qry De?
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, um ponteiro nao nula para o Estabelecimento e um ponteiro nao nulo para a pessoa;
*  Retorno: Não possui retorno*/
void txtDeQry(FILE *txt, Estabelecimento estabelecimento, Pessoa pessoa);

/* Grava no arquivo txt as informações da qry Mud?
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, um ponteiro nao nula para o pessoa, um ponteiro nao nulo para a morador e as informacoes do endereco antigo do morador;
*  Retorno: Não possui retorno*/
void txtMudQry(FILE *txt, Pessoa pessoa, Morador morador, char *cep_A, char face_A, int num_A, char *compl_A);

/* Grava no arquivo txt as informações da qry Eplg
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, um ponteiro nao nula para o pessoa e um ponteiro nao nulo para a estabelecimento;
*  Retorno: Não possui retorno*/
void txtEplgQry(FILE *txt, Pessoa pessoa, Estabelecimento estabelecimento);

/* Grava no arquivo txt as informações da qry catac
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt e um ponteiro nao nula para o generic que armazena o elemento removido;
*  Retorno: Não possui retorno*/
void txtCatacQry(FILE *txt, Generic elemento);

#endif