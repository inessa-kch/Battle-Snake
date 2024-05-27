#include <stdio.h>
#include <stdlib.h>
#include "snakeAPI.h"
#include "arena.h"
#include "snake.h"

//le ​joueur 0 (qui joue le premier) commence à la position (2, H/2) et le ​joueur 1​ à la position ​(L-3, H/2)​.

Snake* initSnake(int x, int y, int size) {
    Snake* s = (Snake*)malloc(sizeof(Snake));
    s->x = x;
    s->y = y;
    s->dir = 0;
    s->size = size;
    s->suivant = NULL;

    //Initialiser le reste du corps du serpent
    Snake* current = s;
    for (int i = 1; i < size; i++) {
        Snake* newPart = (Snake*)malloc(sizeof(Snake));
        newPart->x = x - i;  // Supposons que le serpent commence horizontalement vers la droite
        newPart->y = y;
        newPart->dir = 0;
        newPart->size = size;
        newPart->suivant = NULL;
        current->suivant = newPart;
        current = newPart;
    }
    return s;
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
    s->size++;
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




// int dirSnake(Snake* s, Arena* a){
//     int x = s->x;
//     int y = s->y;
//     if (s->dir == 0){
//         if (a->cells[y-1][x].wallTop == 1){
//             return 0;
//         }
//     }
//     if (s->dir == 1){
//         if (a->cells[y][x+1].wallLeft == 1){
//             return 1;
//         }
//     }
//     if (s->dir == 2){
//         if (a->cells[y][x].wallBottom == 1){
//             return 2;
//         }
//     }
//     if (s->dir == 3){
//         if (a->cells[y][x].wallLeft == 1){
//             return 3;
//         }
//     }
//     return -1;
// }


int dirSnake(Snake* s, Arena* a) {
    int currentX = s->x;
    int currentY = s->y;
    int dir = s->dir;

    // Check possible directions and avoid obstacles
    // Prioritize direction changes to avoid walls

    if (dir != SOUTH && currentY > 0 && a->cells[currentY - 1][currentX].wallBottom == 0) {
        // Move North if it's not the current direction and there's no obstacle
        return NORTH;
    } else if (dir != WEST && currentX < a->sizeX - 1 && a->cells[currentY][currentX + 1].wallLeft == 0) {
        // Move East if it's not the current direction and there's no obstacle
        return EAST;
    } else if (dir != NORTH && currentY < a->sizeY - 1 && a->cells[currentY + 1][currentX].wallTop == 0) {
        // Move South if it's not the current direction and there's no obstacle
        return SOUTH;
    } else if (dir != EAST && currentX > 0 && a->cells[currentY][currentX - 1].wallRight == 0) {
        // Move West if it's not the current direction and there's no obstacle
        return WEST;
    } else {
        // Default case (shouldn't reach here if the arena is properly designed)
        return dir;
    }
}







// void updateSnakePosition(Snake* head) {
//     Snake* current = head;
//     int prevX = head->x;
//     int prevY = head->y;

//     switch (head->dir) {
//         case EAST: head->x += 1; break;
//         case WEST: head->x -= 1; break;
//         case NORTH: head->y -= 1; break;
//         case SOUTH: head->y += 1; break;
//     }

//     while (current->suivant != NULL) {
//         current = current->suivant;
//         int tempX = current->x;
//         int tempY = current->y;
//         current->x = prevX;
//         current->y = prevY;
//         prevX = tempX;
//         prevY = tempY;
//     }
// }


void updateSnakePosition(Snake* head) {
    Snake* current = head;
    int prevX = head->x;
    int prevY = head->y;
    int prevDir = head->dir;

    // Update the head position
    switch (head->dir) {
        case EAST: head->x += 1; break;
        case WEST: head->x -= 1; break;
        case NORTH: head->y -= 1; break;
        case SOUTH: head->y += 1; break;
    }

    // Update the body segments
    while (current->suivant != NULL) {
        current = current->suivant;
        int tempX = current->x;
        int tempY = current->y;
        int tempDir = current->dir;
        current->x = prevX;
        current->y = prevY;
        current->dir = prevDir;
        prevX = tempX;
        prevY = tempY;
        prevDir = tempDir;
    }
}


