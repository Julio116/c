#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    char c = 0;

    scanf("%c", &c);


    int pos_no_alfabeto = c - 'A';
    int quant_letras_final = (pos_no_alfabeto + 1) * 2 - 1;

    int quant_pontos_print = quant_letras_final - 1;

    for (int i = 0; i <= pos_no_alfabeto; i++)
    {
        if (i != 0)
        {
            quant_pontos_print -= 2;
        }

        // pontos do lado esquerdo
        for (int j = 0; j < (quant_pontos_print / 2); j++)
        {
            printf(".");
        }

        // lado esquerdo das letras
        for (int j = 0; j <= i; j++)
        {
            printf("%c", 'A' + j);
        }

        // lado direito das letras
        for (int j = i - 1; j + 'A' >= 'A'; j--)
        {
            printf("%c", 'A' + j);
        }

        // pontos do lado direito
        for (int j = 0; j < (quant_pontos_print / 2); j++)
        {
            printf(".");
        }
        
        printf("\n");
    }


    return EXIT_SUCCESS;
}