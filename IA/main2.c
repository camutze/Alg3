#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    char *origin;
};

struct TrieNode *get_node(void)
{
    struct TrieNode *pNode = NULL;
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (pNode)
    {
        int i;
        pNode->origin = NULL;
        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }
    return pNode;
}

void insert(struct TrieNode *root, const char *key, const char *origin)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = get_node();
        pCrawl = pCrawl->children[index];
    }
    pCrawl->origin = strdup(origin);
}

void load_file_into_trie(const char *filename, struct TrieNode *root)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Não foi possível abrir o arquivo %s.\n", filename);
        return;
    }
    char word[100];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Remove acentos, pontos e converte para minúsculas
        int i, j = 0;
        for (i = 0; word[i]; i++)
        {
            char c = tolower(word[i]);
            if ('a' <= c && c <= 'z')
            {
                word[j++] = c;
            }
        }
        word[j] = '\0';
        // Insere na árvore Trie se a palavra tem no mínimo 4 letras
        if (strlen(word) >= 4)
        {
            insert(root, word, filename);
        }
    }
    fclose(file);
}

void print_trie(struct TrieNode *root, char str[], int level)
{
    if (root->origin)
    {
        str[level] = '\0';
        printf("%s: %s\n", str, root->origin);
    }
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            str[level] = i + 'a';
            print_trie(root->children[i], str, level + 1);
        }
    }
}

void save_trie(FILE *file, struct TrieNode *root)
{
    if (root == NULL)
    {
        int nullFlag = 0;
        fwrite(&nullFlag, sizeof(int), 1, file);
    }
    else
    {
        int nullFlag = 1;
        fwrite(&nullFlag, sizeof(int), 1, file);
        // Escreva a origem
        int originLength = strlen(root->origin) + 1;  // +1 para o terminador de string '\0'
        fwrite(&originLength, sizeof(int), 1, file);
        fwrite(root->origin, sizeof(char), originLength, file);
        // Escreva os filhos
        int i;
        for (i = 0; i < ALPHABET_SIZE; i++)
            save_trie(file, root->children[i]);
    }
}

struct TrieNode *load_trie(FILE *file)
{
    int nullFlag;
    fread(&nullFlag, sizeof(int), 1, file);
    if (nullFlag == 0)
    {
        return NULL;
    }
    else
    {
        struct TrieNode *root = get_node();
        // Leia a origem
        int originLength;
        fread(&originLength, sizeof(int), 1, file);
        root->origin = malloc(originLength);
        fread(root->origin, sizeof(char), originLength, file);
        // Leia os filhos
        int i;
        for (i = 0; i < ALPHABET_SIZE; i++)
            root->children[i] = load_trie(file);
        return root;
    }
}

void destroy_trie(struct TrieNode *root)
{
    if (root == NULL)
        return;
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
        destroy_trie(root->children[i]);
    if (root->origin)
        free(root->origin);
    free(root);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uso: %s <arquivo_base> <arquivo_para_inserir>\n", argv[0]);
        return 1;
    }
    struct TrieNode *root = get_node();
    FILE *file = fopen(argv[1], "rb");
    if (file != NULL)
    {
        root = load_trie(file);
        fclose(file);
    }
    load_file_into_trie(argv[2], root);
    file = fopen(argv[1], "wb");
    save_trie(file, root);
    fclose(file);
    char str[100];
    print_trie(root, str, 0);
    destroy_trie(root);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE (26)
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    char *origin;
};

struct TrieNode *get_node(void)
{
    struct TrieNode *pNode = NULL;
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (pNode)
    {
        int i;
        pNode->origin = NULL;
        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }
    return pNode;
}

void insert(struct TrieNode *root, const char *key, const char *origin)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = get_node();
        pCrawl = pCrawl->children[index];
    }
    pCrawl->origin = strdup(origin);
}

void load_file_into_trie(const char *filename, struct TrieNode *root)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Não foi possível abrir o arquivo %s.\n", filename);
        return;
    }
    char word[100];
    while (fscanf(file, "%s", word) != EOF)
    {
        // Remove acentos, pontos e converte para minúsculas
        int i, j = 0;
        for (i = 0; word[i]; i++)
        {
            char c = tolower(word[i]);
            if ('a' <= c && c <= 'z')
            {
                word[j++] = c;
            }
        }
        word[j] = '\0';
        // Insere na árvore Trie se a palavra tem no mínimo 4 letras
        if (strlen(word) >= 4)
        {
            insert(root, word, filename);
        }
    }
    fclose(file);
}

void print_trie(struct TrieNode *root, char str[], int level)
{
    if (root->origin)
    {
        str[level] = '\0';
        printf("%s: %s\n", str, root->origin);
    }
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            str[level] = i + 'a';
            print_trie(root->children[i], str, level + 1);
        }
    }
}

void save_trie(FILE *file, struct TrieNode *root)
{
    if (root == NULL)
    {
        int nullFlag = 0;
        fwrite(&nullFlag, sizeof(int), 1, file);
    }
    else
    {
        int nullFlag = 1;
        fwrite(&nullFlag, sizeof(int), 1, file);
        // Escreva a origem
        int originLength = strlen(root->origin) + 1;  // +1 para o terminador de string '\0'
        fwrite(&originLength, sizeof(int), 1, file);
        fwrite(root->origin, sizeof(char), originLength, file);
        // Escreva os filhos
        int i;
        for (i = 0; i < ALPHABET_SIZE; i++)
            save_trie(file, root->children[i]);
    }
}

struct TrieNode *load_trie(FILE *file)
{
    int nullFlag;
    fread(&nullFlag, sizeof(int), 1, file);
    if (nullFlag == 0)
    {
        return NULL;
    }
    else
    {
        struct TrieNode *root = get_node();
        // Leia a origem
        int originLength;
        fread(&originLength, sizeof(int), 1, file);
        root->origin = malloc(originLength);
        fread(root->origin, sizeof(char), originLength, file);
        // Leia os filhos
        int i;
        for (i = 0; i < ALPHABET_SIZE; i++)
            root->children[i] = load_trie(file);
        return root;
    }
}

void destroy_trie(struct TrieNode *root)
{
    if (root == NULL)
        return;
    int i;
    for (i = 0; i < ALPHABET_SIZE; i++)
        destroy_trie(root->children[i]);
    if (root->origin)
        free(root->origin);
    free(root);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Uso: %s <arquivo_base> <arquivo_para_inserir>\n", argv[0]);
        return 1;
    }
    struct TrieNode *root = get_node();
    FILE *file = fopen(argv[1], "rb");
    if (file != NULL)
    {
        root = load_trie(file);
        fclose(file);
    }
    load_file_into_trie(argv[2], root);
    file =