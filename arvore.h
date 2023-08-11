typedef struct nodo
{
    int dado;
    struct nodo *esq;
    struct nodo *dir;

} nodo;

typedef struct arvore
{
    nodo *raiz;

} arvore;

arvore *cria_arvore();

nodo *cria_nodo(int dado);

nodo *busca(arvore *ipe, int dado);

int insere(arvore *ipe, int dado);


int remove();

void imprime(arvore *ipe);
