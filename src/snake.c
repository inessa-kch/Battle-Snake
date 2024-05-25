#include <stdio.h>
#include "snake.h"
#include "snakeAPI.h"

//le ​joueur 0 (qui joue le premier) commence à la position (2, H/2) et le ​joueur 1​ à la position ​(L-3, H/2)​.

void initSnake(int x, int y, int size) {
    Snake* s = (Snake*)malloc(sizeof(Snake));
    s->x = x;
    s->y = y;
    s->dir = NORTH;
    s->size = size;
    s->suivant = NULL;

    // // Initialiser le reste du corps du serpent
    // Snake* current = head;
    // for (int i = 1; i < size; i++) {
    //     Snake* newPart = (Snake*)malloc(sizeof(Snake));
    //     newPart->x = x - i;  // Supposons que le serpent commence horizontalement vers la droite
    //     newPart->y = y;
    //     newPart->dir = 0;
    //     newPart->size = size;
    //     newPart->suivant = NULL;
    //     current->suivant = newPart;
    //     current = newPart;
    //}
}


void freeSnake(Snake* snake){
    Snake* tmp = snake;
    Snake* suiv;

    while (tmp != NULL) {
        suiv = tmp->suivant;
        free(tmp);
        tmp = suiv;
    }
}



void growSnake(Snake* s) {
    Snake* tmp = s;
    while (tmp->suivant != NULL) {
        tmp = tmp->suivant;
    }

    Snake* n = (Snake*)malloc(sizeof(Snake));
    n->x = tmp->x;
    n->y = tmp->y;
    n->dir = tmp->dir;
    n->suivant = NULL;
    tmp->suivant = n;
}


void updateSnakePosition(Snake* head) {
    Snake* current = head;
    int prevX = head->x;
    int prevY = head->y;

    switch (head->dir) {
        case EAST: head->x += 1; break;
        case WEST: head->x -= 1; break;
        case NORTH: head->y -= 1; break;
        case SOUTH: head->y += 1; break;
    }

    while (current->suivant != NULL) {
        current = current->suivant;
        int tempX = current->x;
        int tempY = current->y;
        current->x = prevX;
        current->y = prevY;
        prevX = tempX;
        prevY = tempY;
    }
}