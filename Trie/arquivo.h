#include <stdlib.h>

#include "arquivo.h"

#define ALFABETO 52
#define MIN_PALAVRA 3
/*O objetivo é criar uma base de dados para localizar palavras em um conjunto de arquivos.
Isso será feito usando árvores digitais (tries) para organizar as palavras contidas nos arquivos.
Cada registro (palavra) indicará a lista de arquivos onde a palavra ocorre.
Esta base de dados será guardada em um arquivo para uso posterior.

*/
typedef struct trie_t
{
    struct nodo_t *raiz;
    int tamanho;
} trie_t;

typedef struct nodo_t
{
    struct nodo_t *filho[ALFABETO];
    char letra;
    int fim;
    int origem;
} nodo_t;

/*cria um ponteiro para a arvore */
trie_t *cria_trie();

/*libera a arvore*/
void libera_trie(trie_t *trie);

/*cria um ponteiro para o nodo
retorna endereço ou NULL em caso de erro*/
nodo_t *cria_nodo(char letra);

/*libera o nodo*/
void libera_nodo(nodo_t *nodo);

/*insere uma palavra na arvore
retorna 1 se sucesso, 0 se falha*/
int insere_trie(trie_t *trie, char *palavra, int origem);

/*insere uma palavra no nodo, 
retorna 1 se sucesso, 0 se falha*/
int insere_nodo(nodo_t *nodo, char *palavra, int origem);

/*busca uma palavra na arvore
retorna 1 se sucesso, 0 se falha*/
int busca_trie(trie_t *trie, char *palavra);

/*busca uma palavra no nodo
retorna 1 se sucesso, 0 se falha*/
int busca_nodo(nodo_t *nodo, char *palavra);
