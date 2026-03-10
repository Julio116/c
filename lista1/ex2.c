#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int N = 0;
    int A = 0;
    int B = 0;

    scanf("%d", &N);
    scanf("%d %d", &A, &B);


    int soma_N_primeiros_nums = N * (N + 1) / 2;
    
    int limite_multiplos_A = N / A;
    int limite_multiplos_B = N / B;

    int soma_multiplos_A = A * limite_multiplos_A * (limite_multiplos_A + 1) / 2;
    int soma_multiplos_B = B * limite_multiplos_B * (limite_multiplos_B + 1) / 2;

    int resultado_final = soma_N_primeiros_nums
        - soma_multiplos_A - soma_multiplos_B;
    

    if ((resultado_final % 2) == 0)
    {
        printf("%d\n", resultado_final);
        printf("Lá ele!!!");
    } else if ((resultado_final % 2) != 0)
    {
        printf("%d\n", resultado_final);
        printf("Opa xupenio AULAS...");
    }


    return EXIT_SUCCESS;
}