#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE_ANAGRAMA   1000


int main(void)
{
    // armazenar as strings recebidas separadas
    // pelo char '1'
    char strs_db[SIZE_ANAGRAMA] = { '\0' };
    int strs_db_i = 0;

    // posicao inicial de cada string de `strs_db`
    int strs_db_pos[SIZE_ANAGRAMA] = { 0 };
    int strs_db_pos_i = 0;
    int strs_db_pos_size = 0;

    // adicionar palavra, seguido de '1'
    char palavra_tmp[SIZE_ANAGRAMA] = { '\0' };
    while( scanf("%s", palavra_tmp) != EOF )
    {
        if (strs_db_i > 0)
        {
            strs_db_i++;
        }

        strs_db_pos[strs_db_pos_i] = strs_db_i;
        strs_db_pos_i++;
        strs_db_pos_size++;
        // printf("#%d\n", strs_db_i);

        strcat(strs_db, palavra_tmp);

        int palavra_size = strlen(palavra_tmp);

        strs_db_i += palavra_size;
        strs_db[strs_db_i] = '1';
    }


    char pares_str[SIZE_ANAGRAMA] = { '\0' };
    int pares_str_i = 0;
    int num_pares = 0;
    
    // criando frequencias para o par
    // de palavras (i,j)
    for (int i = 0; i < strs_db_pos_size - 1; ++i)
    {
        for (int j = i + 1; j < strs_db_pos_size; ++j)
        {
            char word_1[SIZE_ANAGRAMA] = { '\0' };
            int word_1_i = 0;

            char word_2[SIZE_ANAGRAMA] = { '\0' };
            int word_2_i = 0;

            int freq_word_1[26] = { 0 };
            int freq_word_2[26] = { 0 };

            // extrair palavra 1
            int percorrer_palavra_i = strs_db_pos[i];
            while( strs_db[percorrer_palavra_i] != '1' )
            {
                char letra_atual = strs_db[percorrer_palavra_i];
                word_1[word_1_i] = letra_atual;

                percorrer_palavra_i++;
                word_1_i++;
            }

            // registrar frequencia de i
            percorrer_palavra_i = strs_db_pos[i];
            while( strs_db[percorrer_palavra_i] != '1' )
            {
                char letra_atual = strs_db[percorrer_palavra_i] - 97;
                int pos_letra_alfabeto = letra_atual;

                freq_word_1[pos_letra_alfabeto] += 1;
                ++percorrer_palavra_i;
            }

            // extrair palavra 2
            int percorrer_palavra_j = strs_db_pos[j];
            while( strs_db[percorrer_palavra_j] != '1' )
            {
                char letra_atual = strs_db[percorrer_palavra_j];
                word_2[word_2_i] = letra_atual;

                percorrer_palavra_j++;
                word_2_i++;
            }

            // registrar frequencia de j
            percorrer_palavra_j = strs_db_pos[j];
            while( strs_db[percorrer_palavra_j] != '1' )
            {
                int pos_letra_alfabeto = strs_db[percorrer_palavra_j] - 97;
                freq_word_2[pos_letra_alfabeto] += 1;
                ++percorrer_palavra_j;
            }

            // checar se o par eh anagrama
            int par_igual = 1;

            for (int i = 0; i < 26; ++i)
            {
                if ( freq_word_1[i] != freq_word_2[i] )
                    par_igual = 0;
            }

            // registrar par
            if (par_igual == 1)
            {
                num_pares++;

                if (pares_str_i > 0)
                    pares_str_i++;

                pares_str_i += strlen(word_1);
                strcat(pares_str, word_1);
                pares_str[pares_str_i] = '1';

                pares_str_i += strlen(word_2);
                strcat(pares_str, word_2);

                pares_str_i++;
                pares_str[pares_str_i] = '2';

                // printf("%s %d\n", pares_str, pares_str_i);
            }
        }
    }

    // printf("%s\n", pares_str);

    if (num_pares > 0)
    {
        printf("Pares de anagramas encontrados:\n");

        // printar os pares
        for (int i = 0; i <= pares_str_i; ++i)
        {
            int achou_1 = 0;
            int achou_2 = 0;

            if (pares_str[i] == '1')
            {
                achou_1 = 1;
                printf(" e ");
            } else if (pares_str[i] == '2')
            {
                achou_2 = 1;
                printf("\n");
            } else
            {
                printf("%c", pares_str[i]);
            }
        }

        printf("\nTotal de pares: %d\n", num_pares);
    } else
    {
        printf("Nao existem anagramas na frase.\n");
    }


    return EXIT_SUCCESS;
}