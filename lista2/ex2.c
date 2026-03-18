#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int numero_site = 0;
    int quant_canais = 0;

    scanf("%d %d", &numero_site, &quant_canais);


    int melhor_distancia = 0;
    int melhor_canal = 0;
    int melhor_minuto = 0;
    int is_vip = 0;

    for (int i = 0; i < quant_canais; i++)
    {
        // sempre resetar vip
        is_vip = 0;


        int termo_inicial_1 = 0;
        int termo_inicial_2 = 0;

        scanf("%d %d", &termo_inicial_1, &termo_inicial_2);


        int menor_distancia_i1 = abs(numero_site - termo_inicial_1);
        int menor_distancia_i2 = abs(numero_site - termo_inicial_2);
        int menor_distancia = 0;

        // calculando menor distancia
        // nos termos iniciais
        if (menor_distancia_i1 < menor_distancia_i2)
        {
            melhor_distancia = menor_distancia_i1;
        } else if (menor_distancia_i1 >= menor_distancia_i2)
        {
            melhor_distancia = menor_distancia_i2;
        }
        menor_distancia = melhor_distancia;


        int continuar_busca = 1;

        int ultimo_termo = termo_inicial_2;
        int penultimo_termo = termo_inicial_1;
        int termo_atual = 0;

        int minuto_atual = 3;

        // achar o termo da sequencia que mais
        // se aproxima do numero recebido
        while (continuar_busca == 1)
        {
            termo_atual = ultimo_termo + penultimo_termo;
            penultimo_termo = ultimo_termo;
            ultimo_termo = termo_atual;

            int dist_atual = abs(termo_atual - numero_site);

            if (dist_atual < menor_distancia)
            {
                menor_distancia = dist_atual;
            }

            // se eh verdadeiro, nao eh possivel
            // haver distancia menor
            if (termo_atual >= numero_site)
            {
                continuar_busca = 0;
            } else
            {
                minuto_atual += 1;
            }
        }


        if (menor_distancia <= melhor_distancia)
        {
            melhor_distancia = menor_distancia;
            melhor_canal = i + 1;
            melhor_minuto = minuto_atual;

            // testar se pode vip
            int num_decompor = termo_atual;
            int soma_digitos = 0;

            while (num_decompor != 0)
            {
                soma_digitos += num_decompor % 10;
                num_decompor /= 10;
            }

            if (soma_digitos > 10)
            {
                is_vip = 1;
            }
        }
    }

    if (is_vip == 1)
    {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d e com o VIP garantido!!!",
            melhor_canal, melhor_minuto);
    } else
    {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d, mas o ingresso VIP não vai rolar :(",
            melhor_canal, melhor_minuto);
    }


    return EXIT_SUCCESS;
}
//sc,it