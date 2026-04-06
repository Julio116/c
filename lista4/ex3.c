#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
multiplas saidas?
*/

// receber mapa por entrada do teclado
void receber_mapa(int limite_x, int limite_y, char mapa[][limite_y])
{
  for (int i = 0; i < limite_x; ++i)
  {
    scanf("%s", mapa[i]);
  }
}

// procurar o primeiro 'o' para posicao inicial
void set_posicao_inicial(int limite_x, int limite_y, int pos_inicial[], char mapa[][limite_y])
{
  int continuar_buscando = 0;

  int i = 0;
  int j = 0;

  while (continuar_buscando)
  {
    // se dentro do mapa
    if ((i < limite_x) && (j < limite_y))
    {
      if ( mapa[i][j] == 'o' )
      {
        pos_inicial[0] = i;
        pos_inicial[1] = j;
      }
    } else // fim de uma linha
    {
      i = 0;
      j++;
    }
  }
}

// inicializar com coordenadas -1, e distancia percorrida 0
void inicializar_caminhos(int num_total, int caminhos[][3])
{
  for (int i = 0; i < num_total; ++i)
  {
    caminhos[i][0] = -1;
    caminhos[i][1] = -1;
    caminhos[i][2] = 0;
  }
}

// inicializar matriz binaria de lugares visitados
void inicializar_visitados(int limite_x, int limite_y, int ja_visitados[][limite_y])
{
  for (int i = 0; i < limite_x; ++i)
  {
    for (int j = 0; j < limite_y; ++j)
    {
      ja_visitados[i][j] = 0;
    }
  }
}

int adicionar_novo_caminho(int pos_x, int pos_y,
  int dist_percorrida, int caminhos[][3], int ja_visitados[][])
{
  // checar se ha caminho acima
  if ( pos_x - 1 >= 0 )
  {
    char novo_char = caminhos[pos_x - 1][pos_y];

    if ( novo_char == 'd' || novo_char == '_' )
    {
      int novo_caminho[3];

      novo_caminho[0] = pos_x - 1;
      novo_caminho[1] = pos_y;
      novo_caminho[2] = dist_percorrida++;

      return 1;
    }
  }
// checar nao visitado

  return 0;
}


// testar se as coordenadas estao dentro do mapa
int calc_limite_valido(int x, int y, int limite_x, int limite_y)
{
  int is_x_valido = (x >= 0) && (x < limite_x);
  int is_y_valido = (y >= 0) && (y < limite_y);

  if (is_x_valido && is_y_valido)
  {
    return 1;
  } else
  {
    return 0;
  }
}


int calc_caminhos_redor(int x, int y, int lim_x, int lim_y,
  int mapa[][lim_y], int ja_visitados[][lim_y])
{
  int is_esquerdo_limite_valido = calc_limite_valido(x - 1, y, lim_x, lim_y);
  int is_direita_limite_valido = calc_limite_valido(x + 1, y, lim_x, lim_y);
  int is_baixo_limite_valido = calc_limite_valido(x, y + 1, lim_x, lim_y);
  int is_cima_limite_valido = calc_limite_valido(x, y - 1, lim_x, lim_y);

  if (is_esquerdo_limite_valido)
  {
    char nova_pos = mapa[x - 1][y];
    int is_visitado = ja_visitados[x - 1][y];

    if (!is_visitado && nova_pos == '_')
    {

    }
  }
}


int main(void)
{
  int limite_x = 0;
  int limite_y = 0;

  scanf("%dx%d", &limite_x, &limite_y);

  int num_total_caminhos = limite_x * limite_y;


  char mapa[limite_x][limite_y];

  receber_mapa(limite_x, limite_y, mapa);


  // todos as posicoes a serem percorridas no formato:
  // (x, y, distancia_percorrida)
  int caminhos[num_total_caminhos][3];

  inicializar_caminhos(num_total_caminhos, caminhos);


  // formato (x, y, distancia_percorrida)
  int pos_inicial[3] = { -1, -1, 0 };

  set_posicao_inicial(limite_x, limite_y, pos_inicial, mapa);


  // registrando a posicao inicial em `caminhos`
  memcpy(caminhos[0], pos_inicial, sizeof(pos_inicial));


  // processar os caminhos
  for (int i = 0; i < num_total_caminhos; ++i)
  {
    int pos_x = caminhos[i][0];
    int pos_y = caminhos[i][1];
    int dist_percorrida = caminhos[i][2];

    char pos_chr = mapa[pos_x][pos_y];

    if ( pos_chr != 'd' )
    {
      caminhos[i][2] += 1;

      int qnt_caminhos_redor = calc_caminhos_redor();
    } else
    {
      caminhos[i][2] += 1;
    }
  }
  
  return EXIT_SUCCESS;
}