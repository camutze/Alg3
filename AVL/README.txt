Biblioteca AVL Tree

Nome:
Camila H. GRR20222552
Carlos A. T. Mutzenberg GRR20215520

ESPECIFICAÇÕES: 

- struct arvore: Feito para encapsulamento, por motivos estéticos e 
facilidade do uso. Contem uma variavel nodo denominada raiz.

- struct nodo: Cada no de uma arvore. Contém a chave r, os ponteiros 
direito (*dir) e esquerdo(*esq).

- func arvore *cria_arvore(): Aloca espaco para uma struct arvore *avl e retorna
o ponteiro para ela.

- func nodo *cria_nodo(int r): Aloca espaco para um nodo *filho e retorna o ponteiro
para ele.

- func int busca(nodo *no, int r): Realiza a busca de um nodo com valor passado pelo usuario r.
Varre primeiro o lado esquerdo e depois o lado direito da arvore. Retorna 0 caso nao ache o elemento
e 1 caso ache. 

- func void imprime(nodo *no): Imprime a arvore no visual da especificacao.

- func nodo *insere_nodo(nodo *raiz, int r): Verifica se existe nodo raiz. Se nao, cria
um novo nodo usando a funcao cria_nodo(). Havendo nodo, procura o local correto para ele 
na arvore e o insere. Em seguida, refaz o calculo da altura e faz o balanceamento da arvore.

- func nodo *remove_nodo(nodo *raiz, int r): Faz a remocao do nodo especificado pelo usuario.
Se uma raiz nula for encontrada, o valor nao esta na arvore. Se o elemento for encontrado, existem 
3 possiveis casos para a remocao: 
Sem filhos - caso 1 - Apenas da free() no nodo e returna null.
Dois filhos - caso 2 - Usa um auxiliar para realizar a troca de posicao do elemento a ser removido
com um de seus filhos. O nodo passara a ter apenas um filho ou entao nenhum. 
Um filho - caso 3 - salva o filho em um auxiliar aux, em seguida da free() no nodo a ser removido e 
retorna o auxiliar aux.

-func nodo *balancear(nodo *raiz): Faz as chamadas para as funcoes de rotacao com base no tipo
do desequilibrio apresentado. 

- func nodo *rotacao_dir(nodo *raiz): Realiza uma rotacao simples para a direita. Similar a um
procedimento de troca com auxiliar. Depois disso, atualiza a altura da arvore.

- func nodo *rotacao_esq(nodo *raiz): Realiza uma rotacao simples para a esquerda. Similar a um
procedimento de troca com auxiliar. Depois disso, atualiza a altura da arvore.

- func nodo *rotacao_esq_dir(nodo *raiz): Realiza uma rotacao para a esquerda e depois para a direita.
A altura sera atualizada pelo procedimento realizado dentro das funcoes chamadas.

- func nodo *rotacao_dir_esq(nodo *raiz): Realiza uma rotacao para a direita e depois para a esquerda.
A altura sera atualizada pelo procedimento realizado dentro das funcoes chamadas.

- func hort fator_balanceamento(nodo *no):  Calcula o fator de balanceamento, dado por altura esquerda - altura direita

- func short alt_no(nodo *no): Retorna a altura do no ou -1 se este for nulo.

- func short maior(int a, int b): Retorna o maior valor entre a e b.

- func nodo *retorna_raiz(arvore *avl): Retorna o nodo raiz.

- func void salva_raiz(arvore *avl, nodo *raiz): Funcao de encapsulamento, feita 
para garantir a estrutura do codigo e nao violar o TAD. Atribui o valor do nodo *raiz
para avl->raiz.

- func void destruir_arvore(nodo *no): Varre primeiro o lado esquerdo da arvore
e verifica se o nodo existe. Se existe, verifica se tem filhos. Se nao tiver, da 
free nesse nodo e segue para o lado direito. 
