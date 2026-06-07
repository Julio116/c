#include <stdio.h>
#include <stdlib.h>


enum Prioridade { BLOCADO, ATRASADO, ADIANTADO };


struct disciplina {
    char nome[50];
    unsigned vagas;
};


struct matriculaNode {
    long timeout; // em segundos
    long chegada; // em segundos

    unsigned prioridade;
    unsigned matricula;

    double cr;

    struct matriculaNode *proxMatricula;
};


typedef struct disciplina Disciplina;
typedef struct matriculaNode MatriculaNode;
typedef MatriculaNode *MatriculaNodePtr;

typedef enum Prioridade Prioridade;


void enqueue(MatriculaNodePtr *headPtr, MatriculaNodePtr *tailPtr) {

}


int main(void) {
    return EXIT_SUCCESS;
}