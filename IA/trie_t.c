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



/*Retorna 1 se existe pelo menos um acento, 0 caso contrario*/
int word_tem_acento(const char *str)
{
    const char *accentedChars = "ÀÁÂÃÄÅÇÈÉÊËÌÍÎÏÒÓÔÕÖÙÚÛÜÝàáâãäåçèéêëìíîïðòóôõöùúûüýÿ�";

    for (size_t i = 0; i < strlen(str); ++i) {
        if (strchr(accentedChars, str[i]) != NULL) {
            return 1;
        }
    }

    return 0;
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

