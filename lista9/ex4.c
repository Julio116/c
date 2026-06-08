#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


struct PlayerNode {
    struct PlayerNode *leftPtr;
    int data;
    struct PlayerNode *rightPtr;
};


typedef struct PlayerNode PlayerNode;
typedef PlayerNode *PlayerNodePtr;


void insertNode(PlayerNodePtr *playerPtr, int value) {
    if (*playerPtr == NULL) { // arvore vazia
        *playerPtr = malloc(sizeof(PlayerNode));

        if (*playerPtr != NULL) {
            (*playerPtr)->data = value;
            (*playerPtr)->leftPtr = NULL;
            (*playerPtr)->rightPtr = NULL;
        } else {
            printf("%d nao inserido", value);
        }
    } else { // arvore nao vazia
        if (value < (*playerPtr)->data) {
            insertNode(&((*playerPtr))->leftPtr, value);
        } else if (value > (*playerPtr)->data) {
            insertNode(&((*playerPtr))->rightPtr, value);
        } else {
            // puts("valor duplicado");
        }
    }
}


// percorrer a arvore inorder, se nao estiver vazia
void inOrder(PlayerNodePtr playerPtr) {
    if (playerPtr != NULL) {
        inOrder(playerPtr->leftPtr);
        printf(" %d", playerPtr->data);
        inOrder(playerPtr->rightPtr);
    }
}


// percorrer a arvore preorder, se nao estiver vazia
void preOrder(PlayerNodePtr playerPtr) {
    if (playerPtr != NULL) {
        printf(" %d", playerPtr->data);
        preOrder(playerPtr->leftPtr);
        preOrder(playerPtr->rightPtr);
    }
}


// percorrer a arvore postorder, se nao estiver vazia
void postOrder(PlayerNodePtr playerPtr) {
    if (playerPtr != NULL) {
        postOrder(playerPtr->leftPtr);
        postOrder(playerPtr->rightPtr);
        printf(" %d", playerPtr->data);
    }
}


int countTree(PlayerNodePtr playerPtr) {
    int sizeTree = 0;

    if (playerPtr != NULL) {
        sizeTree += countTree(playerPtr->leftPtr);
        sizeTree += countTree(playerPtr->rightPtr);
        sizeTree += 1;
    }

    return sizeTree;
}


int max(int a, int b) {
    return (a > b ? a : b);
}


int getMax(PlayerNodePtr playerPtr) {
    int buff = INT_MIN;

    if (playerPtr != NULL) {
        int currentData = playerPtr->data;
        buff = max(currentData, buff);

        int tmpLeft = getMax(playerPtr->leftPtr);
        buff = max(tmpLeft, buff);

        int tmpRight = getMax(playerPtr->rightPtr);
        buff = max(tmpRight, buff);
    }

    return buff;
}


int min(int a, int b) {
    return (a < b ? a : b);
}


int getMin(PlayerNodePtr playerPtr) {
    int buff = INT_MAX;

    if (playerPtr != NULL) {
        int currentData = playerPtr->data;
        buff = min(currentData, buff);

        int tmpLeft = getMin(playerPtr->leftPtr);
        buff = min(tmpLeft, buff);

        int tmpRight = getMin(playerPtr->rightPtr);
        buff = min(tmpRight, buff);
    }

    return buff;
}


int countLeaves(PlayerNodePtr playerPtr) {
    if (!playerPtr) {
        return 0;
    }

    if (playerPtr->leftPtr == NULL && playerPtr->rightPtr == NULL) {
        return 1;
    }

    return countLeaves(playerPtr->leftPtr) + countLeaves(playerPtr->rightPtr);
}


int getHeight(PlayerNodePtr topPtr) {
    if (!topPtr) {
        return -1;
    }

    int left_height = getHeight(topPtr->leftPtr);
    int right_height = getHeight(topPtr->rightPtr);

    if (left_height > right_height) {
        return left_height + 1;
    } else {
        return right_height + 1;
    }
}


int main(void) {
    PlayerNodePtr iniPtr = NULL;
    int continuarEntrada = 1;

    // inserir as entradas na arvore
    while (continuarEntrada) {
        int valEntrada = 0;
        scanf("%d", &valEntrada);

        if (valEntrada == -1) {
            continuarEntrada = 0;
        } else {
            insertNode(&iniPtr, valEntrada);
        }
    }

    int num_nos = countTree(iniPtr);

    if (num_nos == 0) {
        printf("ARVORE VAZIA\n");
    } else {
        printf("PREORDEM:");
        preOrder(iniPtr);
        printf("\n");

        printf("EMORDEM:");
        inOrder(iniPtr);
        printf("\n");

        printf("POSORDEM:");
        postOrder(iniPtr);
        printf("\n");


        printf("NOS: %d\n", countTree(iniPtr));
        printf("FOLHAS: %d\n", countLeaves(iniPtr));
        printf("ALTURA: %d\n", getHeight(iniPtr));
        printf("MENOR: %d\n", getMin(iniPtr));
        printf("MAIOR: %d\n", getMax(iniPtr));
    }


    return EXIT_SUCCESS;
}