#ifndef ARENA_H
#define ARENA_H






typedef struct {
    int wallTop;
    int wallBottom;
    int wallLeft;
    int wallRight;
    int snake; // 0 si il n'y a pas de snake sur la case, 1 sinon
} Cell;

typedef struct {
    int sizeX;
    int sizeY;
    Cell** cells;
} Arena;



//initialise une arène
Arena* initArena(char* gameType, int* x);
//copie l'arène
Arena* copyArena(Arena* a);
//libère la mémoire allouée pour une arène
void freeArena(Arena* arena);
//affiche l'arène
void myprintArena(Arena* arena);

#endif