#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE_LEDS   1000


int main(void)
{
    int num_testes = 0;
    scanf("%d", &num_testes);

    char todos_leds_str[SIZE_LEDS] = { '\0' };
    int todos_leds_str_i = 0;

    for (int i = 0; i < num_testes; ++i)
    {
        // leds
        char leds_str[SIZE_LEDS];
        int leds_str_size = strlen(leds_str);

        int num_clocks = 0;
        scanf("%s %d", leds_str, &num_clocks);

        int leds_size = strlen(leds_str);

        // lista binaria de leds modificados
        int leds_carry[SIZE_LEDS] = { 0 };

        for (int j = 0; j < num_clocks; ++j)
        {

            // flip primeiro led
            if ( leds_str[0] == 'X' )
            {
                leds_str[0] = 'O';
            } else
            {
                leds_str[0] = 'X';
            }

            // sempre carry no primeiro e segundo led
            if (j > 0)
            {
                leds_carry[0] = 1;
                leds_carry[1] = 1;
                
                // checar quais leds flipar
                for (int k = 1; k < leds_str_size - 1; ++k)
                {
                    if (leds_carry[k] == 1)
                    {
                        if (leds_str[k+1] == 'X')
                        {
                            leds_str[k+1] = 'O';
                        } else
                        {
                            leds_str[k+1] = 'X';
                        }
                        leds_carry[k] = 0;
                        leds_carry[k+1] = 1;
                    }
                }
            }
        }

        strcat(todos_leds_str, leds_str);
        todos_leds_str_i += leds_size;
        char ultimo_char = leds_str[leds_size - 1];

        // adicionar enfeites
        int paridade = (todos_leds_str_i % 2 == 0);
        int igualdade_pontas = (todos_leds_str[0] == 0); // falta

        // nao adicionar no final
        if (i != num_testes - 1)
        {
            if (paridade && igualdade_pontas)
            {
                todos_leds_str[todos_leds_str_i] = '@';
            } else if (!paridade && igualdade_pontas)
            {
                todos_leds_str[todos_leds_str_i] = '#';
            } else if (paridade && !igualdade_pontas)
            {
                todos_leds_str[todos_leds_str_i] = '$';
            } else if (!paridade && !igualdade_pontas)
            {
                todos_leds_str[todos_leds_str_i] = '%';
            }
            todos_leds_str_i++;
        }
        printf("%s\n", leds_str);
    }
    printf("%s\n", todos_leds_str);


    return EXIT_SUCCESS;
}