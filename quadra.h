#ifndef _H_QUADRA
#define _H_QUADRA

/* 
    Esse header especifica um TAD que representa uma quadra e possui funções para criação, desalocamento e acesso das variáveis desse TAD.
*/

#include <stdio.h>
#include <stdlib.h>
#include "ponto.h"
#include "list.h"

#include "generico.h"

typedef void *Quadra;

/* Inicializa uma nova quadra. O ponteiro retornado deve ter sua memoria desalocada utilizando a funcao freeQuadra.
*  Parâmetros: recebe uma string contendo o id, variáveis double contendo x, y, w e r e strings contendo a expressura da borda, a cor da borda e a cor do preenchimento.
*  Retorno: Retorna um ponteiro para a quadra criado. */
Quadra createQuadra(char id[], double x, double y, double w, double h, char borda[], char corBorda[], char corPreench[]);

/* Adiciona n casos de covid a face de uma quadra.
*  Parâmetros: Recebe um ponteiro não nulo para a quadra, um char (N,S,L,O), e um int.
*  Retorno: Não possui retorno. */
void quadraAddCasos(Quadra q, char face, int n);

/* Retorna os n casos de covid da face de uma quadra.
*  Parâmetros: Recebe um ponteiro não nulo para a quadra, um char (N,S,L,O) informando a face.
*  Retorno: Retorna um inteiro contendo a quantidade de casos na face da quadra. */
int quadraGetCasos(Quadra q, char face);

/* Obtem o cep de uma quadra.
*  Parâmetros: Recebe um ponteiro não nulo para a quadra.
*  Retorno: Retorna uma string contendo o cep da quadra. */
char *quadraGetCep(Quadra q);

/* Obtem a expressura da borda de uma quadra.
*  Parâmetros: Recebe um ponteiro não nulo para a quadra.
*  Retorno: Retorna uma string contendo a expressura da borda da quadra. */
char *quadraGetBorda(Quadra q);

/* Obtem a cor da borda de uma quadra.
*  Parâmetros: Recebe um ponteiro não nulo para a quadra.
*  Retorno: Retorna uma string contendo a cor da borda da quadra. */
char *quadraGetCorBorda(Quadra r);

/* Obtem a cor de preenchimento de uma quadra.
*  Parâmetros: Recebe um ponteiro não nulo para a quadra.
*  Retorno: Retorna uma string contendo a cor de preenchimento da quadra. */
char *quadraGetCorPreench(Quadra q);

/* Obtem um ponteiro de um Ponto contendo as coordenada xy da quadra.
*  Parâmetros: Recebe um ponteiro não nulo para a quadra.
*  Retorno: Retorna um ponteiro para o elemento do tipo Ponto que guarda a coordenada da quadra. */
Ponto quadraGetPonto(Quadra q);

/* Obtem a coordenada x de uma quadra
*  Parâmetros: Recebe um ponteiro não nulo para a quadra.
*  Retorno: retorna um double representando a coordenada x da quadra. */
double quadraGetX(Quadra q);

/* Obtem a coordenada y de uma quadra
*  Parâmetros: Recebe um ponteiro não nulo para a quadra.
*  Retorno: retorna um double representando a coordenada y da quadra. */
double quadraGetY(Quadra q);

/* Obtem a largura de uma quadra
*  Parâmetros: Recebe um ponteiro não nulo para a quadra.
*  Retorno: retorna um double representando a largura da quadra. */
double quadraGetW(Quadra q);

/* Obtem altura de uma quadra
*  Parâmetros: Recebe um ponteiro não nulo para a quadra.
*  Retorno: retorna um double representando altura da quadra. */
double quadraGetH(Quadra q);

/* Obtem a coordenada x do centro de uma quadra
*  Parâmetros: Recebe um ponteiro não nulo para a quadra.
*  Retorno: retorna um double representando a coordenada x do centro da quadra. */
double quadraGetXc(Quadra q);

/* Obtem a coordenada y do centro de uma quadra
*  Parâmetros: Recebe um ponteiro não nulo para a quadra.
*  Retorno: retorna um double representando a coordenada y do centro da quadra. */
double quadraGetYc(Quadra q);

/* Obtem a lista de moradores de uma quadra
*  Parâmetros: Recebe um ponteiro não nulo para a quadra.
*  Retorno: retorna um ponteiro contendo a lista que possui os elemento moradores da quadra. Essa lista é desalocada na funcao freeQuadra */
List quadraGetMoradores(Quadra q);

/* Obtem a cor da sombra da quadra especificada.
*  Parâmetros: Recebe ponteiro não nulo para a quadra.
*  Retorno: Uma string contendo a cor da sombra ou NULO caso nao exista cor */
char *quadraGetCorSombra(Quadra q);

/* Inicializa um novo ponto com as coordenadas xy da face e num da quadra. O ponteiro retornado deve ter sua memória desaloca pela função freePonto.
*  Parâmetros: Recebe ponteiro não nulo para a quadra, um caracter representando a face(S,N,L,O) e um inteiro representando o numero.
*  Retorno: Retorna um ponteiro para um ponto com as coordenadas */
Ponto quadraGetEndereco(Quadra q, char face, int num);

/* Insere um morador da lista de moradores da quadra.
*  Parâmetros: Recebe ponteiro não nulo para a quadra e o Generic do morador a ser inserido.
*  Retorno: Não possui retorno */
void quadraInserirMorador(Quadra q, Generic morador);

/* Remove um morador da lista de moradores da quadra.
*  Parâmetros: Recebe ponteiro não nulo para a quadra e uma string com o cpf do morador a ser removido.
*  Retorno: Não possui retorno */
void quadraRemoverMorador(Quadra q, char cpf[]);

// SETTERS
/* Atualiza a cor da sombra para a quadra especificada.
*  Parâmetros: Recebe ponteiro não nulo para a quadra e uma string para a cor da sombra.
*  Retorno: Não possui retorno */
void quadraSetCorSombra(Quadra q, char corSombra[]);

/* Atualiza a cor da borda para a quadra especificada.
*  Parâmetros: Recebe ponteiro não nulo para a quadra e uma string para a cor da borda.
*  Retorno: Não possui retorno */
void quadraSetCorBorda(Quadra q, char corBorda[]);

/* Atualiza a cor do preenchimento para a quadra especificada.
*  Parâmetros: Recebe ponteiro não nulo para o quadra e uma string para a cor de preenchimento.
*  Retorno: Não possui retorno */
void quadraSetCorPreench(Quadra q, char corPreench[]);

/* Desaloca a memória de uma quadra
*  Parâmetros: Recebe um ponteiro não nulo para uma quadra.
*  Retorno: Não possui retorno*/
void freeQuadra(Quadra q);

#endif //_H_QUADRA