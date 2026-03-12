#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    long long N = 0;
    long long K = 0;
    long long P = 0;

    scanf("%lld %lld %lld", &N, &K, &P);


    long long num_primo = 0;
    long long quant_multiplos = 0;
    long long achou_primeiro = 0;

    // procurar o primo com divisores nao repetidos
    for (long long i = N; i < P; i++)
    {
        long long quant_multiplos_novos = 0;

        // checar os divisores
        for (long long j = 3; j < i; j++)
        {
            int is_multiplo = 0;
            int is_multiplo_repetido = 0;

            // checar se os divisores se repetem
            for (int k = 1; k <= 2; k++)
            {
                long long div_int = floor( i / (double) pow(j, k) );
                long long div_n_int = i / (double) pow(j, k);

                // checar se divisor aparece uma vez
                if ((k == 1) && (div_int == div_n_int))
                {
                    is_multiplo = 1;
                }

                // checar se divisor se repete
                if (is_multiplo)
                {
                    int teste_repetido = !(
                        (k == 2) &&
                        (is_multiplo == 1) &&
                        (div_int == div_n_int)
                    );

                    if (teste_repetido)
                    {
                        is_multiplo_repetido = 1;
                    } else
                    {
                        quant_multiplos_novos += 1;
                    }
                }
            }

            // guardar o divisor valido
            if (is_multiplo && !is_multiplo_repetido)
            {
                if (achou_primeiro)
                {

                } else
                {
                    num_primo *= j;
                    quant_multiplos += 1;
                    achou_primeiro = 1;
                }
            }
        }
    }


    return EXIT_SUCCESS;
}