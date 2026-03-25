#include <stdio.h>
#include <stdlib.h>

#define N 10000


int main(void)
{
    int clientes_atendidos = 0;
    int clientes_1_lata = 0;
    int clientes_mais_1_lata = 0;

    int horas_compra[N] = { 0 };
    int minutos_compra[N] = { 0 };
    int num_latas[N] = { 0 };

    scanf("%d", &clientes_atendidos);
    scanf("%d", &clientes_1_lata);
    scanf("%d", &clientes_mais_1_lata);

    // receber dados de compra de mais de 1 lata
    for (int i = 0; i < clientes_mais_1_lata; ++i)
    {
        int hora_compra = 0;
        int minuto_compra = 0;
        int quant_latas = 0;

        scanf("%d:%d %d", &hora_compra,
            &minuto_compra, &quant_latas);
        
        horas_compra[i] = hora_compra;
        minutos_compra[i] = minuto_compra;
        num_latas[i] = quant_latas;
    }

    // numero ordinal do cliente
    int ord_cliente = 0;

    int hora_atual = 7;
    int minuto_atual = 0;

    int menor_hora = N;
    int menor_minuto = N;

    while ( hora_atual > 0 )
    {
        // procurar proxima hora
        for (int i = 0; i < N; ++i)
        {
            if ( horas_compra[i] < N)
            {
                menor_hora = horas_compra[i];
                
            }

            for (int j = 0; j < N; ++j)
            {
                if ( horas_compra[j] < N)
                {
                    menor_minuto = minutos_compra[j];
                }
            }
        }

        // hora valida
        if (menor_hora > 0)
        {
            // 1 lata comprada por cliente a cada 3 minutos
            int quant_latas_1 = menor_minuto / 3;

            for (int i = 0; i < quant_latas_1; ++i)
            {
                clientes_1_lata -= 1;
                ord_cliente += 1;

                // atualizar horario e latas por minuto
                if (minuto_atual <= 57)
                {
                    minuto_atual += 3;
                } else
                {
                    int resto_minutos = 60 - minuto_atual;

                    hora_atual++;
                    minuto_atual = resto_minutos;
                }

                if (ord_cliente == 50)
                {
                    printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %d:%d. Que comprou 3 latas.", ord_cliente, hora_atual, minuto_atual);
                }
            }
        }
    }

    minuto_atual = N;

    for (int i = 0; i < N; ++i)
    {
        if (minutos_compra[i] != 0)
        {

        }
    }


    return EXIT_SUCCESS;
}