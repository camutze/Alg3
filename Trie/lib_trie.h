#ifndef TRIE_T
#define TRIE_T

#define ALPHABET_SIZE 52
#define TAM_PALAVRA 40
#define TAM_ARQUIVO 100

typedef struct trie_node
{
    struct trie_node *children[ALPHABET_SIZE];
    char origem[TAM_ARQUIVO]; // Adiciona campo para armazenar a origem do arquivo
    int is_end_of_word;
} TrieNode;


TrieNode *get_node();

void insert(TrieNode *root, const char *word, const char *origem);

void print_trie(TrieNode *root, char str[], int level);

void print_prefix(TrieNode *root, const char *prefix);

void destroy(TrieNode *root);

int tem_acento(char *str);

void retira_pontuacao(char *str);

void tudo_minusculo(char *str);

void export_trie(FILE *base, TrieNode *root, char str[], int level);

void import_trie(FILE *base, TrieNode *root);

#endif