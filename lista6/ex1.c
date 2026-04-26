#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// receber numeros do teclado
void receber_nums(int **ns_db, int n_linhas, int n_cols) {
	int n_tmp = 0;

	for (int i = 0; i < n_linhas; ++i) {
		for (int j = 0; j < n_cols; ++j) {
			scanf("%d", &n_tmp) != EOF;

			// printf("%dx%d %d\n", i, j, n_tmp);
			ns_db[i][j] = n_tmp;
		}
	}
}


// printar `ns_db`
void print_db(int n_linhas, int n_cols, int **ns_db) {
	for (int i = 0; i < n_linhas; ++i) {
		for (int j = 0; j < n_cols; ++j) {
			printf("%d ", ns_db[i][j]);
		}
		printf("\n");
	}
}


void free_cols(int n_linhas, int **ns_db) {
	for (int i = 0; i < n_linhas; ++i) {
		free( ns_db[i] );

		ns_db[i] = NULL;
	}
}


// alocar colunas para a matriz dupla
int alloc_cols(int n_linhas, int n_cols, int **mtrx) {
	// alocando colunas
	for (int i = 0; i < n_linhas; ++i) {
		mtrx[i] = (int*) calloc(n_cols, sizeof(int) * n_cols);

		if (mtrx[i] == NULL) return 0;
	}
	return 1;
}


int dobro(int n) {
	return (2 * n);
}


int quadrado(int n) {
	return pow(n, 2);
}


int absoluto(int n) {
	return abs(n);
}


void apply_op(int n_cols, int n_linhas, int **ns_db, int (*op)(int n)) {
	for (int i = 0; i < n_linhas; ++i) {
		for (int j = 0; j < n_cols; ++j) {
			int n = ns_db[i][j];
			// printf("%d %dx%d\n", n, i, j);

			ns_db[i][j] = (*op)(n);
		}
	}
}


void aplic_comando(int cmd, int n_cols, int n_linhas, int **ns_db) {
	switch (cmd) {
		case 1:
			apply_op(n_cols, n_linhas, ns_db, dobro);
			break;
		case 2:
			apply_op(n_cols, n_linhas, ns_db, quadrado);
			break;
		case 3:
			apply_op(n_cols, n_linhas, ns_db, absoluto);
			break;
	}
}


int main(void) {
	int n_linhas = 0;
	int n_cols = 0;

	scanf("%d", &n_linhas);
	scanf("%d", &n_cols);


	int size_db = n_linhas * n_cols;

	int **ns_db = (int**) calloc(n_linhas, sizeof(int*) * n_linhas);
	if (ns_db == NULL) return EXIT_FAILURE;

	int status_alloc = alloc_cols(n_linhas, n_cols, ns_db);
	if (status_alloc == 0) return EXIT_FAILURE;


	receber_nums(ns_db, n_linhas, n_cols);


	int (*ops_arr[3])(int) = { dobro, quadrado, absoluto };
	int cmd = 0;

	scanf("%d", &cmd);

	aplic_comando(cmd, n_cols, n_linhas, ns_db);
	print_db(n_linhas, n_cols, ns_db);


	free_cols(n_linhas, ns_db);

	free(ns_db);
	ns_db = NULL;

  	return EXIT_SUCCESS;
}