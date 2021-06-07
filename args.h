/* 
    Esse header possui funções que lidam com o tratamento dos argumentos passados na invocação do programa.
*/

#ifndef _H_ARGS
#define _H_ARGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Diretorios;

/* Define os diretórios de entrada e saída de todos os arquivos baseados nos argumentos passados na invocação do programa. 
*  Parâmetros: Recebe um inteiro representando a quantidade de argumentos e um ponteiro para os argumentos da linha de comando (é obrigatório a presença das flags: -f, -o).
*  Retorno: Retorna um ponteiro para uma estrutura de dados contendo os diretórios. O ponteiro retornado deve ter sua memoria desalocada utilizando a funcao deleteDir.*/
Diretorios defineArgs(int argc, char* argv[]);

/* Desaloca os espaços de memória alocados para os diretórios
*  Parâmetros: Um ponteiro não nulo para os diretorios.
*  Retorno: Não possui retorno*/
void deleteDir(Diretorios d);

/* Obtem o diretório do arquivo .geo
*  Parâmetros: Um ponteiro não nulo para os diretórios.
*  Retorno: Um ponteiro para os diretórios. */
char *getPathGeo(Diretorios d);

/* Obtém o diretorio do arquivo .qry
*  Parâmetros: Um ponteiro não nulo para os diretórios.
*  Retorno: Um ponteiro para os diretórios. */
char *getPathQry(Diretorios d);

/* Obtem o diretório do arquivo .svg
*  Parâmetros: Um ponteiro não nulo para os diretórios.
*  Retorno: Caso exista o diretório desejado, retorna uma string contendo o diretório, caso contrário retorna NULL. */
char *getPathSvg(Diretorios d);

/* Obtem o diretório do arquivo .svg depois da qry
*  Parâmetros: Um ponteiro não nulo para os diretórios.
*  Retorno: Caso exista o diretório desejado, retorna uma string contendo o diretório, caso contrário retorna NULL. */
char *getPathSvgQry(Diretorios d);

/* Obtem o diretório do arquivo .txt
*  Parâmetros: Um ponteiro não nulo para os diretórios.
*  Retorno: Caso exista o diretório desejado, retorna uma string contendo o diretório, caso contrário retorna NULL. */
char *getPathTxtQry(Diretorios d);

/**Obtém o diretorio do arquivo .ec
 * Parâmetros: Um ponteiro não nulo para os diretórios.
 * Retorno: Caso exista o diretório desejado, retorna uma string contendo o diretório, caso contrário retorna NULL. */
char *getPathEC(Diretorios d);

/**Obtém o diretorio do arquivo .pm
 * Parâmetros: Um ponteiro não nulo para os diretórios.
 * Retorno: Caso exista o diretório desejado, retorna uma string contendo o diretório, caso contrário retorna NULL. */
char *getPathPM(Diretorios d);

/**Obtém o diretorio do arquivo .via
 * Parâmetros: Um ponteiro não nulo para os diretórios.
 * Retorno: Caso exista o diretório desejado, retorna uma string contendo o diretório, caso contrário retorna NULL. */
char *getPathVia(Diretorios d);

/**Obtém o diretorio do arquivo qry com sufixo. A string retornada precisa ser desalocada separadamente.
 * Parâmetro: Um ponteiro não nulo para os Diretorios
 * Retorno: O path já com o sufixo para o arquivo .svg
*/
char *getPathSufix(Diretorios d, char *sufixo);

#endif