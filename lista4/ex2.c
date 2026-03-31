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


void salvar_gota_inicial_pos(int parede_horizontal, int parede_vertical,
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

        // flag do while
        int elemento_achado = 0;

        while( elemento_achado == 0 && k < parede_vertical )
        {
          int pos_x = posicoes_gotas[i][k][0];
          int pos_y = posicoes_gotas[i][k][1];

          // salvar em posicao nao ocupada
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

void add_posicao_gota(int x, int y, int limite_y, int posicoes_gotas[][limite_y][2])
{
  // procurar primeira posicao nao ocupada (com -1)
  for (int i = 0; i < limite_y; ++i)
  {
    int pos_x_i = posicoes_gotas[x][i][0];

    // posicao nao ocupada (com -1)
    if ( pos_x_i != -1 )
    {
      posicoes_gotas[x][i][0] = x;
      posicoes_gotas[x][i][1] = y;
    }
  }
}


int correr_gota_esquerda(int gota_x, int gota_y, int limite_x, int limite_y,
  int continuar_percorrendo, char parede[][limite_y])
{
  int is_dentro_limite_x = gota_y >= 0;
  int is_dentro_limite_y = gota_x < limite_x;

  while (is_dentro_limite_y && is_dentro_limite_x)
  {
    // atualizar limites
    is_dentro_limite_x = gota_y >= 0;
    is_dentro_limite_y = gota_x < limite_x;

    // atualizar apenas os que estao dentro dos limites

    char diagonal_chr = '\0';
    char abaixo_chr = '\0';
    char esquerdo_chr = '\0';

    // ha mais uma linha abaixo
    if (gota_x + 1 < limite_x)
    {
      diagonal_chr = parede[gota_x + 1][gota_y - 1];
      abaixo_chr = parede[gota_x + 1][gota_y];
    }

    // ha mais uma coluna ao lado
    if (gota_y - 1 >= 0)
    {
      esquerdo_chr = parede[gota_x][gota_y - 1];
    }

    /* caso ultima linha */
    /* salvar posicoes de gotas */

    // acima de estante, coluna ao lado vazia
    if (diagonal_chr == '#' && esquerdo_chr == '.')
    {
      parede[gota_x][gota_y - 1] = 'o';
      gota_y--;
    } // acima de estante, quina da estante
    else if (abaixo_chr == '#' && diagonal_chr == '.' && esquerdo_chr == '.')
    {
      parede[gota_x][gota_y - 1] = 'o';
      gota_y--;

      is_dentro_limite_x = 0;
      is_dentro_limite_y = 0;
    } // ultima linha
    else if (esquerdo_chr == '.')
    {
      parede[gota_x][gota_y - 1] = 'o';
      gota_y--;
    } // finalizar desenho na parede
    else
    {
      is_dentro_limite_x = 0;
      is_dentro_limite_y = 0;
    }
  }
  
  return gota_y;
}


int correr_gota_direita(int gota_x, int gota_y, int limite_x, int limite_y,
  int continuar_percorrendo, char parede[][limite_y])
{
  int is_dentro_limite_x = gota_y >= 0;
  int is_dentro_limite_y = gota_x < limite_x;

  while (is_dentro_limite_y && is_dentro_limite_x)
  {
    // atualizar limites
    is_dentro_limite_x = gota_y >= 0;
    is_dentro_limite_y = gota_x < limite_x;

    // atualizar apenas os que estao dentro dos limites

    char diagonal_chr = '\0';
    char abaixo_chr = '\0';
    char direita_chr = '\0';

    // ha mais uma linha abaixo
    if (gota_x + 1 < limite_x)
    {
      diagonal_chr = parede[gota_x + 1][gota_y + 1];
      abaixo_chr = parede[gota_x + 1][gota_y];
    }

    // ha mais uma coluna ao lado
    if (gota_y + 1 < limite_y)
    {
      direita_chr = parede[gota_x][gota_y + 1];
    }

    /* caso ultima linha */
    /* salvar posicoes de gotas */

    // acima de estante, coluna ao lado vazia
    if (diagonal_chr == '#' && direita_chr == '.')
    {
      parede[gota_x][gota_y + 1] = 'o';
      gota_y++;
    } // acima de estante, quina da estante
    else if (abaixo_chr == '#' && diagonal_chr == '.' && direita_chr == '.')
    {
      parede[gota_x][gota_y + 1] = 'o';
      gota_y++;

      is_dentro_limite_x = 0;
      is_dentro_limite_y = 0;
    } // ultima linha
    else if (direita_chr == '.')
    {
      parede[gota_x][gota_y + 1] = 'o';
      gota_y++;
    } // finalizar desenho na parede
    else
    {
      is_dentro_limite_x = 0;
      is_dentro_limite_y = 0;
    }
  }
  
  return gota_y;
}


int escorrer_gota_vertical(int gota_x, int gota_y, int limite_x, int limite_y, char parede[][limite_y], int posicoes_gotas[][limite_y][2])
{
  int ha_linha_abaixo = gota_x + 1 < limite_x;
  char abaixo_chr = '\0';

  if (ha_linha_abaixo)
  {
    abaixo_chr = parede[gota_x + 1][gota_y];
  }

  // desenhar gota 'o' ate a proxima estante
  while (abaixo_chr == '.' && ha_linha_abaixo)
  {
    parede[gota_x + 1][gota_y] = 'o';
    gota_x++;

    // atualizar dados
    ha_linha_abaixo = gota_x + 1 < limite_x;

    if (ha_linha_abaixo)
    {
      abaixo_chr = parede[gota_x + 1][gota_y];
    }
  }

  return gota_x;
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

    salvar_gota_inicial_pos(parede_horizontal, parede_vertical,
      parede, posicoes_gotas);

    // processar as gotas restantes,
    // a partir de suas posicoes
    for (int i = 0; i < parede_horizontal; ++i)
    {
      for (int j = 0; j < parede_vertical; ++j)
      {
        int gota_x = posicoes_gotas[i][j][0];
        int gota_y = posicoes_gotas[i][j][1];

        gota_x = escorrer_gota_vertical(gota_x, gota_y, parede_horizontal,
          parede_vertical, parede, posicoes_gotas);


        int gota_pos_esquerda = gota_y;
        int is_limitado_y_esquerda = (gota_pos_esquerda - 1) > 0;

        // desenhar 'o' para a esquerda
        gota_pos_esquerda = correr_gota_esquerda(gota_x, gota_pos_esquerda, parede_horizontal, parede_vertical, is_limitado_y_esquerda, parede);

        // se a gota andou para o lado
        if (gota_pos_esquerda != gota_y)
        {
          add_posicao_gota(gota_x, gota_pos_esquerda, parede_horizontal, posicoes_gotas);
        }


        int gota_pos_direita = gota_y;
        int is_limitado_y_direita = gota_pos_direita + 1 < parede_vertical;

        // desenhar 'o' para a direita
        gota_pos_esquerda = correr_gota_direita(gota_x, gota_pos_direita, parede_horizontal, parede_vertical, is_limitado_y_direita, parede);

        // se a gota andou para o lado
        if (gota_pos_direita != gota_y)
        {
          /* falta remover a gota que deu origem de posicoes gotas */
          add_posicao_gota(gota_x, gota_pos_direita,
            parede_horizontal, posicoes_gotas);
        }
      }
    }

    print_parede(parede_horizontal, parede_vertical, parede);


    return EXIT_SUCCESS;
}