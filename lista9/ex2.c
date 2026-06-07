#include <stdio.h>
#include <stdlib.h>


enum Comando { I, R, L, F };


struct tarefaNode {
    unsigned id;
    unsigned prioridade;
   
    struct tarefaNode *proxTarefa;
};


typedef enum Comando Comando;

typedef struct tarefaNode TarefaNode;
typedef TarefaNode *TarefaNodePtr;


/*
ponteiros para o inicio e fim da cadeia.
se cadeia vazia, ambos NULL.
se cadeia com 1 elemento, ambos iguais.
se cadeia com >1 elemento, ambos diferentes.
*/

TarefaNodePtr iniTarefa = NULL;
TarefaNodePtr finalTarefa = NULL;


// insere tarefa no final da cadeia.
// 0: erro. 1: sucesso.
int insert(unsigned id, unsigned prioridade) {
    TarefaNodePtr novoPtr = malloc(sizeof(TarefaNode));
   
    if (novoPtr != NULL) {
        novoPtr->id = id;
        novoPtr->prioridade = prioridade;
        novoPtr->proxTarefa = NULL;
       
        if (iniTarefa == NULL) {
            iniTarefa = novoPtr;
            finalTarefa = novoPtr;
        } else {
            finalTarefa->proxTarefa = novoPtr;
            finalTarefa = novoPtr;
        }

        return 1;
    } else {
        puts("Nao foi possivel alocar memoria");

        return 0;
    }
}


void printTarefa(TarefaNodePtr tarefaPtr) {
    printf("id=%u prioridade=%u\n", tarefaPtr->id, tarefaPtr->prioridade);
}


int isEmpty() {
    return iniTarefa == NULL;
}


void printCadeia() {
    if (isEmpty()) {
        puts("Fila vazia");
    } else {
        TarefaNodePtr atualPtr = iniTarefa;

        while (atualPtr != NULL) {
        // for (size_t i = 0; i < 10; i++)
        // {
            printTarefa(atualPtr);
            atualPtr = atualPtr->proxTarefa;
        }
        // }
    }
}


// deleta a tarefa no final
void delete() {
    TarefaNodePtr tempPtr = iniTarefa;

    if (iniTarefa == NULL) {
        puts("Fila vazia");
    } else {
        iniTarefa = iniTarefa->proxTarefa;

        printf("Removida: ");
        printTarefa(tempPtr);
        free(tempPtr);
    }
}


int main(void) {
    int receberEntrada = 1;

    while (receberEntrada) {
        char comando = '\0';
        scanf(" %c", &comando);

        switch (comando) {
            case 'I':
                unsigned id = 0;
                unsigned prioridade = 0;

                scanf("%u %u", &id, &prioridade);
                insert(id, prioridade);
                break;
            case 'R':
                delete();
                break;
            case 'L':
                printCadeia();
                break;
            default:
                receberEntrada = 0;
                break;
        }
    }

    return EXIT_SUCCESS;
}