#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#include "trie_t.h"
void tratar_erro(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}



/*Retorna 0 se existe pelo menos um acento, 1 caso contrario*/
int word_acento(char *str)
{
    char *com_acentos = "ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÝàáâãäåçèéêëìíîïðòóôõöùúûüýÿ";

    for (int i = 0; str[i] != '\0'; ++i)
        for (int j = 0; com_acentos[j] != '\0'; j++)
            if (str[i] == com_acentos[j])
                return 0;
    return 1;
}

void word_pontua(char *str)
{
    int len = strlen(str);
    int j = 0;
    for (int i = 0; i < len; i++)
    {
        if (!ispunct(str[i]))
        {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

void word_sem_minusc(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (isupper(str[i]))
        {
            str[i] = tolower(str[i]); // converte para minuscula
        }
    }
}

