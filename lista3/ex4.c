#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define SIZE_LEDS     60


int main(void)
{
    int num_testes = 0;
    scanf("%d", &num_testes);

    for (int i = 0; i < num_testes; ++i)
    {
        // leds
        char leds[SIZE_LEDS];
        scanf("%s", leds);
        int size_leds = strlen(leds);


        // lista binaria de leds modificados
        int leds_modificados[SIZE_LEDS] = {0};


        // inverter o primeiro led
        if (leds[0] == 'X')
        {
            leds[0] = 'O';
        } else
        {
            leds[0] = 'X';
        }
        leds_modificados[0] = 1;


        for (int k = 0; k < SIZE_LEDS; ++k)
        {
            
        }
    }


    return EXIT_SUCCESS;
}