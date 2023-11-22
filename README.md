# ALGORITMOS 3 CI057 - 2023/2 - SEGUNDO TRABALHO PRATICO

O objetivo pratico deste trabalho e a implementacao de uma base de dados para localizacao de palavras em um conjunto de arquivos.
Para isso, foi utilizado um arquivo tipo .txt para o banco de dados e outro .txt como arquivo no qual sera realizada a busca das palavras. 
A estrutura utilizada para a organizacao desses dados e a arvore Trie, voltada para arrays de caracteres (strings).
Observacao: apesar de o enunciado nao exigir a diferenciacao de minusculas e maiusculas, foi feita a conversao por motivos de simplificacao de codigo. 

Os seguintes arquivos estao contidos no trabalho: 

- Cabecalho (header) da biblioteca que implementa a arvore Trie: trie_t.h
- Arquivo .c que implementa as funcoes da biblioteca da arvore Trie: trie_t.c
- Arquivo .txt que armazena as palavras encontradas nas chamadas de insere:
- Arquivo .txt que contem o texto no qual as palavras serao procuradas:
- Arquivo .txt que contem o texto no qual as palavras serao procuradas:
- Arquivo makefile para compilacao do programa: makefile

A seguir, sera explicado as estruturas utilizadas em cada um deles e o motivo para tal.

# Cabecalho (header) da biblioteca de arvore Trie: trie_t:

- struct trie_node TrieNode: possui, dentro dela, um outro struct trie_node, nesse caso, um ponteiro de vetor *filhos[], que aponta para os filhos daquele nodo. Possui, ainda, um vetor de caracteres (string), o char origem[TAM_ARQUIVO] e um inteiro eh_final, que e diferente de zero quando a palavra na arvore esta no final e tem valor zero se o final nao foi alcancado ainda.  

- Funcao TrieNode *get_node(): 

- Funcao void insert():

- Funcao void print_trie():

- Funcao void print_prefix():

- Funcao void destroy():

- Funcao int tem_acento():

- Funcao void retira_pontuacao():

- Funcao 

# Arquivo .c (implementacao) da biblioteca de arvore Trie: trie_t.c:

# Arquivo .txt com texto da Eneida de Virgilio:

# Arquivo .txt com texto bla bla bla:

# Arquivo makefile para compilacao do programa:
 
