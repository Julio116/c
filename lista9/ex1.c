#include <stdio.h>
#include <stdlib.h>


char COLORS[7] = { 'r', 'g', 'b', 'c', 'm', 'y', '\0' };


struct stackNode {
    char color;
    struct stackNode *nextPtr;
};


struct ColorReplacement {
    char color1;
    char color2;
    char colorReplace;
};


typedef struct stackNode StackNode;
typedef struct ColorReplacement ColorReplacement;
typedef StackNode *StackNodePtr;


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
    int found_triple = 0;
    StackNodePtr currentPtr = *topPtr;

    for (size_t i = 0; i < 3; ++i) {
        if (currentPtr == NULL) {
            return found_triple;
        }

        if (currentPtr->color == color) {
            numSameColor++;
        }

        if (numSameColor == 3) {
            pop(topPtr);
            pop(topPtr);
            pop(topPtr);
            found_triple = 1;
        } else {
            currentPtr = currentPtr->nextPtr;
        }
    }

    return found_triple;
}


// Checa se `colorReplacement` está no topo da stack,
// se estiver, o substitui. se nao estiver, nao altera a stack
int replaceColor(StackNodePtr *topPtr, ColorReplacement colorReplacement) {
    StackNodePtr currentPtr = *topPtr;
    if (!currentPtr) return 0;

    StackNodePtr nextPtr = currentPtr->nextPtr;
    if (!nextPtr) return 0;

    char color1 = colorReplacement.color1;
    char color2 = colorReplacement.color2;
    int found_pattern = 0;

    // testar nas duas ordens (permutacoes)
    if ((currentPtr->color == color1) && (nextPtr->color == color2)) {
        found_pattern = 1;
    }
    if ((currentPtr->color == color2) && (nextPtr->color == color1)) {
        found_pattern = 1;
    }

    if (found_pattern) {
        pop(topPtr);
        pop(topPtr);
        push(topPtr, colorReplacement.colorReplace);
    }

    return found_pattern;
}


int get_size_stack(StackNodePtr *top_ptr) {
    StackNodePtr current_ptr = *top_ptr;
    int size_stack = 0;

    while (current_ptr) {
        size_stack++;
        current_ptr = current_ptr->nextPtr;
    }

    return size_stack;
}


// checa as configuracoes de cores dadas na stack,
// se existirem sao removidas, se nao existirem,
// nada acontece. substitui apenas um padrao
// (tripla ou dupla) por chamada.
void checkColorsReplacement(StackNodePtr *topPtr) {
    // testa se ha tripla de qualquer cor no topo da stack
    int size_stack = get_size_stack(topPtr);

    for (size_t j = 0; j < size_stack; ++j) {
        for (size_t i = 0; i < 6; i++)
        {
            int status_tripla = popTripleColor(topPtr, COLORS[i]);
        }

        replaceColor(topPtr, (ColorReplacement) { 'g', 'b', 'c' });
        replaceColor(topPtr, (ColorReplacement) { 'r', 'b', 'm' });
        replaceColor(topPtr, (ColorReplacement) { 'r', 'g', 'y' });
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