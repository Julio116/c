#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int quant_entradas = 0;

    scanf("%d", &quant_entradas);

    
    int posicao_x = 0;
    int posicao_y = 0;

    for (int i = 0; i < quant_entradas; i++)
    {
        int quant_instrucoes = 0;
        char instrucao = 0;

        scanf("%d %c", &quant_instrucoes, &instrucao);


        // calcular a quantidade de vazios
        int quant_vazios_print = 0;

        if (instrucao == 'D' || instrucao == 'B')
        {
            quant_vazios_print = posicao_x;
        } else if (instrucao == 'E')
        {
            quant_vazios_print = posicao_x - quant_instrucoes;
        }


        // processar instrucoes
        if (instrucao == 'D')
        {
            // print vazios
            for (int j = 0; j < quant_vazios_print; j++)
            {
                printf(" ");
            }

            if (posicao_x > 0)
            {
                printf(".");
            }
            // print pontos
            for (int j = 0; j < quant_instrucoes; j++)
            {
                printf(".");
            }
            posicao_x += quant_instrucoes - 1;

            printf("\n");
        } else if (instrucao == 'B')
        {
            for (int k = 0; k < quant_instrucoes - 1; k++)
            {
                // print vazios
                for (int j = 0; j < quant_vazios_print; j++)
                {
                    printf(" ");
                }

                if (quant_instrucoes == 1)
                {
                    // printf("\n");
                } else
                {
                    printf(".\n");
                }

                posicao_y++;
            }
        } else if (instrucao == 'E')
        {
            // print vazios
            for (int j = 0; j < quant_vazios_print; j++)
            {
                printf(" ");
            }

            // print pontos
            for (int j = 0; j < posicao_x - quant_vazios_print + 1; j++)
            {
                printf(".");
            }

            posicao_x -= quant_instrucoes;
            printf("\n");
        }
    }


    return EXIT_SUCCESS;
}