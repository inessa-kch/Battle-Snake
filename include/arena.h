#ifndef ARENA_H
#define ARENA_H




typedef struct _wall{
    int x1;
    int y1;
    int x2;
    int y2;
} Wall;

typedef struct _arena{
    Wall* walls;
    int nbWalls;
    int sizeX;
    int sizeY;
} Arena;



Arena* createArena(char* gameType, int* x);

void freeArena(Arena* arena);









#endif