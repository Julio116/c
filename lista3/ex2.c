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

    // horas nao ordenadas na entrada


    return EXIT_SUCCESS;
}