#ifndef SNAKE_H
#define SNAKE_H


struct Arena;

typedef struct _snake {
    int x;
    int y;
    int dir;
    int size;
    struct _snake* suivant;
} Snake;


Snake* initSnake(int x, int y, int size);
void freeSnake(Snake* snake);
void growSnake(Snake* snake);
int dirSnake(Snake* s, Arena* a);
void updateSnakePosition(Snake* head);
//void changeDirection(Snake* snake, int newDir);
//void printSnake(Snake* snake);










#endif