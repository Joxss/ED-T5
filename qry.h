/* 
    Esse header possui funções que lidam com os comandos específicos de arquivos .qry.
    As descrições dos comandos qry são superficiais não contendo todos os detalhes especificados no pdf do trabalho
*/

#ifndef QRY_H
#define QRY_H

#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "QuadTree.h"
#include "hashTable.h"
#include "pessoa.h"
#include "morador.h"
#include "estabelecimento.h"
#include "grafo.h"

/* Executa a qry pnt - Modifica as cores de um determinado círculo retângulo ou texto.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, um ponteiro não nulo para as quadtrees que armazenam circulos retângulos e textos, 
               um inteiro representando o identificador do elemento, e duas string representando as cores da borda e de preenchimento 
*  Retorno: Não possui retorno. */
void qryPnt(FILE *txt, QuadTree circulos, QuadTree Retangulos, QuadTree textos, int id, char corBorda[], char corPreench[]);

/* Executa a qry pnt* - Modifica as cores de todos os circulos retângulos e textos dentro de um intervalo.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, um ponteiro não nulo para as quadtrees que armazenam circulos retângulos e textos, 
               dois inteiros representando o inicio e o fim do intervalo que serão modificadas as cores, e duas string representando as cores da borda e de preenchimento 
*  Retorno: Não possui retorno. */
void qryPntAll(FILE *txt, QuadTree circulos, QuadTree Retangulos, QuadTree textos, int inicio, int fim, char corBorda[], char corPreench[]);

/* Executa a qry delf - Remove um determinado elemento.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, um ponteiro não nulo para as quadtrees que armazenam circulos retângulos e textos, 
               e um inteiro representando o identificador do elemento.
*  Retorno: Não possui retorno. */
void qryDelf(FILE *txt, QuadTree circulos, QuadTree retangulos, QuadTree textos, int id);

/* Executa a qry delf - Remove todos os elementos dentro de um intervalo.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, um ponteiro não nulo para as quadtrees que armazenam circulos retângulos e textos, 
               e dois inteiros representando o inicio e o fim do intervalo que serão removidos os elementos.
*  Retorno: Não possui retorno. */
void qryDelfAll(FILE *txt, QuadTree circulos, QuadTree retangulos, QuadTree textos, int inicio, int fim);

/* Executa a qry i? - Checa se um ponto é interno a um determinado circulo ou retângulo.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, um ponteiro não nulo para as quadtrees de circulos e retangulos, 
               um ponteiro não nulo para a lista que armazena os elementos criados por qrys, um inteiro que representa o identificador do elemento selecionado 
               e as coordenadas do ponto que sera checado.
*  Retorno: Não possui retorno. */
void iQry(FILE *txt, QuadTree circulos, QuadTree retangulos, List qryFigures,int id, double x, double y);

/* Executa a qry o? - Checa se dois elementos (círculos ou retângulos) se sobrepoem.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, um ponteiro não nulo para as quadtrees de circulos e retangulos, 
               um ponteiro não nulo para a lista que armazena os elementos criados por qrys e dois inteiros que representao o identificador dos elementos que serão checados.
*  Retorno: Não possui retorno. */
void oQry(FILE *txt, QuadTree circulos, QuadTree retangulos, List qryFigures, int id1, int id2);

// ------------------------------------ T2 --------------------------------- //

/* Executa a qry dq - Remove (ou arredonda a borda de) todas as quadras que estiverem completamente dentro de um circunferencia com centro em um determinado equipamento urbano.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, um ponteiro nao nulo para a hashtable cepXquadra, 
               ponteiros não nulos para as quadtrees de quadras, hidrantes, semaforos, radios, um ponteiro nao nulo para a lista de elementos criados por qrys
               uma string que representa o identificador do elemento selecionado, um double que representa o raio da circunferência 
               e um inteiro que representa se o parâmetro opcional está presente ou não. 
*  Retorno: Não possui retorno. */
void qryDq(FILE *txt, Htable cepXquadra, QuadTree quadras, QuadTree hidrantes, QuadTree semaforos, QuadTree radios, List qryFigures, char id[], double r, int opcional);

/* Executa a qry del - Remove uma quadra ou equipamento urbano específico.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, um ponteiro nao nulo para a hashtable cepXquadra,
               ponteiros não nulos para as quadtrees de quadras, hidrantes, semaforos, radios, um ponteiro nao nulo para a lista de elementos criados por qrys
               e uma string que representa o identificador de elemento selecionado
*  Retorno: Não possui retorno. */
void qryDel(FILE *txt, Htable cepXquadra, QuadTree quadras, QuadTree hidrantes, QuadTree semaforos, QuadTree radios, List qryFigures, char id[]);

/* Executa a qry cbq - Muda a cor da borda de todas as quadras que estiverem completamente dentro de uma circunferência.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, ponteiro não nulo para a quadtree de quadras,
               tres doubles representando a coordenada x, y e raio da circunferencia e um ponteiro nao nulo para a lista de elementos criados por qrys.
*  Retorno: Não possui retorno. */
void qryCbq(FILE *txt, QuadTree quadras, double x, double y, double r, char corBorda[], List qryFigures);

/* Executa a qry crd - Imprime na saida txt as informações de uma determinada quadra ou equipamento urbano.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, ponteiros não nulos para as quadtrees de quadras, hidrantes, semaforose e radios
               e uma string contendo o identificador do elemento selecionado.
*  Retorno: Não possui retorno. */
void qryCrd(FILE *txt, QuadTree quadras, QuadTree hidrantes, QuadTree semaforos, QuadTree radios, char id[]);

/* Executa a qry car - Calcula a area total de todas as quadras completamente dentro de um retângulo.
*  Parâmetros: Recebe um ponteiro não nulo para o arquivo txt, um ponteiro não nulo para a quadtree de quadras, um ponteiro nao nulo para a lista de elementos criados por qrys
               e quatro doubles representando a coordenada x, y, a altura e largura do retângulo.
*  Retorno: Não possui retorno. */
void qryCar(FILE *txt, QuadTree quadras, List qryFigures, double x, double y, double w, double h);

/* Executa a qry cv - Cria um quadrado que representa a quantidade de casos de covid em determinado endereço
*  Parâmetros: Um ponteiro nao nulo para a quadtree de casos covid, um ponteiro nao nulo para a hashtable cepXquadra,
               a quantidade de casos, o cep relativo a quadra, a face da quadra e o numero de endereço.
*  Retorno: Não possui retorno. */
void qryCv(QuadTree casosCv, Htable cepXquadra, int n, char id[], char face, double num);

/* Executa a qry ci - Calcula a envoltoria convexa de todos os quadrados dentro de um determinado raio
*  Parâmetros: Recebe o arquivo txt, um ponteiro nao nulo para as quadtrees de postos, casos de covid e densidades, um ponteiro nao nulo para
               a lista que armazena figuras criadas por qrys, e os valores x y e r da circunferencia.
*  Retorno: Não possui retorno. */
void qryCi(FILE *txt, QuadTree postos, QuadTree casosCv, QuadTree densidade, List qryFigures, double x, double y, double r);

/* Executa a qry soc - Encontra os k postos de saude mais proximos de um determinado endereço
* Parametros: Recebe o arquivo txt, um ponteiro nao nulo para a quadtree de postos, um ponteiro nao nulo para a hashtable cepXquadra,
              a lista que armazena figuras criadas por qrys, a quantidade de postos desejada,
              o cep da quadra relativa ao endereço, a face dessa quadra e o numero de endereço
* Retorno: Não possui retorno*/
void qrySoc(FILE *txt, QuadTree postos, Htable cepXquadra, List qryFigures, int k, char * cep, char face, double num);

// ------------------- T4 ------------------------//

/* Executa a qry M? - Encontra todos os moradores da quadra cujo cep é cep. Mostra mensagem de erro no txt se quadra não existir.
* Parametros: Recebe o arquivo txt, as hash tables cpfXpessoa, cepXquadra e o cep da quadra;
* Retorno: Não possui retorno*/
void qryM(FILE *txt, Htable cpfXpessoa, Htable cepXquadra, char *cep);

/* Executa a qry Dm? - Imprime todos os dados do morador identificado pelo cpf.
* Parametros: Recebe o arquivo txt, uma lista contendo as figuras a serem inseridas no svg, uma quadtree nao nula de moradores, uma hash table cpfXpessoa e o cpf do morador a ser identificado;
* Retorno: Não possui retorno*/
void qryDm(FILE *txt, List qryFigures, QuadTree moradores, Htable cpfXpessoa, char *cpf);

/* Executa a qry De? - Imprime todos os dados do estabelecimento comercial identificado por cnpj.
* Parametros: Recebe o arquivo txt, uma quadtree nao nula de estabelecimentos, uma hash table do tipo cpfXpessoa e o cnpj do estabelecimento a ser identificado;
* Retorno: Não possui retorno*/
void qryDe(FILE *txt, QuadTree estabelecimentos, Htable cpfXpessoa, char *cnpj);

/* Executa a qry Mud - Faz a mudança da pessoa identificada por cpf para o endereço determinado pelos parâmetros. Escreve no txt as informacoes da pessoa, seu endereco novo e antigo.
* Parametros: Recebe o arquivo txt, uma quadtree nao nula de moradores, hash tables do tipo cpfXpessoa e cpfXcep, uma lista de figuras a serem inseridas no svg e o cpf, cep, face, num e complemento da quadra de mudanca;
* Retorno: Não possui retorno*/
void qryMud(FILE *txt, QuadTree moradores, Htable cepXquadra, Htable cpfXpessoa, Htable cpfXcep, List qryFigures, char *cpf, char *cep, char face, int num,char *compl);

/* Executa a qry Dmprbt - Imprime o estado atual da arvore no arquivo svg. 
* Parametros: Recebe uma quadtree nao nula e um string que referencia o caminho e nome do arquivo com sufixo;
* Retorno: Não possui retorno*/
void qryDmprbt(QuadTree tree, char *path);

/* Executa a qry Eplg? - Estabelecimentos comerciais do tipo tp (ou de qualquer tipo, caso *) que estão inteiramente dentro da região retangular especificada.
* Parametros: Recebe o arquivo txt, uma quadtree nao nula de estabelecimentos, hash tables do tipo tipoXdescricao e cpfXpessoa, uma lista de figuras a serem inseridas no svg e as coordenadas x,y,w,h do retangulo e o codigo do tipo do estabelecimento.
* Retorno: Não possui retorno*/
void qryEplg(FILE *txt, QuadTree estabelecimentos, Htable tipoXdescricao, Htable cpfXpessoa ,List qryFigures, double x, double y, double w, double h, char *tipo);

/* Executa a qry Catac? - Remove as quadras, elementos urbanos,moradores e estabelecimentos comerciais que estejam inteiramente contidas na circunferência de raio r e centro em x y.
* Parametros: Recebe o arquivo txt, ponteiros nao nulos para quadtrees de quadras, hidrantes, semaforos, radios, moradores, estabelecimentos,
              um ponteiro nao nulo para a lista de elemento criados por qrys e 3 doubles representando os valores x y e r da circunferencia
* Retorno: Não possui retorno*/
void qryCatac(FILE *txt, QuadTree quadras, QuadTree hidrantes, QuadTree semaforos, QuadTree radios, QuadTree moradores, QuadTree estabelecimentos, List qryFigures, double x, double y, double r);


// ------------------- T5 ------------------------//
void qryCCV(QuadTree trees[], Grafo ruas, char path[]);

void qryP(QuadTree trees[], Grafo ruas, Ponto inicio, Ponto destino, char corCurto[], char corRapido[], char pathSvg[], FILE *pathTxt);

#endif