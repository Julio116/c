#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main(void)
{
    int dinheiro_total = 0;
    double porcent_dinheiro1 = 0;
    double porcent_dinheiro2 = 0;
    double porcent_dinheiro3 = 0;

    scanf(" %d %lf %lf %lf", &dinheiro_total, &porcent_dinheiro1,
        &porcent_dinheiro2, &porcent_dinheiro3);


    double premio1 = dinheiro_total * (porcent_dinheiro1 / 100);
    double premio2 = dinheiro_total * (porcent_dinheiro2 / 100);
    double premio3 = dinheiro_total * (porcent_dinheiro3 / 100);

    
    int dinheiro_rebeca = 3;
    int invest_rebeca = 0;

    int divisao_funcionou = (
            floor(premio1) == premio1 &&
            floor(premio2) == premio2 &&
            floor(premio3) == premio3
        );

    if (divisao_funcionou == 1)
    {
        printf("Cada homem ficou com %.0lf, %.0lf e %.0lf reais, respectivamente\n",
            premio1, premio2, premio3);

        dinheiro_rebeca += dinheiro_total - premio1 - premio2 - premio3;
    } else if (divisao_funcionou == 0)
    {
        dinheiro_rebeca -= 1;
        invest_rebeca += 1;
        dinheiro_total += 1;

        double premio1 = dinheiro_total * (porcent_dinheiro1 / 100);
        double premio2 = dinheiro_total * (porcent_dinheiro2 / 100);
        double premio3 = dinheiro_total * (porcent_dinheiro3 / 100);

        int divisao_funcionou = (
            floor(premio1) == premio1 &&
            floor(premio2) == premio2 &&
            floor(premio3) == premio3
        );
        
        if (divisao_funcionou == 1)
        {
            printf("Cada homem ficou com %.0lf, %.0lf e %.0lf reais, respectivamente\n",
                premio1, premio2, premio3);

            dinheiro_rebeca += dinheiro_total - premio1 - premio2 - premio3;
        } else
        {
            dinheiro_rebeca -= 1;
            invest_rebeca += 1;
            dinheiro_total += 1;


            char letra1 = 0;
            char letra2 = 0;
            char letra3 = 0;

            scanf(" %c %c %c", &letra1, &letra2, &letra3);

            int soma = 0;
            int valor1 = letra1 - 96;
            int valor2 = letra2 - 96;
            int valor3 = letra3 - 96;

            soma = valor1 + valor2 + valor3;

            printf("%d\n", soma);


            double premio1 = dinheiro_total * (porcent_dinheiro1 / 100);
            double premio2 = dinheiro_total * (porcent_dinheiro2 / 100);
            double premio3 = dinheiro_total * (porcent_dinheiro3 / 100);

            int divisao_funcionou = (
                floor(premio1) == premio1 &&
                floor(premio2) == premio2 &&
                floor(premio3) == premio3
            );

            int sobra_int = dinheiro_total
                - premio1 - premio2 - premio3;
            
            if ((divisao_funcionou == 1) && (sobra_int >= invest_rebeca + 1))
            {
                printf("Cada homem ficou com %.0lf, %.0lf e %.0lf reais, respectivamente\n",
                    premio1, premio2, premio3);

                dinheiro_rebeca += sobra_int;
            } else
            {
                dinheiro_rebeca -= 1;
                invest_rebeca += 1;
                dinheiro_total += 1;


                int idade1 = 0;
                int idade2 = 0;
                int idade3 = 0;

                scanf(" %d %d %d", &idade1, &idade2, &idade3);

                int soma_parcelas_3 = 0;

                if (idade1 / 3)
                    soma_parcelas_3 += idade1 / 3;
                if (idade2 / 3)
                    soma_parcelas_3 += idade2 / 3;
                if (idade3 / 3)
                    soma_parcelas_3 += idade3 / 3;

                printf("%d\n", soma_parcelas_3);


                double premio1 = dinheiro_total * (porcent_dinheiro1 / 100);
                double premio2 = dinheiro_total * (porcent_dinheiro2 / 100);
                double premio3 = dinheiro_total * (porcent_dinheiro3 / 100);

                int divisao_funcionou = (
                    floor(premio1) == premio1 &&
                    floor(premio2) == premio2 &&
                    floor(premio3) == premio3
                );

                int sobra_int = dinheiro_total
                    - premio1 - premio2 - premio3;
                
                if ((divisao_funcionou == 1) && (sobra_int >= invest_rebeca + 1))
                {
                    printf("Cada homem ficou com %.0lf, %.0lf e %.0lf reais, respectivamente\n",
                        premio1, premio2, premio3);

                    dinheiro_rebeca += sobra_int;
                } else
                {
                    printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
                }
            }
        }
    }

    if (dinheiro_rebeca >= 7)
    {
        printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
    } else if (dinheiro_rebeca < 7)
    {
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    }


    return EXIT_SUCCESS;
}