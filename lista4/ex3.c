#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
multiplas saidas?
*/


// receber mapa por entrada do teclado
void receber_mapa(int size_x, int size_y, char mapa[][size_y])
{
    for (int i = 0; i < size_x; ++i)
    {
        scanf("%s", mapa[i]);
    }
}


// procurar a posicao inicial no mapa e registrar em `posicao_inicial`
void set_posicao_inicial(int size_x, int size_y,
  int pos_inicial[2], char mapa[size_x][size_y])
{
  for (int i = 0; i < size_x; ++i)
  {
    for (int j = 0; j < size_y; ++j)
    {
      if ( mapa[i][j] == 'o' )
      {
        pos_inicial[0] = i;
        pos_inicial[1] = j;
      }
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
void inicializar_visitados(int size_x, int size_y, int ja_visitados[][size_y])
{
  for (int i = 0; i < size_x; ++i)
  {
    for (int j = 0; j < size_y; ++j)
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


int calc_caminhos_redor(int x, int y, int lim_x, int lim_y,
  int mapa[][lim_y], int ja_visitados[][lim_y])
{
  int is_dentro_limite_x = 0;
  if (x - 1 >= 0
  {

  }
}


int main(void)
{
  int size_x = 0;
  int size_y = 0;

  scanf("%dx%d", &size_x, &size_y);


  char mapa[size_x][size_y];

  receber_mapa(size_x, size_y, mapa);


  // matriz das posicoes ja visitadas no mapa
  int ja_visitados[size_x][size_y];

  inicializar_visitados(size_x, size_y, ja_visitados);


  int num_total_caminhos = size_x * size_y;

  // todos as posicoes a serem percorridas no formato:
  // (x, y, distancia_percorrida)
  int caminhos[num_total_caminhos][3];

  int caminhos_i = 0;

  inicializar_caminhos(num_total_caminhos, caminhos);

  // formato (x, y, distancia_percorrida)
  int pos_inicial[3] = { -1, -1, 0 };

  set_posicao_inicial(size_x, size_y, pos_inicial, mapa);

  // registrando a posicao inicial em `caminhos`
  memcpy(caminhos[0], pos_inicial, sizeof(pos_inicial));

  caminhos_i++;

  // processar os caminhos
  for (int i = 0; i < num_total_caminhos; ++i)
  {
    int pos_x = caminhos[i][0];
    int pos_y = caminhos[i][1];
    int dist_percorrida = caminhos[i][2];

    if ( mapa[pos_x][pos_y] != 'd' )
    {
      caminhos[i][2] += 1;

      int qnt_validos_redor = calc_caminhos_redor();
    } else
    {
      caminhos[i][2] += 1;
    }
  }
  

  /*
  if atual nao 'd'
    checar se ha caminhavel ao redor nao visitado
      checar 4 posicoes ao redor, caminhavel, limite mapa, posicoes ocupadas
      quant posicoes validas

      se 1 caminhavel e nao visitado
        ande +1
      se >1 caminhavel e nao visitado
        para cada um-1
          posicao add no array de caminhos
          somar +1 na distancia de cada caminho desses + distancia atual ja feita
  */
  return EXIT_SUCCESS;
}