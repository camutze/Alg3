
typedef struct arvore
{
    struct nodo *raiz;
} arvore;

typedef struct nodo
{
    int r;
    struct nodo *esq;
    struct nodo *dir;
    short alt; /* Balanceamento do nodo. */
} nodo;

/* Cria um ponteiro que aponta para a raiz e o retorna. */
arvore *cria_arvore();

/* Cria um nodo. Em caso de sucesso, retorna o nodo. */
nodo *cria_nodo(int r);

/* Realiza a busca na arvore, retorna 0 caso chave buscada nao esteja presente, e 1 se estiver. */
int busca(nodo *no, int r);

/* Imprime a arvore. */
void imprime(nodo *no);

/* Cria um novo nodo com o valor passado pelo usuario e o insere no lugar correto da arvore. */
nodo *insere_nodo(nodo *raiz, int r);

/* Faz a remocao de um nodo com o valor passado pelo usuario. */
nodo *remove_nodo(nodo *raiz, int r);

/* Implementa as rotacoes na arvore quando existe desbalanceamento. */
nodo *balancear(nodo *raiz);

/* Rotacao simples para a direita. */
nodo *rotacao_dir(nodo *raiz);

/* Rotacao simples para a esquerda. */
nodo *rotacao_esq(nodo *raiz);

/* Rotacao dupla para a direita. */
nodo *rotacao_esq_dir(nodo *raiz);

/* Rotacao dupla para a esquerda. */
nodo *rotacao_dir_esq(nodo *raiz);

/* Calcula o fator de balanceamento, dado por (altura esquerda - altura direita). */
short fator_balanceamento(nodo *no);

/* Retorna a altura de um determinado nodo. */
short alt_no(nodo *no);

/* Retorna o maior entre dois valores a e b. */
short maior(int a, int b);

/* Retorna o nodo raiz. */
nodo *retorna_raiz(arvore *avl);

/* Atribui o valor para raiz. */
void salva_raiz(arvore *avl, nodo *raiz);

/* Destroi a arvore e da free nos nodos. */
void destruir_arvore(nodo *no);