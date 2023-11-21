#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 52
#define TAM_PALAVRA 40
#define TAM_ARQUIVO 100

typedef struct trie_node
{
    struct trie_node *children[ALPHABET_SIZE];
    char origem[TAM_ARQUIVO]; // Adiciona campo para armazenar a origem do arquivo
    int is_end_of_word;
} TrieNode;

TrieNode *get_node()
{
    TrieNode *node = (TrieNode *)malloc(sizeof(TrieNode));
    node->is_end_of_word = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;
    return node;
}

void insert(TrieNode *root, const char *word, const char *origem)
{
    int index;
    TrieNode *pCrawl = root;
    while (*word != '\0')
    {
        index = *word - 'a';
        if (pCrawl->children[index] == NULL)
        {
            pCrawl->children[index] = get_node();
            strcpy(pCrawl->children[index]->origem, origem); // Copia a origem para o novo nó
        }
        pCrawl = pCrawl->children[index];
        word++;
    }
    pCrawl->is_end_of_word = 1;
}

void print_trie(TrieNode *root, char str[], int level)
{
    if (root->is_end_of_word)
    {
        str[level] = '\0';
        printf("%s ", str);
        printf("%s\n", root->origem);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            str[level] = i + 'a';
            print_trie(root->children[i], str, level + 1);
        }
    }
}

void print_prefix(TrieNode *root, const char *prefix)
{
    printf("Palavras com prefixo %s:\n", prefix);
    TrieNode *pCrawl = root;
    while (*prefix != '\0')
    {
        int index = *prefix - 'a';
        if (!pCrawl->children[index])
            return;
        pCrawl = pCrawl->children[index];
        prefix++;
    }

    char str[TAM_PALAVRA];
    print_trie(pCrawl, str, 0);
}

void destroy(TrieNode *root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i] != NULL)
            destroy(root->children[i]);
    free(root);
}

int tem_acento(char *str)
{
    char *acentuadas = "ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÝàáâãäåçèéêëìíîïðòóôõöùúûüýÿ";
    size_t i, j;

    for (i = 0; i < strlen(str); i++)
    {
        for (j = 0; j < strlen(acentuadas); j++)
        {
            if (str[i] == acentuadas[j])
            {
                return 1; // Retorna 1 se encontrar um acento a ser ignorado
            }
        }
    }
    return 0; // Retorna 0 se não encontrar acentos a serem ignorados
}

void retira_pontuação(char *str)
{
    int len = strlen(str);
    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if (!ispunct(str[i]))
        {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

void tudo_minusculo(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (isupper(str[i]))
        {
            str[i] = tolower(str[i]); // converte para minuscula
        }
    }
}

void export_trie(FILE *base, TrieNode *root, char str[], int level)
{
    if (root->is_end_of_word)
    {
        str[level] = '\0';
        fprintf(base, "%s ", str);
        fprintf(base, "%s\n", root->origem);
    }

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            str[level] = i + 'a';
            export_trie(base, root->children[i], str, level + 1);
        }
    }
}

void import_trie(FILE *base, TrieNode *root)
{
    char word[TAM_PALAVRA];
    char origem[TAM_ARQUIVO];

    while (fscanf(base, "%s %s", word, origem) == 2)
    {
        insert(root, word, origem);
    }
}

int main(int argc, char *argv[])
{
    TrieNode *root;
    FILE *base, *arquivo;
    root = get_node();

    if (argc != 3)
    {
        printf("Uso: %s <arquivo base de dados> <arquivo de saída>\n", argv[0]);
        return 1;
    }
    if (!(base = fopen(argv[1], "r")))
    {
        printf("Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }
    if (!(arquivo = fopen(argv[2], "r")))
    {
        printf("Erro ao abrir o arquivo %s\n", argv[2]);
        return 1;
    }
    import_trie(base, root);
    /*while (!feof(arquivo))
    {
        char palavra[TAM_PALAVRA];
        fscanf(arquivo, "%25s", palavra);
        retira_pontuação(palavra);
        tudo_minusculo(palavra);
        if (!tem_acento(palavra) && strlen(palavra) >= 4)
            insert(root, palavra, argv[2]);
    }*/

    char str[TAM_PALAVRA];
    //export_trie(base, root, str, 0);
    fclose(arquivo);
    fclose(base);

    print_trie(root, str, 0);
    printf("\n\n");
    print_prefix(root, "ca");

    destroy(root);
    return 0;
}
