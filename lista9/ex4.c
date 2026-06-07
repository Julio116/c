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
            puts("valor duplicado");
        }
    }
}


// percorrer a arvore inorder, se nao estiver vazia
void inOrder(PlayerNodePtr playerPtr) {
    if (playerPtr != NULL) {
        inOrder(playerPtr->leftPtr);
        printf("%3d", playerPtr->data);
        inOrder(playerPtr->rightPtr);
    }
}


// percorrer a arvore preorder, se nao estiver vazia
void preOrder(PlayerNodePtr playerPtr) {
    if (playerPtr != NULL) {
        printf("%3d", playerPtr->data);
        preOrder(playerPtr->leftPtr);
        preOrder(playerPtr->rightPtr);
    }
}


// percorrer a arvore postorder, se nao estiver vazia
void postOrder(PlayerNodePtr playerPtr) {
    if (playerPtr != NULL) {
        postOrder(playerPtr->leftPtr);
        postOrder(playerPtr->rightPtr);
        printf("%3d", playerPtr->data);
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


int getMax(PlayerNodePtr playerPtr) {
    int max = INT_MIN;

    if (playerPtr != NULL) {
        int currentData = playerPtr->data;
        max = (currentData > max) ? currentData : max;

        int tmpLeft = getMax(playerPtr->leftPtr);
        max = (tmpLeft > max) ? tmpLeft : max;

        int tmpRight = getMax(playerPtr->rightPtr);
        max = (tmpRight > max) ? tmpRight : max;
    }

    return max;
}


int getMin(PlayerNodePtr playerPtr) {
    int min = INT_MAX;

    if (playerPtr != NULL) {
        int currentData = playerPtr->data;
        min = (currentData < min) ? currentData : min;

        int tmpLeft = getMin(playerPtr->leftPtr);
        min = (tmpLeft < min) ? tmpLeft : min;

        int tmpRight = getMin(playerPtr->rightPtr);
        min = (tmpRight < min) ? tmpRight : min;
    }

    return min;
}


int getHeight(PlayerNodePtr playerPtr) {

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


    preOrder(iniPtr);
    puts("");

    postOrder(iniPtr);
    puts("");

    inOrder(iniPtr);
    puts("");


    printf("\n%d", countTree(iniPtr));
    printf("\n%d", getMax(iniPtr));
    printf("\n%d", getMin(iniPtr));


    return EXIT_SUCCESS;
}