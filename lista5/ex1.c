#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NUM_CHAR_WORD 1000


// Receber os animais em `strs_db`, como entrada, do teclado.
// Retorna 1, em caso de sucesso, ou 0, em caso de erro.
int receber_ornitos(int total_strs, int pos_strs[], char *strs_db) {
  int pos_ultima_str = 0;

  for (size_t i = 0; i < total_strs; ++i) {
    // registrar posicao inicial da string
    pos_strs[i] = pos_ultima_str;


    char *str_ornitos = NULL;
    str_ornitos = (char*) calloc(NUM_CHAR_WORD, sizeof(char));

    if (str_ornitos == NULL) return 0;


    scanf("%s", str_ornitos);
    strcat(strs_db, str_ornitos);


    int size_str = strlen(str_ornitos);
    pos_ultima_str += size_str;

    // adicionar char separador das strings
    strs_db[pos_ultima_str] = ':';
    pos_ultima_str++;

    free(str_ornitos);
  }

  // ultima posicao da string
  pos_ultima_str--;

  return 1;
}


// utiliza um indice generico, aplicado a cada string de `strs_db`,
// enquanto houver caracteres restantes. retorna o tamanho da fusao.
int merge_strings(int total_strs, char *strs_db, char *merged_str, int pos_strs[]) {
  int merged_str_i = 0;
  int str_achadas = 0;

  while (1) {
    for (int i = 0; i < total_strs; ++i) {
      if (str_achadas == total_strs) return merged_str_i;

      int pos_chr = pos_strs[i];
      char atual_chr = strs_db[pos_chr];

      if ((atual_chr != ':') && (pos_chr != -1)) {
        merged_str[merged_str_i] = atual_chr;
        merged_str_i++;
        pos_strs[i] += 1;
      } else if (atual_chr == ':') {
        pos_strs[i] = -1;
        str_achadas++;
      }
    }
  }
}


void merge_chars(int size_merged, char *old_str, char *new_str) {
  int new_str_i = 0;
  int i = 0;

  while (i <= size_merged - 1)
  {
    char atual_chr = old_str[i];
    char proximo_chr = old_str[i + 1];

    if (atual_chr == proximo_chr) {
      char substituto_chr;

      if (atual_chr == 'z')
        substituto_chr = 'a';
      else
        substituto_chr = atual_chr + 1;

      new_str[new_str_i] = substituto_chr;
      i += 2;
    } else {
      new_str[new_str_i] = atual_chr;
      i++;
    }
    new_str_i++;
  }
  new_str[new_str_i] = '\0';
}


int merge_final(int size_merged, char *merged_str, char *final_str) {
  char *final_s_1 = NULL;
  final_s_1 = calloc(NUM_CHAR_WORD, 1);

  if (final_s_1 == NULL) return 0;
  else strcpy(final_s_1, final_str);

  char *final_s_2 = NULL;
  final_s_2 = calloc(NUM_CHAR_WORD, 1);

  if (final_s_2 == NULL) return 0;
  else strcpy(final_s_2, final_str);

  do {
    strcpy(final_s_1, final_s_2);

    size_merged = strlen(final_s_1);

    merge_chars(size_merged, final_s_1, final_s_2);
  } while ( strcmp(final_s_1, final_s_2) != 0 );

  printf("%s\n", final_s_2);

  free(final_s_1);
  free(final_s_2);

  return 1;
}


int main(void) {
  int total_strs = 0;

  scanf("%d", &total_strs);


  // array da posicao inicial das strings
  int pos_strs[total_strs];

  // array de todas as strings
  char *strs_db = NULL;
  strs_db = calloc(total_strs, NUM_CHAR_WORD);

  if (strs_db == NULL) return EXIT_FAILURE;


  int recebeu_input = receber_ornitos(total_strs, pos_strs, strs_db);

  if (recebeu_input == 0) return EXIT_FAILURE;


  int pos_iteracoes[total_strs];
  memcpy(pos_iteracoes, pos_strs, sizeof(pos_strs));


  char *merged_str = NULL;
  merged_str = calloc(NUM_CHAR_WORD, 1);

  if (merged_str == NULL) return EXIT_FAILURE;

  int size_merged = merge_strings(total_strs, strs_db, merged_str, pos_strs);


  printf("%s\n", merged_str);

  // merge_chars(size_merged, merged_str, final_str);
  merge_final(size_merged, merged_str, merged_str);


  free(strs_db);
  free(merged_str);

  return EXIT_SUCCESS;
}