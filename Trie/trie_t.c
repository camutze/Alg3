#include "trie_t.h"

void tratar_erro(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

trie_node *criar_no(void)
{
    trie_node *novo_no;
    int i;

    if (!(novo_no = malloc(sizeof(trie_node))))
        tratar_erro("ERRO_ALOCACAO");

    novo_no->is_end = 0;
    for (i = 0; i < TAMANHO_ALFABETO; i++)
        novo_no->filhos[i] = NULL;

    return novo_no;
}

void inserir(trie_node *raiz, const char *chave)
{
    trie_node *atual;
    int nivel;
    int comprimento;
    int indice;

    atual = raiz;
    comprimento = strlen(chave);

    for (nivel = 0; nivel < comprimento; nivel++)
    {
        indice = chave[nivel] - 'a';
        if (!atual->filhos[indice])
        {
            atual->filhos[indice] = criar_no();
        }
        atual = atual->filhos[indice];
    }

    atual->is_end = 1;
}

int buscar(trie_node *raiz, const char *chave)
{
    int nivel;
    int comprimento = strlen(chave);
    int indice;
    trie_node *atual = raiz;

    for (nivel = 0; nivel < comprimento; nivel++)
    {
        indice = chave[nivel] - 'a'; // conversao para indice
        if (!atual->filhos[indice])
        {
            return 0;
        }
        atual = atual->filhos[indice];
    }

    return (atual != NULL && atual->is_end);
}

int comeca_com(trie_node *raiz, const char *prefixo)
{
    int nivel;
    int comprimento = strlen(prefixo);
    int indice;
    trie_node *atual = raiz;

    for (nivel = 0; nivel < comprimento; nivel++)
    {
        indice = prefixo[nivel] - 'a';
        if (!atual->filhos[indice])
        {
            return 0;
        }
        atual = atual->filhos[indice];
    }

    return (atual != NULL);
}

void destruir_trie(trie_node *raiz)
{
    if (raiz)
    {
        int i;
        for (i = 0; i < TAMANHO_ALFABETO; i++)
        {
            destruir_trie(raiz->filhos[i]);
        }
        free(raiz);
    }
}
void imprime_palavras(trie_node *raiz, char palavra[], int nivel)
{
    // Verifica se o nó atual é o final de uma palavra
    if (raiz->is_end)
    {
        palavra[nivel] = '\0';   // Adiciona o caractere nulo para indicar o fim da palavra
        printf("%s\n", palavra); // Imprime a palavra encontrada
    }

    int i;
    for (i = 0; i < TAMANHO_ALFABETO; i++)
    {
        if (raiz->filhos[i] != NULL)
        {
            palavra[nivel] = i + 'a';                              // Converte o índice para o caractere correspondente
            imprime_palavras(raiz->filhos[i], palavra, nivel + 1); // Chama recursivamente para o próximo nível
        }
    }
}

void imprime(trie_node *raiz)
{
    char palavra[TAMANHO_ALFABETO + 1]; // +1 para o caractere nulo
    imprime_palavras(raiz, palavra, 0); // Chama a função auxiliar para imprimir as palavras
}
