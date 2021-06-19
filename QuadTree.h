#ifndef _H_QTREE
#define _H_QTREE
#include "generico.h"
#include "list.h"

typedef void *QuadNode;
typedef void *QuadTree;

typedef void* ExtraInfo;
typedef char *key;

typedef key getKey(void*); // void* -> tads

typedef void funcVisita(Generic, ExtraInfo);

/**
    Inicializa uma quadtree vazia. "f" é uma funcao que retorna a chave de ordenacao do dado armazenado.
    Parametros: Um ponteiro nao nulo para a funcao que retorna a chave de ordenacao do elemento armazenado.
    Retorno: retorna um ponteiro para a quadtree criada
 */
QuadTree createQuadTree(getKey idFunc);

/**
    Cria uma lista contendo as chaves de ordenacao de todas as informacoes
    cujas coordenas associadas (no momento da insercao) estao dentro do
    retangulo determinado pelo vertices opostos (x1,y1) e (x2,y2).
    A memoria é alocada para cada chave armazenada na lista, portanto,
    é seguro (e recomendavel) desaloca-la quando a respectiva chave nao for mais necessaria.
    É recomendavel que a lista retornada seja desalocada completamente apos ser usada, incluindo os elementos armazenados dentro dos nodes da lista.
    Retorno: retorna a lista contendo os elementos completamento dentro do retangulo.
*/
List QtChavesDentroRetangulo(QuadTree tree, double x1, double y1, double x2, double y2);

/**
    Similar a funcao QtChavesDentroRetangulo(). Retorna a chave cuja
    coordenada é interna a circunferencia de raio r e centro em (x,y).
*/
List QtChavesDentroCirculo(QuadTree tree, double x, double y, double r);

/**
    Similar a funcao QtChavesDentroRetangulo().Porem, retorna a coordenada geografica (Ponto)
    associada a informacao. Memoria tambem é alocada para cada ponto retornado na lista.
*/
List QtPontosDentroRetangulo(QuadTree tree, double x1, double y1, double x2, double y2);

/**
    Similar a funcao QtPontosDentroRetangulo(). Retorna pontos internos
    a circunferencia de raio r e centro em (x,y).
*/
List QtPontosDentroCirculo(QuadTree tree, double x, double y, double r);

/**
    Similar a funcao QtPontosDentroRetangulo(). Retorna apontadores para elemento armazenados dentro dos
    nos da árvore contendo informacoes cuja coordenada esta dentro da região de busca.
    Apenas as memorias da lista e dos nodes da lista deve ser desalocadas, sem desalocar memoria de elementos armazenados dentro de nodes.
*/
List QtNosDentroRetangulo(QuadTree tree, double x1, double y1, double x2, double y2);

/**
    Similar a funcaoo nosDentroRetanguloQt(). Retorna elementos armazenados em nos internos
    a circunferencia de raio r e centro em (x,y).
*/
List QtNosDentroCirculo(QuadTree tree, double x, double y, double r);

/**
    Percorre a arvore em profundidade. Em cada no visitado invoca
    a funcao f. Seja pInfo o valor retornado pela operacao QtgetInfo()
    aplicada ao node visitado; a invocacao de f é da forma: f(pInfo,e)
 */
void QtPercorreProfundidade(QuadTree tree, funcVisita f, ExtraInfo e);

/**
    Semelhante a QtPercorreProfundidade. Percorre a arvore em largura.
 */
void QtPercorreLargura(QuadTree tree, funcVisita f, ExtraInfo e);

/**
    Insere na arvore a informacao "Info", associada a coordenada referente ao ponto "p".
    Retorna referencia ao no da arvore onde a pInfo foi armazenada.
 */
QuadNode QtInsert(QuadTree tree, Ponto p, void *info);

/**
    Marca como removido da arvore o no referenciado por "node". O no ainda existe na arvore, mas a informacao armazenada dentro dele nao pode ser acessada.
    "node" deve referenciar um no valido dentro da arvore.
    Retorna a informacao contida no nó removido.
 */
Generic QtRemoveNode(QuadTree tree, QuadNode node);

/** Reconstroi uma quadtree retirando os elementos marcados como removidos.
 *  Essa funcao zera a variavel qtdRemovidos, desaloca memoria dos nodes antigos e aloca memoria para novos nodes, sem alterar os ponteiros dos elementos armazenados dentro dos nodes.
 *  Parametros: Um ponteiro nao nulo para a quadtree.
 *  Retorno: Não possui retorno. */
void QtRefazArvore(QuadTree tree);

/**
    Retorna uma referencia ao no da arvore associado a coordenada (x,y).
    Retorna NULL, caso nao exista tal no ou esteja marcado como removido.
 */
QuadNode QtGetNode(QuadTree tree, double x, double y);

/**
    Retorna a informacao armazenada na arvore no no referenciiado por "node".
    "node" deve referenciar um no valido dentro da arvore.
    Caso o node esteja marcado como deletado retorna NULL;
 */

Generic QtGetInfo(QuadTree tree, QuadNode node);

/**
    Libera memoria alocada pela implementacao da arvore. Desaloca apenas memoria alocada por createQuadTree() e os
    nos da arvore criados por QtInsert() e os elementos armazenados dentro dos nós. Nao desaloca as listas retornadas nas consultas
    espaciais (Qt_*_DentroRetangulo() e Qt_*_DentroCirculo()).
    Parametros: Um ponteiro nao nulo para a quadtree e um ponteiro nao nulo para a funcao utilizada para desalocar o elemento armazenado nos nodes.
    Retorno: Nao possui retorno.
 */
void freeQt(QuadTree tree, void(*freeNodeData)(void*)); 

/**
    Libera memoria alocada pela implementacao da arvore. Desaloca  memoria alocada por createQuadTree() e os
    nos da arvore criados por QtInsert(). Nao desaloca as listas retornadas nas consultas
    espaciais (Qt_*_DentroRetangulo() e Qt_*_DentroCirculo()).
    Parametros: Um ponteiro nao nulo para a quadtree.
    Retorno: Nao possui retorno.
 */
void freeQt2(QuadTree tree); 

/** Obtem o primeiro node de uma quadtree.
 *  Parametros: Um ponteiro nao nulo para a quadtree.
 *  Retorno: Retorna um QuadNode contendo a raiz da quadtree. 
*/
QuadNode QtGetRoot(QuadTree tree);

/** Obtem um quadnode a partir do id utilizando getKey percorrendo a quadtree por profundidade.
 *  Parametros: Um ponteiro nao nulo para a quadtree e uma string contendo o id do elemento armazenado no node.
 *  Retorno: Retorna o QuadNode que contem o elemento desejado caso exista, caso contrario retorna NULL.
*/
QuadNode QtGetById(QuadTree tree, char *id);

/** Obtem o pai de um node da quadtree.
 *  Parametros: Um ponteiro nao nulo para o node da quadtree.
 *  Retorno: Retorna um QuadNode contendo o pai de tree. 
*/
QuadNode QtGetParent(QuadNode tree);

/** Obtem o node NW de um node da quadtree.
 *  Parametros: Um ponteiro nao nulo para o node da quadtree.
 *  Retorno: Retorna um QuadNode contendo o node NW de tree. 
*/
QuadNode QtGetNW(QuadNode tree);

/** Obtem o node NE de um node da quadtree.
 *  Parametros: Um ponteiro nao nulo para o node da quadtree.
 *  Retorno: Retorna um QuadNode contendo o node NE de tree. 
*/
QuadNode QtGetNE(QuadNode tree);

/** Obtem o node SW de um node da quadtree.
 *  Parametros: Um ponteiro nao nulo para o node da quadtree.
 *  Retorno: Retorna um QuadNode contendo o node SW de tree. 
*/
QuadNode QtGetSW(QuadNode tree);

/** Obtem o node SE de um node da quadtree.
 *  Parametros: Um ponteiro nao nulo para o node da quadtree.
 *  Retorno: Retorna um QuadNode contendo o node SE de tree. 
*/
QuadNode QtGetSE(QuadNode tree);

/** Obtem a quantidade elemento marcados como removidos em uma quadtree.
 *  Parametros: Um ponteiro nao nulo para a quadtree.
 *  Retorno: Um inteiro representando a quantidade de elementos marcados como removidos
*/
int QtGetQtdRemovidos(QuadTree tree);

/** Obtem a quantidade elemento de uma quadtree. Essa funcao não considera os elemento marcados como removidos mas ainda presentes na quadtree.
 *  Parametros: Um ponteiro nao nulo para a quadtree.
 *  Retorno: Um inteiro representando a quantidade de elementos validos da quadtree.
*/
int QtGetLenght(QuadTree tree);

/** Insere os elementos de uma lista em uma quadtree em uma determinada ordem.
 *  A ordem consiste em calcular a envoltoria convexa dos elementos da lista e inserindo em uma pilha repetidamente até a lista estiver vazia e em seguida remover os elementos da pilha e adicionar na quadtree
 *  Parametros: Um ponteiro nao nulo para a quadtree e um ponteiro nao nulo para a lista contendo os elementos.
 *  Retorno: Nao possui retorno.
*/
void QtOrdenarInsercao(QuadTree tree, List lista);

/** Cria uma lista contendo todos os elementos armazenados em uma quadtree. A lista deve ter sua memória desalocada utilizando a função freeLista2
 *  Parametros: Um ponteiro nao nulo para a quadtree.
 *  Retorno: Uma lista contendo todos os elementos armazenados em uma quadtree.
*/
List QuadTToList(QuadTree tree);

#endif