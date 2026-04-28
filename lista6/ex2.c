#include <stdio.h>
#include <stdlib.h>


enum pkm_t { fogo, agua, eletricidade, planta };

typedef struct {
    int id;
    int val_ataque;
    int xp;

    enum pkm_t tipo;

    char nome[100];
} Pokemon;


typedef struct {
    char nome[100];
    char cpf[12];

    int idade;
    int nivel;

    Pokemon pokemons[];
} Treinador;


void cadastrar_treinador(Treinador *trn) {
    scanf("%s", trn->nome );
    scanf("%s", trn->cpf );
    scanf("%d", trn->idade );
}


int main(void) {
    while (1) {
        

        break;
    }
    return EXIT_SUCCESS;
}