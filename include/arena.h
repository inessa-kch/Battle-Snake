#ifndef ARENA_H
#define ARENA_H






typedef struct {
    int wallTop;
    int wallBottom;
    int wallLeft;
    int wallRight;
    int snake; // 0 if no snake, 1 if snake
} Cell;

typedef struct {
    int sizeX;
    int sizeY;
    Cell** cells;
} Arena;




Arena* initArena(char* gameType, int* x);

void freeArena(Arena* arena);

void myprintArena(Arena* arena);









#endif