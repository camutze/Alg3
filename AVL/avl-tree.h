
typedef struct arvore
{
    struct nodo *raiz;

} arvore;

typedef struct nodo
{
    int r;
    struct nodo *esq;
    struct nodo *dir;
    short alt; /* balanceamento do nodo*/

} nodo;

/*cria um ponteiro que aponta para a raiz */
arvore *cria_arvore();

/*retorna um endereço de um nodo */
nodo *cria_nodo(int r);

int busca(nodo *no, int r);

void imprime(nodo *no);

nodo *insere_nodo(nodo *raiz, int r);

nodo *remove_nodo(nodo *raiz, int r);

/*comentar*/
nodo *balancear(nodo *raiz);

nodo *rotacao_dir(nodo *raiz);

nodo *rotacao_esq(nodo *raiz);

nodo *rotacao_esq_dir(nodo *raiz);

nodo *rotacao_dir_esq(nodo *raiz);

short fator_balanceamento(nodo *no);

short alt_no(nodo *no);

short maior(int a, int b);

nodo *retorna_raiz(arvore *avl);

void salva_raiz(arvore *avl, nodo *raiz);

void destruir_arvore(nodo *no);