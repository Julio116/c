#include <stdio.h>
#include <stdlib.h>


typedef enum { EXPLOSAO_ARCANA, NUVEM_VENENOSA } TipoAtaque;
typedef enum { CAMADA_1, CAMADA_2 } TipoCamada;


typedef struct  {
    int size_x;
    int size_y;

    int **mapa;
} Mapa;


typedef struct {
    int x;
    int y;
} Posicao;


typedef struct {
    Posicao pos_central;
    int **area;
} Ataque;


typedef struct {
    int n_x;
    int *elems_x;

    int n_y;
    int *elems_y;
} Camada;


int aloc_linhas_mapa(Mapa* mapa) {
    size_t s_mapa = sizeof(int*) * (mapa->size_x);

    mapa->mapa = (int**) malloc(s_mapa);

    if ( mapa->mapa == NULL ) return 0;

    return 1;
}


int aloc_cols_mapa(Mapa* mapa) {
    for (size_t i = 0; i < (mapa->size_x); i++)
    {
        size_t s_cols = sizeof(int) * (mapa->size_y);

        mapa->mapa[i] = (int*) malloc(s_cols);

        // desalocar as colunas ja alocadas
        if (mapa == NULL) {
            for (size_t j = i - 1; j >= 0; j--) {
                free(mapa->mapa[i]);
            }
            return 0;
        }
    }
    return 1;
}


void dealoc_cols_mapa(Mapa* mapa) {
    for (size_t i = 0; i < (mapa->size_x); i++)
    {
        free( mapa->mapa[i] );
    }
}


// alocacao de um mapa completo na memoria
Mapa* aloc_mapa(int num_linhas, int num_cols) {
    Mapa *mapa = (Mapa*) malloc( sizeof(Mapa) );

    if (mapa == NULL) return NULL;

    mapa->size_x = num_linhas;
    mapa->size_y = num_cols;


    int status_linhas = aloc_linhas_mapa(mapa);

    if (!status_linhas) {
        free(mapa);
        return NULL;
    }


    int status_cols = aloc_cols_mapa(mapa);

    if (!status_cols) {
        free(mapa);
        return NULL;
    }

    return mapa;
}


// receber entradas do teclado
void receber_mapa(Mapa *mapa) {
    for (size_t i = 0; i < (mapa->size_x); i++)
    {
        for (size_t j = 0; j < (mapa->size_y); j++) {
            int n_tmp = 0;

            scanf("%d", &n_tmp);

            mapa->mapa[i][j] = n_tmp;
        }
    }
}


void print_mapa(Mapa *mapa) {
    for (size_t i = 0; i < (mapa->size_x); i++)
    {
        for (size_t j = 0; j < (mapa->size_y); j++) {
            printf("%d ", mapa->mapa[i][j] );
        }
        printf("\n");
    }
}


// receber entrada do teclado
Posicao receber_pos() {
    int x = 0;
    int y = 0;

    scanf("%d", &x);
    scanf("%d", &y);

    Posicao pos = { x, y };

    return pos;
}


Camada* get_camada_1_dir(Posicao pos, int direcao, Mapa *mapa, Camada *camada1) {
    int pos_atual = 0;
    int lim = 0;

    if (direcao == 0) {
        pos_atual = pos.x;
        lim = mapa->size_x;
    } else {
        pos_atual = pos.y;
        lim = mapa->size_y;
    }

    // adicionar mais um elemento à camada
    for (size_t i = -1; i < 2; i++) {
        if ((pos_atual + i >= 0) && (pos_atual + i < lim)) {
            size_t s_camada1 = 0;

            if (direcao == 0) {
                (camada1->n_x)++;
                s_camada1 = sizeof(int*) * (camada1->n_x);
            } else {
                (camada1->n_y)++;
                s_camada1 = sizeof(int*) * (camada1->n_y);
            }

            Camada* tmp = (Camada*) realloc(camada1, s_camada1);

            if (tmp == NULL) {
                free(camada1);
                return NULL;
            }

            camada1 = tmp;


            if (direcao == 0) {
                int elem_atual = mapa->mapa[pos.x][pos_atual];

                camada1->elems_x[ (camada1->n_x) - 1 ] = elem_atual;
            } else {
                int elem_atual = mapa->mapa[pos_atual][pos.y];

                camada1->elems_y[ (camada1->n_y) - 1 ] = elem_atual;
            }
        }
    }
    return camada1;
}


Camada* get_camada_1(Posicao pos, Mapa *mapa) {
    Camada *camada1 = { 0, NULL };

    camada1 = get_camada_1_dir(pos, 0, mapa, camada1);
    camada1 = get_camada_1_dir(pos, 1, mapa, camada1);

    return camada1;
}


// checar se a posicao esta dentro do mapa
int is_pos_valida(Posicao pos, Mapa *mapa) {
    int x = pos.x;
    int y = pos.y;

    int is_valido = 1;

    if ( !((x >= 0) && (x < mapa->size_x)) ) is_valido = 0;
    if ( !((y >= 0) && (y < mapa->size_y)) ) is_valido = 0;

    return is_valido;
}


// abstrair qual posicao, de x ou y, sera adicionada
Camada* add_pos_camada_2(int *n_cmd2, int *elems_cmd2, Camada* cmd2) {
    (*n_cmd2)++;

    size_t s_elems = sizeof(int) * (*n_cmd2);
    int *tmp = (int*) realloc(elems_cmd2, s_elems);

    if (tmp == NULL) {
        free(cmd2);
        return NULL;
    };

    tmp = camada2;

    if (dir == 0) {
        camada2->elems[ (camada2->n) - 1 ] = mapa->mapa[x][pos_atual];
    } else {
        camada2->elems[ (camada2->n) - 1 ] = mapa->mapa[pos_atual][y];
    }
}


// `dir`: 0 horizontal, vertical
Camada* get_camada_2_dir(Posicao pos, int dir, Camada *camada2, Mapa *mapa) {
    int x = pos.x;
    int y = pos.y;

    for (size_t i = -1; i < 2; i++)
    {
        int pos_atual = 0;

        if (dir == 0) {
            pos_atual = y + i;
        } else {
            pos_atual = x + i;
        }

        int is_valida = is_pos_valida(pos, mapa);

        // adicionar posicao na camada
        if (is_valida) {
            if (dir == 0) camada2 = add_pos_camada_2();
            else camada2 = add_pos_camada_2();
        }
    }
    return camada2;
}


Camada* get_camada_2(Posicao pos, Mapa *mapa) {
    size_t s_camada2 = sizeof(Camada);
    Camada* camada2 = malloc(s_camada2);

    if (camada2 == NULL) return NULL;

    camada2->n = 0;
    camada2->elems = NULL;

    int x = pos.x;
    int lim_x = mapa->size_x;

    int y = pos.y;
    int lim_y = mapa->size_y;

    // percorrer acima, posicao (x - 1)
    if ((x - 1 >= 0) && (x - 1 < lim_x)) {
        Posicao pos_acima = { pos.x - 1, pos.y };
        camada2 = get_camada_2_dir(pos_acima, 0, camada2, mapa);

        if (camada2 == NULL) return NULL;
    }
    
    // percorrer abaixo, posicao (x + 1)
    if ((x + 1 >= 0) && (x + 1 < lim_x)) {
        Posicao pos_abaixo = { pos.x + 1, pos.y };
        camada2 = get_camada_2_dir(pos_abaixo, 0, camada2, mapa);

        if (camada2 == NULL) return NULL;
    }

    // percorrer lados, posicao (y -+ 1)
    int ha_coluna_atras = (y + 1 >= 0) && (y + 1 < (mapa->size_x));
    int ha_coluna_frente = (y - 1 >= 0) && (y - 1 < (mapa->size_x));
    
    if (ha_coluna_atras && ha_coluna_frente) {
        Posicao pos_acima = { pos.x + 1, pos.y };
        camada2 = get_camada_2_dir(pos, 0, camada2, mapa);

        if (camada2 == NULL) return NULL;
    }

    return camada2;
}


int atq_explosao_arcana(Posicao pos, Mapa *mapa, TipoCamada tipo_cmd) {
    int x = pos.x;
    int y = pos.y;

    int val = 0;

    switch (tipo_cmd) {
        case CAMADA_1:
            val = mapa->mapa[x][y] - 50;
            break;
        case CAMADA_2:
            val = mapa->mapa[x][y] - 25;
            break;
    }

    return val;
}


int atq_nuvem_veneno(Posicao pos, Mapa *mapa, TipoCamada tipo_cmd) {

}


int (*ataques[2])(Posicao, Mapa*, TipoCamada) = {
    atq_explosao_arcana,
    atq_nuvem_veneno
};


Ataque* criar_ataque(Mapa *mapa, TipoAtaque tipo_atq, Posicao pos) {
    Ataque atq = { pos, NULL };

    Camada* camada1 = get_camada_1(pos, mapa);

    for (size_t i = 0; i < (camada1->n); i++)
    {
        switch (tipo_atq) {
            case EXPLOSAO_ARCANA:
                int val = (ataques)[0](pos, mapa, tipo_atq);

                mapa->mapa
                break;
            case NUVEM_VENENOSA:
                (ataques)[1](pos, mapa, tipo_atq);
                break;
        }
    }
    
    return &atq;
}


int main(void) {
    int num_linhas = 0;
    int num_cols = 0;

    scanf("%d", &num_linhas);
    scanf("%d", &num_cols);


    Mapa *mapa = aloc_mapa(num_linhas, num_cols);

    receber_mapa(mapa);
    print_mapa(mapa);


    Posicao pos = receber_pos();

    TipoAtaque t_atq = 0;

    scanf("%d", &t_atq);


    dealoc_cols_mapa(mapa);
    free(mapa);

    return EXIT_SUCCESS;
}