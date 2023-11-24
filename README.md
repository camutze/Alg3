# ALGORITMOS 3 CI057 - 2023/2 - SEGUNDO TRABALHO PRATICO

O objetivo pratico deste trabalho e a implementacao de uma base de dados para localizacao de palavras em um conjunto de arquivos.
Para isso, foi utilizado um arquivo tipo .txt para o banco de dados e outro .txt como arquivo no qual sera realizada a busca das palavras. 
A estrutura utilizada para a organizacao desses dados e a arvore Trie, voltada para arrays de caracteres (strings).
A árvore usa um programa 'busca.c' para encontrar palavras fornecidas pelo usuario e um programa 'insere.c' para inserir essas palavras em uma base de dados base.txt.
Observacao: apesar de o enunciado nao exigir a diferenciacao de minusculas e maiusculas, foi feita a conversao por motivos de simplificacao de codigo. 

Os seguintes arquivos estao contidos no trabalho: 

- Cabecalho (header) da biblioteca que implementa a arvore Trie: trie_t.h
- Arquivo .c que implementa as funcoes da biblioteca da arvore Trie: trie_t.c
- Arquivo .txt que armazena as palavras encontradas nas chamadas de insere:
- Arquivo .txt que contem o texto no qual as palavras serao procuradas:
- Arquivo .txt que contem o texto no qual as palavras serao procuradas:
- Arquivo makefile para compilacao do programa: makefile

A seguir, serao explicadas as estruturas utilizadas em cada um deles e os motivos para tal.

# Cabecalho (header) da biblioteca de arvore Trie: trie_t / Arquivo .c (implementacao) da biblioteca de arvore Trie: trie_t.c:

- struct trie_node TrieNode: possui, dentro dela, um outro struct trie_node, nesse caso, um ponteiro de vetor *filhos[], que aponta para os filhos daquele nodo. Possui, ainda, um vetor de caracteres (string), o char origem[TAM_ARQUIVO] e um inteiro eh_final, que e diferente de zero quando a palavra na arvore esta no final e tem valor zero se o final nao foi alcancado ainda.  

- Funcao TrieNode *cria_nodo_trie(): Aloca o espaco para um nodo. Em caso de falha, sai com exit(). Se alocar com sucesso, atribui os valores das variaveis dentro da estrutura *node de modo que a arvore esteja vazia ao inicializar, ou seja, node->filhos[i] serao apontados para NULL para todas as letras do alfabeto. A variavel eh_final sera apontada para zero (nao eh final). Retorna o novo nodo.

- Funcao void inserir_trie(TrieNode *raiz, const char *palavra, const char *origem): Recebe o nodo raiz na variavel TrieNode *percorre, usada para marca o caminho do ponteiro na arvore, uma palavra para ser inserida e um char que denota a origem da palavra. Sera declarado um int index para indice.
Um laco de repeticao ira percorrer cada caractere da palavra ate encontrar a terminacao ('\0'), calculando o indice correspondente ao caractere da palavra, considerando 'a' como indice 0, 'b' como 1 e assim por diante. O calculo e feito pela formula index = *palavra -'a'.
Depois disso, verifica a existencia do nodo correspondente ao caractere atual. Se nao existir, chama cria_nodo_trie() para criar o nodo e o atribui a 'percorre->filhos[index]' (indice correspondente).
Em seguida, copia a origem da palavra para o novo nodo. 'percorre' ira receber percorre->filhos[index] e a 'palavra' sera incrementado para ir para o proximo caractere.
Finalmente, 'percorre->eh_final' tera seu valor mudado para 1, indicando que a palavra chegou ao fim.

- Funcao void print_trie(TrieNode *raiz, char str[], int nivel): Recebe o nodo raiz na variavel TrieNode *raiz, que sera usado para comecar a impressao, recebe um array de caracteres char str[], que armazena as palavras durante a impressao, e recebe tamebem um int nivel, que guarda o nivel atual da trie.
Verifica se o nodo atual marca o final de uma palavra na trie. Se sim, imprime a palavra, seguido de sua origem (arquivo).
O proximo loop percorre os filhos do nodo atual (letras do algabeto), verificando se cada uma delas eh um filho daquele nodo. Se existir, o arry srt recebera
a letra atual (i+ 'a') e a funcao print_trie sera chamada recursivamente para o filho correspondente.

- Funcao void print_prefix(TrieNode *raiz, const char *prefix): Recebe o nodo raiz na variavel TrieNode *raiz, que sera atribuido a *pCrawl para percorrer a arvore e um const char *prefix, com o
prefico que sera usado para buscar as palavras na arvore.
Realiza um loop que varre a arvore buscando o prefixo, caracatere por caractere, enquanto o prefiro nao estiver finalizado (fim da string, '\0'). O indice sera calculado com a formula
index = *prefix - 'a'. Caso nao seja nodo no indice calculado atual, a funcao retorna. Caso exista, o ponteiro 'pCrawl' sera movido para o indice correspondente e o prefixo sera atualizado para o proximo caractere.
Em seguida, sera criada uma string char str [TAM_PALAVRA], que sera usada para armazenar as palavras durante a impressao e a funcao print_trie() sera chamada para imprimir as palavras com o prefixo fornecido a partir do nodo indicado em 'pCrawl'.

- Funcao void destroy((TrieNode *raiz): Recebe um ponteiro TrieNode *raiz, que aponta para a raiz que sera destruida. Eh feito um loop para percorrer cada posicao do vetor de filhos do nodo atual 'raiz'. Para cada posicao, verifica se existem filhos (raiz->filhos[i] != NULL). Se houver, chama recursivamente a funcao 'destroy' para esse filho. Apos liberar a memoria de todos os filhos e subarvores, chama free() para liberar a memoria do nodo atual 'raiz'.

- Funcao int tem_acento(char *str):

- Funcao void retira_pontuacao(char *str):

- Funcao void tudo_minusculo(char *str):
  
- Funcao void export_trie(FILE *base, TrieNode *raiz, char str[], int nivel):

- Funcao int import_trie(FILE *base, TrieNode *raiz):

# Programa / arquivo 'busca.c', feito para buscar em um texto as palavras / prefixos fornecidas pelo usuario:

- 1: São declarados um ponteiro para raiz da arvore Trie (TrieNode *root), um ponteiro para a base de dados (FILE *base), um 
ponteiro para arquivo de texto (FILE *arquivo).
- 2: O programa chama a funcao get_node() e inicializa a arvore Trie, atribuindo a raiz para root.
- 3: O programa verifica se o numero de argumentos (arquivos, com sua quantia representada por argc - argument count, e seus nomes representados no vetor
argv[] - argument vector) passados esta correto (deve ser 3). Se nao estiver, imprime mensagem de erro e retorna 1.
- 4: O programa tenta abrir a base de dados usando a funcao fopen. Caso haja falha, imprime mensagem de erro e retorna 1.
- 5: Havendo sucesso nos passos anteriores, a arvore Trie sera importada com a funcao import_trie(). Se a arvore estiver vazia, sera mostrada
mensagem de erro com essa informacao. Em caso de sucesso na importacao, sera mostrada mensagem informando sucesso na operacao.
- 6: Imprime mensagem informando o inicio da busca.
- 7: Declara uma string str[TAM_PALAVRA] e chama print_prefix() para imprimir as palavras com o prefixo buscado em argv[2].
- 8: Fecha o arquivo 'base' com a funcao fclose() e chama destroy() para destruir a arvore e liberar a memoria utilizada pela Trie. Em seguida, retorna 0.

# Programa / arquivo 'insere.c', feito para inserir palavras buscadas na base de texto:

- 

# Arquivo .txt com texto da Eneida de Virgilio:

- Primeiro arquivo de texto.

# Arquivo .txt com texto bla bla bla:

- Segundo arquivo de texto.

# Arquivo makefile para compilacao do programa:

- CARLOS ME EXPLICA ESSE MAKEFILE PELO AMOR DE DEUS.
 
