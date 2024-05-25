#ifndef SNAKE_H
#define SNAKE_H


typedef struct _snake {
    int x;
    int y;
    int dir;
    int size;
    struct _snake* suivant;
} Snake;


void initSnake(int x, int y, int size);
void freeSnake(Snake* snake);
void moveSnake(Snake* snake);
void growSnake(Snake* snake);
void changeDirection(Snake* snake, int newDir);
void printSnake(Snake* snake);










#endif