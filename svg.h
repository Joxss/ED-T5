/* 
    Esse header possui funções que lidam com a escrita em arquivos svg.
*/

#ifndef _H_SVG
#define _H_SVG

#include "calculos.h"
#include "list.h"
#include "QuadTree.h"

/* Abre a tag svg em um arquivo.
*  Parâmetros: Recebe uma string representando o diretório do arquivo.
*  Retorno: Não possui retorno. */
void svgOpenTag(char file[]);

/* Fecha a tag svg em um arquivo.
*  Parâmetros: Recebe uma string representando o diretório do arquivo.
*  Retorno: Não possui retorno. */
void svgCloseTag(char file[]);

/* Percorre uma lista escrevendo no arquivo svg uma tag específica baseada em cada elemento.
*  Parâmetros: Recebe ponteiro não nulo para a lista e uma string representando o diretório do arquivo svg.
*  Retorno: Não possui retorno.*/ 
void svgPrintList(List l, char svg[]);

/* Verifica o tipo do elemento e seleciona a funcao correta para escreve-lo no svg.
*  Parâmetros: Recebe ponteiro não nulo para o generic que armazena o elemento e um ponteiro nao nulo para o FILE aberto na forma de um void *.
*  Retorno: Não possui retorno.*/ 
void svgSelectTag(Generic elemento, void *file);

/* Escreve no arquivo svg o estadual atual de uma arvore.
*  Parâmetros: Recebe ponteiro não nulo a arvore e uma string contendo o caminho mais o nome do arquivo svg a ser gerado.
*  Retorno: Não possui retorno.*/ 
void svgPrintTreeState(QuadTree tree, char *path);

#endif