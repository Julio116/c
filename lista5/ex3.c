#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// printar conjunto de numeros
void print_nums(int n, int *arr) {
  for (size_t i = 0; i < n; i++)
  {
    printf("%d\n", arr[i]);
  }
}


// adicionar um numero ao conjunto, realocando
int* add_num(int val, int *qtd_nums, int *nums) {
  nums = (int*) realloc(nums, ((*qtd_nums) + 1) * sizeof(int));

  if (nums == NULL) return NULL;

  nums[ (*qtd_nums) ] = val;

  (*qtd_nums)++;

  return nums;
}


// receber numeros dos teclados
int* receber_nums(int *qtd_nums, int *nums) {
  int n_tmp = 0;

  while ( scanf("%d", &n_tmp) != EOF ) {
    nums = add_num(n_tmp, qtd_nums, nums);

    if (nums == NULL) return NULL;
  }

  return nums;
}


// extrair os numeros pares/impares de um conjunto de numeros naturais
// `paridade`: 0 par, 1 impar
int* separar_paridade(int *qtd_db, int *nums_db, int *qtd_paridade, int *nums_paridade, int paridade) {
  // posicao do ultimo elemento no array
  int paridade_index = 0;

  for (size_t i = 0; i < (*qtd_db); i++) {
    int n = nums_db[i];
    int condicao = 0;

    if (paridade) {
      condicao = ((n % 2) != 0);
    } else {
      condicao = ((n % 2) == 0);
    }

    if (condicao) {
      nums_paridade = add_num(n, &paridade_index, nums_paridade);

      if (nums_paridade == NULL) return NULL;
    }
  }
  return nums_paridade;
}


// quantos elementos sao pares/impares
int contar_paridade(int n, int *arr, int paridade) {
  int condicao = 0;
  int qtd = 0;

  for (size_t i = 0; i < n; ++i)
  {
    int num = arr[i];

    if (paridade == 1) {
      condicao = ((num % 2) != 0);
    } else {
      condicao = ((num % 2) == 0);
    }

    if (condicao) qtd++;
  }

  return qtd;
}


int main(void) {
  int qtd_nums = 0;
  int *nums = NULL;
  
  nums = receber_nums(&qtd_nums, nums);

  if (nums == NULL) return EXIT_FAILURE;


  printf("Mais um bom dia de trabalho!\n");

  int *pares = NULL;
  int *impares = NULL;

  int qtd_pares = contar_paridade(qtd_nums, nums, 0);
  int qtd_impares = contar_paridade(qtd_nums, nums, 1);


  if (qtd_pares > 0) {
    pares = separar_paridade(&qtd_nums, nums, &qtd_pares, pares, 0);

    if (pares == NULL) return EXIT_FAILURE;
  }


  if (qtd_impares > 0) {
    impares = separar_paridade(&qtd_nums, nums, &qtd_impares, impares, 1);

    if (impares == NULL) return EXIT_FAILURE;
  }

  if ((qtd_pares > 0) || (qtd_impares > 0)) {
    print_nums(qtd_impares, impares);
    print_nums(qtd_pares, pares);

    printf("Vou visitar esses lugares de novo... algum dia.\n");
  }

  // print_nums(qtd_pares, pares);
  // printf("%d %d\n", qtd_pares, qtd_nums);

  free(nums);
  free(pares);
  free(impares);

  return EXIT_SUCCESS;
}