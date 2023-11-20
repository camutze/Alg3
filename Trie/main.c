#include <stdio.h>
#include <stdlib.h>
#define ALPHABET_SIZE 26
#define MAX_WORD_LENGTH 20

typedef struct trie_node
{
    struct trie_node *children[ALPHABET_SIZE];
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

void insert(TrieNode *root, const char *word)
{
    int index;
    TrieNode *pCrawl = root;
    while (*word != '\0')
    {
        index = *word - 'a';
        if (pCrawl->children[index] == NULL)
            pCrawl->children[index] = get_node();
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
        printf("%s\n", str);
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
    printf("Palavras com prefixo %s: ", prefix);
    TrieNode *pCrawl = root;
    while (*prefix != '\0')
    {
        int index = *prefix - 'a';
        if (!pCrawl->children[index])
            return;
        pCrawl = pCrawl->children[index];
        prefix++;
    }

    char str[MAX_WORD_LENGTH];
    print_trie(pCrawl, str, 0);
}

void destroy(TrieNode *root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i] != NULL)
            destroy(root->children[i]);
    free(root);
}

int main()
{
    TrieNode *root = get_node();
    insert(root, "palavra");
    insert(root, "palavro");
    insert(root, "palavre");
    insert(root, "palavri");
    insert(root, "palavru");
    insert(root, "palavroo");
    insert(root, "carro");
    insert(root, "carroca");
    insert(root, "carroceiro");
    insert(root, "carroceria");
    insert(root, "carrocerias");
    insert(root, "carrocerias");
    insert(root, "carrocerias");

    char str[MAX_WORD_LENGTH];
    print_trie(root, str, 0);
    print_prefix(root, "carr");
    destroy(root);
    return 0;
}
