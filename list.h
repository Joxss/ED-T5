    /* 
    Esse header especifica dois TAD, o primeiro representando uma lista ligada duplamente encadada, e o segundo representando um nó dessa lista.
    Possui funções que lidam com a inserção, remoção e acesso de elementos dentro da lista.
*/

#ifndef _H_LIST
#define _H_LIST

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generico.h"

typedef void *List;
typedef void *Node;
 
/* Inicializa um nova Linked List. O ponteiro retornado deve ter sua memoria desalocada utilizando a funcao freeLista ou freeLista2.
*  Parâmetros: nenhum parâmetro é necessário.
*  Retorno: retorna um ponteiro para uma Linked List zerada. */
List createLista();

/* Verifica o tamanho da lista.
*  Parâmetros: Um ponteiro não nulo para a lista.
*  Retorno: Retorna o tamanho da lista. */
int listLenght(List l);

/* Insere um elemento na Linked List.
*  Parâmetros: recebe um ponteiro não nulo para a lista e um ponteiro não nulo para as informações do elemento a ser inserido. 
*  Retorno: Retorna um ponteiro para o nó do elemento adicionado. */
Node listInsert(List l, void* n);

/* Procura por um elemento na Linked List a partir de seu id.
*  Parâmetros: recebe um ponteiro não nulo para a lista e um tipo char[] representando o id do elemento desejado e um ponteiro para a função que obtem o id do elemento armazenado. 
*  Retorno: Caso exista, retorna um ponteiro para o nó do elemento desejado, caso contrario retorna NULL. */
Node listGetById(List l, char id[], char*(*getId)(void*));

/* Procura por um node na Linked List a partir de seu elemento armazenado.
*  Parâmetros: recebe um ponteiro não nulo para a lista e um tipo void* representando o elemento armazenado dentro do node desejado
*  Retorno: Caso exista, retorna um ponteiro para o nó desejado, caso contrario retorna NULL. */
Node listGetByData(List l, void*data);

/* Desaloca os espaços de memória alocados na criação da lista e inclusive para os valores contidos dentro dos nodes.
*  Parâmetros: Um ponteiro não nulo para a lista e um ponteiro para a funcao utilizada para desalocar o elemento armazenado nos nodes.
*  Retorno: Não possui retorno. */
void freeLista(List l, void(*freeFunc)(void*));

/* Desaloca os espaços de memória alocados na criação da lista e inclusive para os valores contidos dentro dos nodes. Exclusiva para uso na hashTable
*  Parâmetros: Um ponteiro não nulo para a lista e um ponteiro para a funcao utilizada para desalocar o elemento armazenado nos nodes.
*  Retorno: Não possui retorno. */
void freeListaHT(List l, void(*freeFunc)(void*));

/* Similar a função freeLista porém desaloca apenas a memória dos nodes e da lista, sem desalocar a memória de elementos dentro dos nodes.
*  Parâmetros: Um ponteiro não nulo para a lista.
*  Retorno: Não possui retorno. */
void freeLista2(List l);

/* Remove um nó pertencente a lista e não desaloca a memória de seus dados.
*  Parâmetros: Um ponteiro não nulo para a lista e um ponteiro para o nó a ser removido.
*  Retorno: Retorno um void pointer que referência os seus dados. */
void *listRemoveNode(List l, Node node);

/* Remove o primeiro nó de uma lista.
*  Parâmetros: Um ponteiro não nulo para a lista.
*  Retorno: Retorna a informação armazenada dentro do node. */
void *listRemoveFirst(List l);

/* Remove o ultimo nó de uma lista.
*  Parâmetros: Um ponteiro não nulo para a lista.
*  Retorno: Retorna a informação armazenada dentro do node. */
void *listRemoveLast(List l);

/* Obtem o primeiro nó de uma lista.
*  Parâmetros: Um ponteiro não nulo para a lista .
*  Retorno: Caso a lista não esteja vazia, retorna um ponteiro para o primeiro nó, caso contrário retorna NULL. */
Node listGetFirst(List l);

/* Verifica se o nó tem um próximo nó armazenado
*  Parâmentros: Um ponteiro não nulo para o nó
*  Retorno: retorna 1 se tem próximo ou 0 se não existir*/
int nodeHasNext(Node n);

/* Pega o próximo nó de um nó.
*  Parâmetros: Um ponteiro não nulo para um nó.
*  Retorno: Caso o nó recebido por parâmetro possua um próximo nó, retorna um ponteiro para o próximo nó, caso contrário retorna NULL. */
Node nodeGetNext(Node n);

/* Retorna o valor armazenado dentro do node.
*  Parâmetros: Um ponteiro não nulo para o nó.
*  Retorno: Retorna um generic ou um valor nulo caso não haja valores armazenado no node. */
void* nodeGetData(Node n);

/* Obtem o nó anterior de um nó.
*  Parâmetros: Recebe um ponteiro não nulo para um nó.
*  Retorno: Caso o nó recebido por parâmetro possua um nó anterior, retorna um ponteiro para o nó anterior, caso contrário retorna NULL. */
Node nodeGetPrevious(Node n);

/* Obtem o último nó de uma lista.
*  Parâmetros: Um ponteiro não nulo para a lista .
*  Retorno: Caso a lista não esteja vazia, retorna um ponteiro para o último nó, caso contrário retorna NULL. */
Node listGetLast(List l);

/* Insere um elemento na Linked List antes de um certo nó.
*  Parâmetros: Um ponteiro não nulo para a lista , um ponteiro não nulo para o nó específico e um ponteiro não nulo para as informações do elemento a ser inserido.
*  Retorno: Retorna um ponteiro para o nó do elemento adicionado. */
Node listInsertBefore(List l, Node t, void* g);

/* Insere um elemento na Linked List depois de um certo nó.
*  Parâmetros: Um ponteiro não nulo para a lista , um ponteiro não nulo para o nó específico e um ponteiro não nulo para as informações do elemento a ser inserido.
*  Retorno: Retorna um ponteiro para o nó do elemento adicionado */
Node listInsertAfter(List l, Node t, void* g);

#endif