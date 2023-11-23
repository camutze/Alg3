#ifndef TRIE_T
#define TRIE_T

/* 
 * Estrutura de dados para a implementação de uma Trie
 */

#define ALPHABET_SIZE 52
#define TAM_PALAVRA 40
#define TAM_ARQUIVO 100

typedef struct trie_node
{
    struct trie_node *filhos[ALPHABET_SIZE]; // Array de ponteiros para os filhos do nó
    char origem[TAM_ARQUIVO]; // String que armazena a origem da palavra
    int eh_final; // Flag que indica se o nó representa o final de uma palavra
} TrieNode;

/* 
 * Função para criar um novo nó da Trie
 */
TrieNode *cria_nodo_trie();

/* 
 * Função para inserir uma palavra na Trie
 */
void inserir_trie(TrieNode *raiz, const char *palavra, const char *origem);

/* 
 * Função para imprimir todas as palavras da Trie
 */
void print_trie(TrieNode *raiz, char str[], int nivel);

/* 
 * Função para imprimir todas as palavras da Trie que possuem um determinado prefixo
 */
void print_prefix(TrieNode *raiz, const char *prefix);

/* 
 * Função para destruir a Trie e liberar a memória alocada
 */
void destroi(TrieNode *raiz);

/* 
 * Função para verificar se uma string possui caracteres acentuados
 */
int tem_acento(char *str);

/* 
 * Função para remover pontuações de uma string
 */
void retira_pontuacao(char *str);

/* 
 * Função para converter todos os caracteres de uma string para minúsculo
 */
void tudo_minusculo(char *str);

/* 
 * Função para exportar a Trie para um arquivo binário
 */
void export_trie(FILE *base, TrieNode *raiz);

/* 
 * Função para importar a Trie de um arquivo binário
 */
TrieNode *import_trie(FILE *base);

#endif