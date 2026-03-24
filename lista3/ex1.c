#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_SIZE_ARRAY 100


int main(void)
{
    int num_casos = 0;
    scanf("%d", &num_casos);

    // receber vetores
    for (int i = 0; i < num_casos; ++i)
    {
        int n = 0;
        scanf("%d", &n);

        int vetor_base[MAX_SIZE_ARRAY] = {0};
        int size_vetor_base = 0;

        // receber o vetor base,
        // para pesquisar as sequencias decrescentes
        for (int j = 0; j < n; ++j)
        {
            int num_entrada = 0;
            scanf("%d", &num_entrada);

            vetor_base[j] = num_entrada;
            size_vetor_base += 1;
        }


        // guarda a maior sequencia decrescente achada
        int maior_vetor[MAX_SIZE_ARRAY] = {0};
        int size_maior_vetor = 0;
        int i_maior_vetor = 0;

        
        // começando do lado esquerdo da lista,
        // procurar a lista decrescente
        for (int j = 0; j < size_vetor_base - 1; ++j)
        {
            // testar se a sequencia eh repetida
            int igual_prox_elem = 1;

            for (int k = 0; k < size_vetor_base - 1; ++k)
            {
                if (vetor_base[k] != vetor_base[k+1])
                {
                    igual_prox_elem = 0;
                }
            }

            if (igual_prox_elem == 1)
            {
                continue;
            }


            int inicio_indice = j;
            int final_indice = j;
            int atual_indice = j;

            // aumentar indice ate o fim da corrente decrescente
            while (atual_indice < (size_vetor_base - 1) &&
                vetor_base[atual_indice + 1] < vetor_base[atual_indice])
            {
                atual_indice++;
            }

            final_indice = atual_indice;
            int size_sequencia = (final_indice - inicio_indice) + 1;


            // substituir a maior sequencia decrescente
            if (size_sequencia > size_maior_vetor)
            {
                size_maior_vetor = 0;
                i_maior_vetor = 0;

                for (int k = inicio_indice; k <= final_indice; ++k)
                {
                    maior_vetor[i_maior_vetor] = vetor_base[k];

                    size_maior_vetor++;
                    i_maior_vetor++;
                }
            }
        }


        if (size_maior_vetor == 0)
        {
            printf("0\n");
        } else
        {
            printf("%d\n", size_maior_vetor);

            for (int j = 0; j < size_maior_vetor; j++)
            {
                printf("%d ", maior_vetor[j]);
            }

            printf("\n");
        }
    }


    return EXIT_SUCCESS;
}