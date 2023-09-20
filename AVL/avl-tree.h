typedef struct arvore
{
    struct nodo *raiz;

} arvore;

typedef struct nodo
{
    int r;
    struct nodo *esq;
    struct nodo *dir;

} nodo;


/*cria um ponteiro que aponta para a raiz */
arvore *cria_arvore();

/*retorna um endereço de um nodo */
nodo *cria_nodo(int r);

nodo *busca(nodo *no, int r);

int insere(nodo *no, int r);

int remover(nodo *no, int r);

nodo *rotacao_esq(nodo *no);

int rotacao_dir(nodo *no);

void imprime(nodo *no);

void destruir_arvore(nodo *no);
