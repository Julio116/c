#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


// receber notas do teclado. retorna 0 falha, 1 sucesso
void receber_notas(int last_pos, int qtd_alunos, double *notas) {
  for (size_t i = 0; i < qtd_alunos; ++i)
  {
    double nota_tmp = 0;
    
    scanf("%lf", &nota_tmp);

    notas[last_pos + i] = nota_tmp;
  }
}


void print_notas(int qtd_alunos, double *notas) {
  for (size_t i = 0; i < qtd_alunos; ++i)
  {
    printf("%.2lf\n", notas[i]);
  }
}


// soma uma lista de numeros
double calc_soma(int num_elems, double *elems) {
  double soma = 0;

  for (size_t i = 0; i < num_elems; i++)
  {
    soma += elems[i];
  }

  return soma;
}


// calcula a media de um conjunto de numeros
double calc_media(int num_elems, double* elems) {
  double soma = calc_soma(num_elems, elems);
  double media = soma / num_elems;

  return media;
}


// printar o id do aluno com a maior nota, e sua nota
void achar_maior_nota(int qtd_alunos, double *notas) {
  double max = 0;
  int pos_aluno = 0;

  for (size_t i = 0; i < qtd_alunos; i++)
  {
    if (notas[i] > max) {
      max = notas[i];
      pos_aluno = i + 1;
    }
  }
  printf("Maior nota: %.2f (aluno %d)\n", max, pos_aluno);
}


// printar o id do aluno com a menor nota, e sua nota
void achar_menor_nota(int qtd_alunos, double *notas) {
  double min = 10;
  int pos_aluno = 0;

  for (size_t i = 0; i < qtd_alunos; i++)
  {
    if (notas[i] < min) {
      min = notas[i];
      pos_aluno = i + 1;
    }
  }
  printf("Menor nota: %.2f (aluno %d)\n", min, pos_aluno);
}


// calcular a quantidade de elementos acima da media
int calc_acima_media(double media, int num_elems, double *elems) {
  int qtd_acima = 0;

  for (size_t i = 0; i < num_elems; i++)
  {
    if (elems[i] > media) qtd_acima++;
  }

  return qtd_acima;
}


void bubble_sort(int n, double *elems) {
  for (int i = 0; i < n-1; ++i) {
    for (int j = 0; j < n-i-1; ++j) {
      if ( elems[j] > elems[j + 1] ) {
        double tmp = elems[j];
        
        elems[j] = elems[j + 1];
        elems[j + 1] = tmp;
      }
    }
  }
}


double calc_mediana(int num_elems, double *elems) {
  bubble_sort(num_elems, elems);

  double meio_pos = num_elems / (double) 2;

  // teste se faz a media ou nao
  if (meio_pos != ceil(meio_pos)) {
    int pos = ceil(meio_pos) - 1;
    double mediana = elems[pos];

    return mediana;
  }

  int pos_final = ceil(meio_pos) - 1;

  double elem1 = elems[pos_final];
  double elem2 = elems[pos_final + 1];
  double mediana = (elem1 + elem2) / (double) 2;

  return mediana;
}


double achar_max(int num_elems, int *elems) {
  int max = 0;

  for (size_t i = 0; i < num_elems; i++) {
    if (elems[i] > max) {
      max = elems[i];
    }
  }

  return max;
}


// calcula a frequencia de uma lista de numeros
void calc_frequencias(int num_elems, double *elems, int *freqs) {
  for (size_t i = 0; i < num_elems; i++) {
    double elem1 = elems[i];

    for (size_t j = 0; j < num_elems; j++) {
      double elem2 = elems[j];

      if (elem1 == elem2) freqs[i]++;
    }
  }
}


// checa se a moda se repete
int ha_modas_repetidas(double elem_moda, double moda, int num_elems, int *freqs, double *elems) {
  for (size_t i = 0; i < num_elems; i++)
  {
    double elem = elems[i];
    if ( (freqs[i] == moda) && (elem != elem_moda) ) return 1;
  }
  return 0;
}


int lin_search(int value, int num_elems, int *elems) {
  for (size_t i = 0; i < num_elems; ++i) {
    if ( elems[i] == value ) return i;
  }
  return -1;
}


// retorna -1 se houver erro, -2 se a moda nao for unica,
// ou a moda, se houver
double calc_moda(int num_elems, double *elems) {
  int *freqs = NULL;
  freqs = (int*) calloc(num_elems, sizeof(int));

  if (freqs == NULL) return -1;


  calc_frequencias(num_elems, elems, freqs);

  int max_freq = (int) achar_max(num_elems, freqs);
  int pos_moda = lin_search(max_freq, num_elems, freqs);

  double moda = elems[pos_moda];
  int is_moda_repetida = ha_modas_repetidas(moda, max_freq, num_elems, freqs, elems);

  free(freqs);

  if ((max_freq == 0) || is_moda_repetida) return -2;

  return moda;
}


int print_relatorio(int qtd_alunos, double *notas) {
  double media = calc_media(qtd_alunos, notas);
  printf("Media: %.2lf\n", media);

  achar_maior_nota(qtd_alunos, notas);
  achar_menor_nota(qtd_alunos, notas);

  int acima_media = calc_acima_media(media, qtd_alunos, notas);
  printf("Acima da media: %d\n", acima_media);


  double *notas_cpy = malloc( sizeof(double) * qtd_alunos );

  if (notas_cpy == NULL) return 0;

  memcpy(notas_cpy, notas, sizeof(double) * qtd_alunos);


  double mediana = calc_mediana(qtd_alunos, notas_cpy);
  printf("Mediana: %.2lf\n", mediana);


  double moda = calc_moda(qtd_alunos, notas);

  if (moda == -1)
    return 0;
  else if (moda == -2)
    printf("Moda: Nao ha moda unica\n");
  else
    printf("Moda: %.2lf\n", moda);
  
  free(notas_cpy);
  
  return 1;
}


int fazer_relatorio(int old_size, int qtd_alunos, double *notas) {
  receber_notas(old_size, qtd_alunos, notas);

  int status_relatorio = print_relatorio(qtd_alunos, notas);
  if (status_relatorio == 0) return EXIT_FAILURE;

  return 1;
}


int main(void) {
  int qtd_alunos1 = 0;

  scanf("%d", &qtd_alunos1);


  double *notas = NULL;
  notas = (double*) calloc(qtd_alunos1, sizeof(double) * qtd_alunos1);

  if (notas == NULL) return EXIT_FAILURE;


  printf("Relatorio inicial\n");

  int status_relatorio_1 = fazer_relatorio(0, qtd_alunos1, notas);
  if (status_relatorio_1 == 0) return EXIT_FAILURE;


  double *notas_old = NULL;
  notas_old = (double*) calloc(qtd_alunos1, sizeof(double));

  if (notas_old == NULL) return EXIT_FAILURE;

  memcpy(notas_old, notas, sizeof(double) * qtd_alunos1);



  int qtd_alunos2 = 0;

  scanf("%d", &qtd_alunos2);

  qtd_alunos2 += qtd_alunos1;


  notas = (double*) realloc(notas, qtd_alunos2 * sizeof(double));
  if (notas == NULL) return 0;

  memcpy(notas, notas_old, sizeof(double) * qtd_alunos2);


  printf("\nRelatorio atualizado\n");

  int status_relatorio_2 = fazer_relatorio(qtd_alunos1, qtd_alunos2, notas);
  if (status_relatorio_2 == 0) return EXIT_FAILURE;


  free(notas);

  return EXIT_SUCCESS;
}