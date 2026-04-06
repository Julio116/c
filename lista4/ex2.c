#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// recebe entrada do teclado
void receber_parede(int lim_x, int lim_y, char parede[][lim_y])
{
  for (int i = 0; i < lim_x; i++)
  {
    scanf("%s", parede[i]);
  }
}


void print_parede(int lim_x, int lim_y, char parede[][lim_y])
{
  for (int i = 0; i < lim_x; i++)
  {
    for (int j = 0; j < lim_y; j++)
    {
      printf("%c", parede[i][j]);
    }
    printf("\n");
  }
}


// checar se a posicao horizontal/vertical esta na parede
int is_dentro_mapa(int pos, int lim_pos)
{
  int is_pos_limitada = (pos >= 0) && (pos < lim_pos);

  if (is_pos_limitada)
  {
    return 1;
  } else
  {
    return 0;
  }
}


// retorna -1 caso nao exista estante abaixo da gota,
// retorna o numero da linha caso haja
int ha_estante_vertical(int x, int y, int lim_x, int lim_y, char parede[][lim_y])
{
  int linha_atual = x;
  int dentro_parede = 1;

  while (dentro_parede)
  {
    char chr_atual = parede[linha_atual][y];

    if (chr_atual == '#')
    {
      return linha_atual;
    }

    linha_atual++;
    dentro_parede = linha_atual < lim_x;
  }

  return -1;
}


// -1 se nao houver nada a direita,
// e a posicao do obstaculo, se houver
int get_pos_obstaculo_horiz(int x, int y, int lim_x, int lim_y, int direcao, char parede[][lim_y])
{
  int is_limitado = 1;

  while (is_limitado)
  {
    char chr_atual = parede[x][y];
    int is_obstaculo = chr_atual == '#';

    if (is_obstaculo)
    {
      return y;
    }

    if (direcao == 0) { // esquerda
      is_limitado = is_dentro_mapa(y - 1, lim_y);

      if (is_limitado)
        y--;
    } else { // direita
      is_limitado = is_dentro_mapa(y + 1, lim_y);

      if (is_limitado)
        y++;
    }
  }

  return -1;
}


// printar a gota na parede,
// da posicao atual ate a posicao final especificada
void print_gota_vertical(int x, int y, int final_pos, int lim_y, char parede[][lim_y])
{
  for (int i = x; i < final_pos; ++i)
  {
    parede[i][y] = 'o';
  }
}


// printar a gota na parede,
// da posicao atual ate a posicao final especificada,
// direcao: +1 direita, -1 esquerda
void print_gota_horizontal(int x, int y, int final_pos, int lim_y, int direcao, char parede[][lim_y])
{
  if (direcao == 0) { // esquerda
    // printf("|%d", final_pos);
    for (int j = y; j > final_pos; --j)
    {
      parede[x][j] = 'o';
    }
  } else { // direita
    for (int j = y; j < final_pos; ++j)
    {
      parede[x][j] = 'o';
    }
  }
}


// recebe posicao de gota, desce ate a primeira estante, ou ate o fim da parede
int escorrer_vertical(int x, int y, int lim_x, int lim_y, char parede[][lim_y])
{
  int pos_estante = ha_estante_vertical(x, y, lim_x, lim_y, parede);

  if (pos_estante >= 0) // escorrer ate a proxima estante
  {
    print_gota_vertical(x, y, pos_estante, lim_y, parede);

    return pos_estante - 1;
  } else // escorrer ate o final da parede
  {
    print_gota_vertical(x, y, lim_x, lim_y, parede);

    return lim_x;
  }
}


// escorrer gota 'o' na parede, na horizontal. com direcao: 0 esquerda, 1 direita.
// retorna coluna da gota
int escorrer_horizontal(int x, int y, int lim_x, int lim_y, int direcao, char parede[][lim_y])
{
  int pos_obstaculo = get_pos_obstaculo_horiz(x, y, lim_x, lim_y, direcao, parede);
  int ha_obstaculo = is_dentro_mapa(pos_obstaculo, lim_y);

  
  // se nao houver obstaculos,
  // a posicao sera na borda
  if (pos_obstaculo == -1) {
    if (direcao == 0) { // esquerda
      pos_obstaculo = 0;
    }

    if (direcao == 1) { // direita
      pos_obstaculo = lim_y - 1;
    }
  }
  printf("pos_obstaculo ha_obstaculo %d %d\n", pos_obstaculo, ha_obstaculo);

  if (ha_obstaculo) {
    // se esta na ultima linha nao escorra
    if (x < lim_x - 1) {
      print_gota_horizontal(x, y, pos_obstaculo, lim_y, direcao, parede);
    }
  } else {
    // se esta na ultima linha nao escorra
    if (x < lim_x - 1) {
      if (direcao == 0) { // esquerda
        print_gota_horizontal(x, y, -1, lim_y, direcao, parede);
        pos_obstaculo = 0;
      }

      if (direcao == 1) { // direita
        print_gota_horizontal(x, y, lim_y, lim_y, direcao, parede);
        pos_obstaculo = lim_y - 1;
      }
    }
  }

  return pos_obstaculo;
}


// registrar o primeiro 'o' achado na parede
void achar_gota_inicial(int lim_x, int lim_y, char parede[][lim_y], int pos_gota[])
{
  for (int i = 0; i < lim_x; ++i)
  {
    for (int j = 0; j < lim_y; ++j)
    {
      char atual_chr = parede[i][j];

      if (atual_chr == 'o')
      {
        pos_gota[0] = i;
        pos_gota[1] = j;

        return;
      }
    }
  }
}


// inserir na primeira posicao nao '-1', retorna 1, senao retorna 0
int add_gota(int x, int y, int num_gotas, int gotas_pos[][2]) {
  int inseriu_gota = 0;
  int i = 0;

  while ((inseriu_gota == 0) && (i < num_gotas)) {
    int x_atual = gotas_pos[i][0];
    
    if (x_atual == -1) {
      gotas_pos[i][0] = x;
      gotas_pos[i][1] = y;

      inseriu_gota = 1;
    }

    i++;
  }

  if (inseriu_gota) {
    return 1;
  } else {
    return 0;
  }
}


// remove a primeira ocorrencia da gota dada
int remover_gota(int x, int y, int num_gotas, int gotas_pos[][2]) {
  int removeu_gota = 0;
  int i = 0;

  while ((removeu_gota == 0) && (i < num_gotas)) {
    int x_atual = gotas_pos[i][0];
    int y_atual = gotas_pos[i][1];
    
    if ((x_atual == x) && (y_atual == y)) {
      gotas_pos[i][0] = -1;
      gotas_pos[i][1] = -1;

      removeu_gota = 1;
    }

    i++;
  }

  if (removeu_gota) {
    return 1;
  } else {
    return 0;
  }
}


int get_proxima_gota(int nova_gota[], int num_gotas, int gotas_pos[][2]) {
  int achou_gota = 0;
  int i = 0;

  while ((achou_gota == 0) && (i < num_gotas)) {
    int x_atual = gotas_pos[i][0];
    
    if (x_atual != -1) {
      int x = gotas_pos[i][0];
      int y = gotas_pos[i][1];

      nova_gota[0] = x;
      nova_gota[1] = y;

      achou_gota = 1;
    }

    i++;
  }

  if (achou_gota) {
    return 1;
  } else {
    return 0;
  }
}


int ha_gotas(int num_gotas, int gotas_pos[][2]) {
  int achou_gota = 0;
  int i = 0;

  while ((achou_gota == 0) && (i < num_gotas)) {
    int x_atual = gotas_pos[i][0];
    
    if (x_atual != -1)
      achou_gota = 1;

    i++;
  }

  if (achou_gota) {
    return 1;
  } else {
    return 0;
  }
}


// inicializar gotas com -1
void inicializar_gotas(int num_gotas, int gotas[][2]) {
  for (int i = 0; i < num_gotas; ++i)
  {
    gotas[i][0] = -1;
    gotas[i][1] = -1;
  }
}


void percorrer_gota(int x_inicial, int y_inicial, int lim_x, int lim_y, char parede[][lim_y])
{
  int num_gotas = lim_x * lim_y;

  // gotas a serem processadas
  int gotas_pos[num_gotas][2];

  inicializar_gotas(num_gotas, gotas_pos);

  // adicionar gota inicial
  add_gota(x_inicial, y_inicial, num_gotas, gotas_pos);

  int existem_gotas = ha_gotas(num_gotas, gotas_pos);

  // faz a gota correr na vertical, esquerda e direita,
  // fazer correrem as novas gotas, ate nao ser mais possivel
  // while (existem_gotas) {
  for (int i = 0; i < 3; ++i) {
    int nova_gota[2] = { -1, -1 };

    int achou_gota = get_proxima_gota(nova_gota, num_gotas, gotas_pos);
    printf("antigas_gotas %d %d\n", nova_gota[0], nova_gota[1]);
    
    if (achou_gota) {
      int x_antes = nova_gota[0];
      int y_antes = nova_gota[1];

      int moveu_vertical = 0;
      int moveu_esquerda = 0;
      int moveu_direita = 0;

      // descer na vertical
      int x_depois = escorrer_vertical(x_antes, y_antes, lim_x, lim_y, parede);

      if (x_depois != x_antes) {
        add_gota(x_depois, y_antes, num_gotas, gotas_pos);
        moveu_vertical = 1;
      }

      // mover gota para a esquerda
      int y_esquerda = escorrer_horizontal(x_depois, y_antes, lim_x, lim_y, 0, parede);
      printf("x_depois y_esquerda %d %d\n", x_depois, y_esquerda);
      printf("\n");

      if (y_esquerda != y_antes) { // se moveu
        add_gota(x_depois, y_esquerda, num_gotas, gotas_pos);
        moveu_esquerda = 1;
      }

      // mover gota para a esquerda
      int y_direita = escorrer_horizontal(x_depois, y_antes, lim_x, lim_y, 1, parede);

      if (y_direita != y_antes) { // se moveu
        add_gota(x_depois, y_direita, num_gotas, gotas_pos);
        moveu_direita = 1;
      }


      // remover as gotas ja percorridas
      if (moveu_vertical) {
        remover_gota(x_antes, y_antes, num_gotas, gotas_pos);
      }

      if (moveu_esquerda || moveu_direita) {
        remover_gota(x_depois, y_antes, num_gotas, gotas_pos);
      }

      existem_gotas = ha_gotas(num_gotas, gotas_pos);
    } else {
      existem_gotas = 0;
    }
  }
}


int main(void)
{
  int lim_x = 0;
  int lim_y = 0;

  scanf("%d %d", &lim_x, &lim_y);


  char parede[lim_x][lim_y];

  int k = lim_y;
  receber_parede(lim_x, lim_y, parede);
  lim_y = k;


  int gota_inicial[2] = { -1, -1 };

  achar_gota_inicial(lim_x, lim_y, parede, gota_inicial);


  int x = gota_inicial[0];
  int y = gota_inicial[1];

  percorrer_gota(x, y, lim_x, lim_y, parede);

  print_parede(lim_x, lim_y, parede);

  return EXIT_SUCCESS;
}