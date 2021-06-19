/* 
    Esse header possui funções que lidam com a escrita em arquivos svg.
*/

#ifndef _H_SVG
#define _H_SVG

#include "calculos.h"
#include "list.h"
#include "QuadTree.h"
#include "grafo.h"

/* Printa filtros utilizados por alguns elementos no svg.
*  Parâmetros: Recebe o arquivo svg.
*  Retorno: Não possui retorno. */
void svgPrintFilter(FILE *svg);

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

/* Printa um elemento do tipo poligono no arquivo svg.
*  Parâmetros: Recebe o arquivo svg e um ponteiro não nulo para o poligono.
*  Retorno: Não possui retorno.*/ 
void svgPrintPoligono(FILE *svg, Poligono p);

/* Verifica o tipo do elemento e seleciona a funcao correta para escreve-lo no svg.
*  Parâmetros: Recebe ponteiro não nulo para o generic que armazena o elemento e um ponteiro nao nulo para o FILE aberto na forma de um void *.
*  Retorno: Não possui retorno.*/ 
void svgSelectTag(Generic elemento, void *file);

/* Escreve no arquivo svg o estado atual de uma arvore.
*  Parâmetros: Recebe ponteiro não nulo a arvore e uma string contendo o caminho mais o nome do arquivo svg a ser gerado.
*  Retorno: Não possui retorno.*/ 
void svgPrintTreeState(QuadTree tree, char *path);

/* Escreve no arquivo svg o estado atual de um grafo
*  Parâmetros: Recebe o arquivo svg, um ponteiro nao nulo para o grafo e uma variavel booleana indicando se o grafo é direcionado ou não, 
*  Retorno: Não possui retorno.*/ 
void svgPrintGrafo(FILE *svg, Grafo grafo, int ehDirecionado);

/* Escreve no arquivo svg o caminho animado com uma imagem.
*  Parâmetros: Recebe o arquivo svg, um ponteiro nao nulo para a lista que contem as coordenadas do caminho, uma string contendo a cor do caminho
               uma variavel booleana indicando se é um caminho mais rapido ou mais curto e uma variavel booleana indicando se é um percusso de uma ciclovia
*  Retorno: Não possui retorno.*/ 
void svgPrintCaminhoAnimado(FILE *svg, List caminho, char *cor, int ehMaisCurto, int taDeBike);

#endif