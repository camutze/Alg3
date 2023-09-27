typedef struct arvore
{
    struct nodo *raiz;

} arvore;

typedef struct nodo
{
    int r;
    struct nodo *esq;
    struct nodo *dir;
    int alt; // balanceamento do nodo

} nodo;

/*cria um ponteiro que aponta para a raiz */
arvore *cria_arvore();

/*retorna um endereço de um nodo */
nodo *cria_nodo(int r);

int busca(nodo *no, int r);

void imprime(nodo *no);

nodo *procura_menor(nodo *atual);

int insere_nodo(nodo **raiz, int r);

int remove_nodo(nodo **raiz, int r);

int fator_balanceamento(nodo *no);

void rotacao_esq(nodo **raiz);

void rotacao_dir(nodo **raiz);

void rotacao_esq_dir(nodo **raiz);

void rotacao_dir_esq(nodo **raiz);

void destruir_arvore(nodo *no);

int alt_no(nodo *no);

int maior(int a, int b);
