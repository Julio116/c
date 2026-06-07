#include <stdio.h>
#include <stdlib.h>


typedef struct stackNode StackNode;
typedef struct ColorReplacement ColorReplacement;

typedef StackNode *StackNodePtr;

typedef enum Color Color;

enum Color {
    RED='r', GREEN='g', BLUE='b', CYAN='c', MAGENTA='m', YELLOW='y'
};


struct stackNode {
    char color;
    struct stackNode *nextPtr;
};


struct ColorReplacement {
    char colorCheck1;
    char colorCheck2;
    char colorReplace;
};


void push(StackNodePtr *topPtr, char color) {
    StackNodePtr newPtr = malloc( sizeof(StackNode) );

    if (newPtr != NULL) {
        newPtr->color = color;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    } else {
        printf("A cor %c nao foi inserida.\n", color);
    }
}


char pop(StackNodePtr *topPtr) {
    StackNodePtr tempPtr = *topPtr;
    char popColor = (*topPtr)->color;
    *topPtr = (*topPtr)->nextPtr;
    
    free(tempPtr);
    return popColor;
}


void printStack(StackNodePtr currentPtr) {
    if (currentPtr == NULL) {
        puts("Pilha vazia!");
        puts("");
    } else {
        while (currentPtr != NULL) {
            printf("%c\n", currentPtr->color);
            currentPtr = currentPtr->nextPtr;
        }
        printf("\n");
    }
}


int isEmpty(StackNodePtr topPtr) {
    return topPtr == NULL;
}


// faz pop se os 3 elementos mais altos da pilha forem `color`,
// se nao houver, nao altera a stack. retorna 1 ou 0, para garantir
// que remove um trio apenas uma vez.
int popTripleColor(StackNodePtr *topPtr, char color) {
    unsigned numSameColor = 0;
    StackNodePtr currentPtr = *topPtr;
    int eliminou = 0;

    while (currentPtr != NULL) {
        if (currentPtr->color == color) {
            numSameColor++;
        }

        if (numSameColor == 3) {
            pop(topPtr);
            pop(topPtr);
            pop(topPtr);

            currentPtr = NULL;
            eliminou = 1;
        } else {
            currentPtr = currentPtr->nextPtr;
        }
    }

    return eliminou;
}


// Checa se `colorReplacement` está no topo da stack,
// se estiver, o substitui. se nao estiver, nao altera a stack
void replaceColor(StackNodePtr *topPtr, ColorReplacement colorReplacement) {
    StackNodePtr currentPtr = *topPtr;
    unsigned numCorrectcolors = 0;

    while (currentPtr != NULL) {
        if (numCorrectcolors < 2) {
            char colorCheck1 = colorReplacement.colorCheck1;
            char colorCheck2 = colorReplacement.colorCheck2;

            if ((currentPtr->color == colorCheck1) || (currentPtr->color == colorCheck2)) {
                numCorrectcolors++;
            }
            currentPtr = currentPtr->nextPtr;
        } else {
            pop(topPtr);
            pop(topPtr);
            push(topPtr, colorReplacement.colorReplace);
            currentPtr = NULL;
        }
    }
}


// checa as configuracoes de cores dadas na stack,
// se existirem sao removidas, se nao existirem,
// nada acontece.
void checkColorsReplacement(StackNodePtr *topPtr) {
    // garante que as cores sao alteradas apenas uma vez
    int replaced = 0;

    // testa se ha tripla de qualquer cor no topo da stack
    for (char testColor = RED; testColor <= YELLOW; testColor++)
    {
        if (replaced) break;

        int status_tripla = popTripleColor(topPtr, testColor);
        if (status_tripla) replaced = 1;
    }

    if (!replaced) {
        ColorReplacement colorReplacement1 = { GREEN, BLUE, CYAN };
        ColorReplacement colorReplacement2 = { RED, BLUE, MAGENTA };
        ColorReplacement colorReplacement3 = { RED, GREEN, YELLOW };

        replaceColor(topPtr, colorReplacement1);
        replaceColor(topPtr, colorReplacement2);
        replaceColor(topPtr, colorReplacement3);
    }
}


int main(void) {
    char inputColor = 0;
    StackNodePtr stackPtr = NULL;

    while ( scanf(" %c", &inputColor) != EOF ) {
        push(&stackPtr, inputColor);
        checkColorsReplacement(&stackPtr);
        printStack(stackPtr);
    }

    puts("Thank You So Much For Playing My Game!");
    
    return EXIT_SUCCESS;
}