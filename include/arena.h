#ifndef ARENA_H
#define ARENA_H
#include "snake.h"





typedef struct {
    int wallTop;
    int wallBottom;
    int wallLeft;
    int wallRight;
    int snake; // 0 if no snake, 1 if my snake, 2 if enemy snake
} Cell;

typedef struct {
    int sizeX;
    int sizeY;
    Cell** cells;
} Arena;




Arena* initArena(char* gameType, int* x);

void freeArena(Arena* arena);

void printArenax(Arena* arena);









#endif