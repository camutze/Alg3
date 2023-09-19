typedef struct nodo
{
    int dado;
    struct nodo *esq;
    struct nodo *dir;

} nodo;

typedef struct arvore
{
    nodo *      raiz;

} arvore;

arvore *cria_arvore();

nodo *cria_nodo(int dado);

nodo *busca(nodo *ipe, int dado);

int insere(nodo *ipe, int dado);

void imprime(nodo *pai);

int remover(nodo *pai, int dado);

int destruir_arvore();
