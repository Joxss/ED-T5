/* 
    Esse header especifica um TAD que representa um ponto e possui funções para criação e acesso das variáveis desse TAD.
*/

#ifndef _H_PONTO
#define _H_PONTO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Ponto;

/* Inicializa um novo ponto. O ponteiro retornado deve ter sua memoria desalocada utilizando a funcao freePonto.
*  Parâmetros: Recebe dois doubles representando as coordenadas x e y.
*  Retorno: retorna um ponteiro para o ponto criado. */
Ponto createPoint(double x, double y);

/* Obtem a coordenada x do Ponto p
*  Parâmetros: Recebe o void pointer de p.
*  Retorno: Retorna um double. */
double pontoGetX(Ponto p);

/* Obtem a coordenada y do Ponto p
*  Parâmetros: Recebe o void pointer de p.
*  Retorno: Retorna um double. */
double pontoGetY(Ponto p);

/* Altera a coordenada x do Ponto p
*  Parâmetros: Recebe o void pointer de p e um double representando o valor de x.
*  Retorno: Não possui retorno. */
void pontoSetX(Ponto p, double x);

/* Altera a coordenada y do Ponto p
*  Parâmetros: Recebe o void pointer de p e um double representando o valor de y.
*  Retorno: Não possui retorno. */
void pontoSetY(Ponto p, double y);

/* Retorna o proprio elemento.
*  Parâmetros: Recebe um ponto P.
*  Retorno: Retorna o ponto recebido por parâmetro */
Ponto pontoGetPonto(Ponto p);

/* Retorna a string "ponto". Função necessario apenas para criar uma quadtree de pontos.
*  Parâmetros: Recebe um ponto P.
*  Retorno: Retorna a string "ponto". */
char *pontoGetId(Ponto p);

/* Desaloca a memória de um ponto
*  Parâmetros: Recebe um ponteiro não nulo para o ponto
*  Retorno: Não possui retorno*/
void freePonto(Ponto p);
#endif
