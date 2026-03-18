#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void)
{
    long N = 0;
    long K = 0;
    long P = 0;

    scanf("%ld %ld %ld", &N, &K, &P);


    long primeiro_procurado = 0;
    long Q = 0;


    // buscar divisores primos
    // ate o numero atual
    for (long i = N; i < K; i++)
    {
        long salvar_fatores = 1;
        long num_fatores = 0;

        
        long is_fator_repetido = 0;

        for (long j = 3; j <= i; j += 2) // nao contar pares
        {
            // verificar se o fator nao eh repetido
            long fator_repetido = salvar_fatores % j;


            if (fator_repetido == 0)
            {
                is_fator_repetido = 1;
                break;
            }


            // verificar se a divisao eh numero inteiro
            long is_div_int = i % j;

            if (is_div_int == 0)
            {
                salvar_fatores *= j;
                num_fatores += 1;
            }
        }

        if (is_fator_repetido) continue;


        // se o numero tem a quantidade
        // de fatores desejada
        if (num_fatores == P)
        {
            if (primeiro_procurado == 0)
            {
                primeiro_procurado = salvar_fatores;
            }
            
            Q += 1;
        }
    }


    if (Q != 0)
    {
        printf("%ld %ld", primeiro_procurado, Q);
    } else
    {
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.");
    }


    return EXIT_SUCCESS;
}