// qual o indice add a addposicaogota eh x y da parede
// verificar gota_x e gota_y final apos rodar o programa

#include <stdio.h>
#include <stdlib.h>


// inicializar `posicoes_gotas` apenas com '-1'
void inicializar_posicoes_gotas(int parede_vertical, int parede_horizontal,
  int posicoes_gotas[parede_horizontal][parede_horizontal][2])
{
  for (int i = 0; i < parede_horizontal; ++i)
  {
    for (int j = 0; j < parede_vertical; ++j)
    {
      for (int k = 0; k < 2; ++k)
      {
        posicoes_gotas[i][j][k] = -1;
      }
    }
  }
}


void receber_array_parede(int parede_horizontal, int parede_vertical,
  char parede[][parede_vertical])
{
  // salvar na matriz `parede`
  for (int i = 0; i < parede_horizontal; ++i)
  {
    scanf("%s", parede[i]);
  }
}


void salvar_posicoes_gotas(int parede_horizontal, int parede_vertical,
  char parede[parede_horizontal][parede_vertical],
  int posicoes_gotas[parede_horizontal][parede_vertical][2])
{
  for (int i = 0; i < parede_horizontal; ++i)
  {
    for (int j = 0; j < parede_vertical; ++j)
    {
      if ( parede[i][j] == 'o' )
      {
        // achar posicao valida para inserir gota
        int k = 0;

        int elemento_achado = 0;

        while( elemento_achado == 0 && k < parede_vertical )
        {
          int pos_x = posicoes_gotas[i][k][0];
          int pos_y = posicoes_gotas[i][k][1];

          if ( pos_x == -1 && pos_y == -1 )
          {
            posicoes_gotas[i][k][0] = i;
            posicoes_gotas[i][k][1] = j;
            elemento_achado = 1;
          }

          k++;
        }
      }
    }
  }
}


void print_parede(int size_x, int size_y, char parede[size_x][size_y])
{
  for (int i = 0; i < size_x; ++i)
  {
    for (int j = 0; j < size_y; ++j)
    {
      printf("%c", parede[i][j]);
    }
    printf("\n");
  }
}

void add_posicao_gota(int x, int y, int limite_x, int posicoes_gotas[][limite_x][2])
{
  for (int i = 0; i < limite_x; ++i)
  {
    int pos_x_i = posicoes_gotas[x][i][0];

    if ( pos_x_i != -1 )
    {
      posicoes_gotas[x][i][0] = x;
      posicoes_gotas[x][i][1] = y;
    }
  }
}


int main(void)
{
    int parede_horizontal = 0;
    int parede_vertical = 0;

    scanf("%d %d", &parede_horizontal, &parede_vertical);


    char parede[parede_horizontal][parede_vertical];

    receber_array_parede(parede_horizontal, parede_vertical, parede);


    // o primeiro indice identifica a linha,
    // o segundo indice identifica a gota,
    // a terceira, a coordenada, x ou y.
    // pode haver mais de uma gota por linha
    int posicoes_gotas[parede_horizontal][parede_vertical][2];

    inicializar_posicoes_gotas(parede_vertical, parede_horizontal,
      posicoes_gotas);

    salvar_posicoes_gotas(parede_horizontal, parede_vertical,
      parede, posicoes_gotas);


    // processar as gotas restantes
    for (int i = 0; i < parede_horizontal; ++i)
    {
      for (int j = 0; j < parede_vertical; ++j)
      {
        int gota_x = posicoes_gotas[i][j][0];
        int gota_y = posicoes_gotas[i][j][1];

        if ( (gota_x >= 0) && (gota_y >= 0) )
        {
          int is_limitado_x = gota_x + 1 < parede_horizontal;

          // ha algo na linha abaixo
          if (is_limitado_x)
          {
            char abaixo_chr = parede[gota_x + 1][gota_y];

            // vazio abaixo
            if ( abaixo_chr != '#' )
            {
              // desenhar gota 'o' ate a proxima estante
              while (abaixo_chr != '#' && is_limitado_x)
              {
                parede[gota_x+1][gota_y] = 'o';
                gota_x++;

                // atualizar dados
                is_limitado_x = gota_x + 1 < parede_horizontal;

                if (is_limitado_x)
                {
                  abaixo_chr = parede[gota_x + 1][gota_y];
                }
              }
            }

            int gota_pos_esquerda = gota_y;
            int is_limitado_y_esquerda = gota_pos_esquerda - 1 >= 0;
            char esquerdo_chr = parede[gota_x][gota_pos_esquerda - 1];

            if (is_limitado_y_esquerda)
            {
              esquerdo_chr = parede[gota_x][gota_pos_esquerda - 1];
            }

            // desenhar 'o' para a esquerda
            while ( esquerdo_chr != '#' && is_limitado_y_esquerda )
            {
              parede[gota_x][gota_pos_esquerda - 1] = 'o';

              gota_pos_esquerda--;
              is_limitado_y_esquerda = gota_pos_esquerda - 1 >= 0;
            }

            if (gota_pos_esquerda != gota_y)
              add_posicao_gota(gota_x, gota_pos_esquerda,
                parede_horizontal, posicoes_gotas);


            int gota_pos_direita = gota_y;
            int is_limitado_y_direita = gota_pos_direita + 1 < parede_vertical;
            char direita_chr = parede[gota_x][gota_pos_direita + 1];

            if (is_limitado_y_direita)
            {
              direita_chr = parede[gota_x][gota_pos_direita + 1];
            }

            // desenhar 'o' para a direita
            while ( direita_chr != '#' && is_limitado_y_direita )
            {
              parede[gota_x][gota_pos_direita + 1] = 'o';

              gota_pos_direita++;
              is_limitado_y_direita = gota_pos_direita + 1 < parede_vertical;
              
              if (!is_limitado_y_direita && gota_pos_direita != gota_y)
              {
                gota_pos_direita--;
                add_posicao_gota(gota_x, gota_pos_direita,
                  parede_horizontal, posicoes_gotas);
              }
            }
          }
        }
      }
    }

    print_parede(parede_horizontal, parede_vertical, parede);


    return EXIT_SUCCESS;
}