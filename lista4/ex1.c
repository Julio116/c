#include <stdio.h>
#include <stdlib.h>


// receber grade por input
void receber_grade(int n_linhas, int n_cols, char grade[n_linhas][n_cols])
{
    for (int i = 0; i < n_linhas; ++i)
    {
        scanf("%s", grade[i]);
    }
}


void print_grade(int n_linhas, int n_cols, char grade[n_linhas][n_cols])
{
    for (int i = 0; i < n_linhas; ++i)
    {
        for (int j = 0; j < n_cols; ++j)
        {
            printf("%c", grade[i][j]);
        }
        printf("\n");
    }
}


// testar caracteres na diagonal de um 'P' e trocar pelo correto
void teste_char_diagonal(int teste_x, int teste_y, int n_linhas, int n_cols,
    char grade[n_linhas][n_cols])
{
    int is_pos_linha_valido = teste_x < n_linhas && teste_x >= 0;
    int is_col_linha_valido = teste_y < n_cols && teste_y >= 0;

    if ( is_pos_linha_valido && is_col_linha_valido )
    {
        char teste_chr = grade[teste_x][teste_y];

        if ( teste_chr == '-' )
            grade[teste_x][teste_y] = 'x';
    }
}


// testar caracteres nas 4 direcoes de um 'P' e trocar pelo correto
void teste_char_direcoes(int teste_x, int teste_y, int n_linhas, int n_cols,
    char grade[n_linhas][n_cols])
{
    int is_pos_linha_valido = teste_x < n_linhas && teste_x >= 0;
    int is_col_linha_valido = teste_y < n_cols && teste_y >= 0;

    if ( is_pos_linha_valido && is_col_linha_valido )
    {
        char teste_chr = grade[teste_x][teste_y];

        if ( teste_chr == '-' || teste_chr == 'x' )
            grade[teste_x][teste_y] = '+';
    }
}


// adicionando decoracao nas 4 direcoes
void decorar_poste_4_direcoes(int pos_x, int pos_y,
    int n_linhas, int n_cols, char grade[][n_cols])
{
    teste_char_direcoes(pos_x + 1, pos_y, n_linhas, n_cols, grade);
    teste_char_direcoes(pos_x - 1, pos_y, n_linhas, n_cols, grade);
    teste_char_direcoes(pos_x, pos_y - 1, n_linhas, n_cols, grade);
    teste_char_direcoes(pos_x, pos_y + 1, n_linhas, n_cols, grade);

}


// adicionando decoracao nas 4 diagonais
void decorar_poste_4_diagonais(int pos_x, int pos_y,
    int n_linhas, int n_cols, char grade[][n_cols])
{
    // adicionando decoracao nas 4 diagonais
    teste_char_diagonal(pos_x + 1, pos_y + 1, n_linhas, n_cols, grade);
    teste_char_diagonal(pos_x + 1, pos_y - 1, n_linhas, n_cols, grade);
    teste_char_diagonal(pos_x - 1, pos_y - 1, n_linhas, n_cols, grade);
    teste_char_diagonal(pos_x - 1, pos_y + 1, n_linhas, n_cols, grade);
}


// decorar poste nas 4 direcoes e nas 4 diagonais
void decorar_postes(int n_linhas, int n_cols, char grade[n_linhas][n_cols])
{
    for (int i = 0; i < n_linhas; ++i)
    {
        for (int j = 0; j < n_cols; ++j)
        {
            if ( grade[i][j] == 'P' )
            {
                decorar_poste_4_direcoes(i, j, n_linhas, n_cols, grade);
                decorar_poste_4_diagonais(i, j, n_linhas, n_cols, grade);
            }
        }
    }
}


int main(void)
{
    int n_cols = 0;
    int n_linhas = 0;

    scanf("%d %d", &n_cols, &n_linhas);


    char grade[n_linhas][n_cols];

    receber_grade(n_linhas, n_cols, grade);
    decorar_postes(n_linhas, n_cols, grade);

    print_grade(n_linhas, n_cols, grade);

    return EXIT_SUCCESS;
}