#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    long long N = 0;
    long long A = 0;
    long long B = 0;

    scanf("%d", &N);
    scanf("%d %d", &A, &B);


    long long soma_N_primeiros_nums = N * (N + 1) / 2;
    
    long long limite_multiplos_A = N / A;
    long long limite_multiplos_B = N / B;
    long long limite_multiplos_A_B = N / (A * B);

    long long soma_multiplos_A = A * limite_multiplos_A * (limite_multiplos_A + 1) / 2;
    long long soma_multiplos_B = B * limite_multiplos_B * (limite_multiplos_B + 1) / 2;
    long long soma_multiplos_A_B = A * B * limite_multiplos_A_B
        * (limite_multiplos_A_B + 1) / 2;

    long long resultado_final = soma_N_primeiros_nums
        - soma_multiplos_A - soma_multiplos_B + soma_multiplos_A_B;
    

    if ((resultado_final % 2) == 0)
    {
        printf("%lld\n", resultado_final);
        printf("Lá ele!!!");
    } else if ((resultado_final % 2) != 0)
    {
        printf("%lld\n", resultado_final);
        printf("Opa xupenio AULAS...");
    }


    return EXIT_SUCCESS;
}