#include <stdio.h>
#include <stdlib.h>


// alocar colunas da matriz. 0 erro, 1 sucesso.
int alloc_cols(int n_linhas, int n_cols, int **mtrx) {
    for (int i = 0; i < n_linhas; ++i) {
        mtrx[i] = calloc(n_cols, sizeof(int) * n_cols);

        if (mtrx == NULL) return 0;
    }
    return 1;
}


void receber_mapa(int n_cols, int n_linhas, int **mapa) {
    for (int i = 0; i < n_linhas; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            int hp = 0;
            scanf("%d", &hp);

            mapa[i][j] = hp;
        }
    }
}


void print_mapa(int n_cols, int n_linhas, int **mapa) {
    for (int i = 0; i < n_linhas; ++i) {
        for (int j = 0; j < n_cols; ++j) {
            printf("%d ", mapa[i][j] );
        }
        printf("\n");
    }
}


void dealloc_cols(int n_cols, int n_linhas, int **mtrx) {
    for (int i = 0; i < n_linhas; ++i) {
        free( mtrx[i] );
    }
}


typedef struct {
    int n;
    int n_pos[];
} Camada;


typedef struct {
    int x;
    int y;
} Posicao;


Camada* get_camada_1(int n_cols, int n_linhas, Posicao pos, int **mapa) {
    int x = pos.x;
    int y = pos.y;

    int n = 1;
    Camada *cmd = NULL;

    // percorrer a partir de x, -1, +0, +1
    for (int i = -1; i < 2; ++i) {
        int index = x + i;

        if ((index > 0) && (index < n_linhas)) {
            n++;

            realloc(cmd, sizeof(Camada) + sizeof(int) * n);
            if (cmd == NULL) return NULL;

            cmd->n = n;
            cmd->n_pos[n] = mapa[x][i];
        }
    }

    // percorrer a partir de y, -1, +0, +1
    for (int i = -1; i < 2; ++i) {
        int index = y + i;

        if ((index > 0) && (index < n_linhas)) {
            n++;

            realloc(cmd, sizeof(Camada) + sizeof(int) * n);
            if (cmd == NULL) return NULL;

            cmd->n = n;
            cmd->n_pos[n] = mapa[i][y];
        }
    }
    return cmd;
}


void get_camada_2() {

}


int main(void) {
    int n_linhas = 0;
    int n_cols = 0;

    scanf("%d", &n_linhas);
    scanf("%d", &n_cols);

    int n_elems = n_linhas * n_cols;


    int **mapa = calloc(n_linhas, sizeof(int*) * n_linhas);
    if (mapa == NULL) return EXIT_FAILURE;

    int status_cols = alloc_cols(n_linhas, n_cols, mapa);
    if (status_cols == 0) return EXIT_FAILURE;


    receber_mapa(n_cols, n_linhas, mapa);

    printf("Estado inicial do mapa:\n");
    print_mapa(n_cols, n_linhas, mapa);


    int x_ataque = 0;
    int y_ataque = 0;

    scanf("%d", &x_ataque);
    scanf("%d", &y_ataque);

    Posicao pos = { x_ataque, y_ataque };


    Camada *cmd = get_camada_1(n_cols, n_linhas, pos, mapa);

    for (size_t i = 0; i < (cmd->n); i++)
    {
        printf("%d ", cmd->n_pos[i]);
    }
    printf("\n");
    

    // print_mapa(n_cols, n_linhas, mapa);

    dealloc_cols(n_cols, n_linhas, mapa);
    free(mapa);

    return EXIT_SUCCESS;
}