#ifndef SNAKE_H
#define SNAKE_H
#include "snakeAPI.h"

struct Arena;

typedef struct {
    int x;
    int y;
} Position;



typedef struct _snake {
    int x;
    int y;
    struct _snake* suivant;
} Snake;


Snake* initSnake(int x, int y);
void freeSnake(Snake* snake);
t_move sendMySnakeMove();
void moveSnake(Snake** head, t_move dir, int grow);












#endif