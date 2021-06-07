#ifndef _H_HTABLE
#define _H_HTABLE

/* 
    Esse header especifica um TAD que representa uma hashtalbe e possui funçoes para criacao, desalocamento e insercao, remocao e acesso de elemento armazenados nesse TAD.
*/

#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *Htable;


/* Inicializa uma nova HashTable. O ponteiro retornado deve ter sua memoria desalocada com a função freeHashTable caso ele queira desalocar inclusive os valores armazenados ou utilizando a freeHashTable2 caso queira desacolar apenas a HashTable.
*  Parâmetros: recebe um int n que define o tamanho da tabela
*  Retorno: retorna um ponteiro para a HashTable criada criado. */
Htable createHashTable(int n);

/* Insere um novo dado dentro da hash table.
 * Parâmetros: Recebe um ponteiro nao nulo para a hash table o valor da chave como string e um ponteiro para o dado a ser armazenado.
 * Retorno: Nao possui retorno.
*/
void hashInsert(Htable ht, char *key, void *data);

/* Checa se uma determinada chave existe na HashTable.
*  Parâmetros: Recebe um ponteiro nao nulo para a hash table e uma string representando a chave desejada.
*  Retorno: retorna 1 caso a chave ja exista na hashtable e 0 caso contrario. */
int hashKeyExist(Htable ht, char *key);

/* Retorna uma informacao relacionada a uma chave em uma hash table.
 * Parâmetros: Recebe um ponteiro nao nulo para a hash table o valor da chave relacioada a informacao desejada como string.
 * Retorno: Retorna a informacao armazenada que se relaciona com a chave especificada.
*/
void *hashGetKey(Htable ht, char *key);

/* Atualiza uma informacao relacionada a uma chave em uma hash table.
 * Parâmetros: Recebe um ponteiro nao nulo para a hash table, a chave e o novo valor.
 * Retorno: Retorna o valor antigo, caso a chave exista.
*/
void *hashUpdateKey(Htable ht, char *key, void *data);

/* Remove um chave pertencente a hash table.
 * Parâmetros: Recebe um ponteiro nao nulo para a hash table e o valor da chave como string.
 * Retorno: Retorna a informacao relacionada a chave removida.
*/
void *hashRemoveKey(Htable ht, char *key);

/* Desaloca o espaço de memoria alocado para uma hash table e inclusive para as informacoes armazenadas dentro dela.
 * Parâmetros: Recebe um ponteiro nao nulo para a hash table.
 * Retorno: Nao possui retorno.
*/
void freeHashTable(Htable ht, void(*freeFunc)(void*));

/* Desaloca apenas o espaço de memoria alocado para uma hash table mantendo alocado os informacoes armazenados dentro dela.
 * Parâmetros: Recebe um ponteiro nao nulo para a hash table.
 * Retorno: Nao possui retorno.
*/
void freeHashTable2(Htable ht);
#endif