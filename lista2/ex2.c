#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int numero_site = 0;
    int N = 0;

    scanf("%d %d", &numero_site, &N);


    int canal_mais_chance = 0;
    int minuto_mais_proximo = 0;
    int pode_vip = 0;

    for (int i = 0; i < N; i++)
    {
        int termo1 = 0;
        int termo2 = 0;

        scanf("%d %d", &termo1, &termo2);


        int distancia_atual = abs(numero_site - termo1);

        // calculando as distancias iniciais do termo recebido
        if ( abs(numero_site - termo2) < distancia_atual)
        {
            distancia_atual = abs(numero_site - termo2);
        }


        // calcular qual o minuto mais proximo do numero recebido
        while (1)
        {
            int minuto_atual = termo1 + termo2;
            int distancia_temp = abs(distancia_atual - minuto_atual);

            if (distancia_temp < distancia_atual)
            {
                termo1 = termo2;
                termo2 = minuto_atual;
            } else if (distancia_temp > distancia_atual)
            {
                if (distancia_temp < minuto_mais_proximo)
                {
                    minuto_mais_proximo = distancia_temp;
                    canal_mais_chance = i;

                    // decompor e somar os algarismos
                    int soma_algarismos = 0;
                    int chance_temp = minuto_mais_proximo;
                    int quant_algarismos_chance = floor(log10(minuto_mais_proximo));

                    for (int i = 0; i < quant_algarismos_chance; i++)
                    {
                        soma_algarismos += chance_temp % 10; // somar ultimo algarismo
                        chance_temp /= 10; // retirar um digito
                    }

                    if (soma_algarismos > 10)
                    {
                        pode_vip = 1;
                    } else if (soma_algarismos <= 10)
                    {
                        pode_vip = 0;
                    }
                }

                break;
            } else if (distancia_atual == distancia_temp)
            {

            }
        }
    }


    return EXIT_SUCCESS;
}