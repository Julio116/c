#include <stdio.h>
#include <stdlib.h>


enum pkm_t { fogo, agua, eletricidade, planta };


typedef struct {
    int id;
    int val_ataque;
    int xp;

    enum pkm_t tipo;

    char cpf_treinador[4];
    char nome[100];
} Pokemon;


typedef struct {
    char cpf[12];

    int idade;
    int nivel;

    char nome[100];

    int num_pkmns;
    Pokemon *pokemons;
} Treinador;


Treinador* cadastrar_treinador() {
    size_t s_treinador = sizeof(Treinador);
    Treinador *treinador = (Treinador*) malloc(s_treinador);

    if (treinador == NULL) return NULL;


    scanf("%s", treinador->nome );
    scanf("%s", treinador->cpf );
    scanf("%d", treinador->idade );

    treinador->nivel = 0;
    treinador->pokemons = NULL;
    treinador->num_pkmns = 0;

    return treinador;
}


// adicionar pokemon na lista do treinador
int add_pokemon_treinador(Treinador *treinador, Pokemon *pkmn) {
    (treinador->num_pkmns)++;

    size_t s_pkmns = sizeof(Pokemon) * (treinador->num_pkmns);

    Pokemon *tmp = (Pokemon*) realloc( treinador->pokemons, s_pkmns );
    if (tmp == NULL) return 0;

    treinador->pokemons = tmp;

    return 1;
}


void cadastrar_pokemon(Treinador *treinadores) {
    size_t s_pkmn = sizeof(Pokemon);
    Pokemon *pkmn = (Pokemon*) malloc(s_pkmn);

    if (pkmn == NULL) return NULL;


    scanf("%s", pkmn->cpf_treinador);
    scanf("%d", pkmn->id);
    scanf("%s", pkmn->nome);
    scanf("%d", pkmn->xp);
    scanf("%d", pkmn->val_ataque);
    scanf("%d", pkmn->tipo);

    add_pokemon_treinador(trein)
}


int main(void) {
    while (1) {
        

        break;
    }
    return EXIT_SUCCESS;
}