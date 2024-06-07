#ifndef SNAKE_H
#define SNAKE_H
#include "snakeAPI.h"
#include "arena.h"



typedef struct {
    int x;
    int y;
} Position;



typedef struct _snake {
    int x;
    int y;
    int length;
    struct _snake* suivant;
} Snake;


Snake* initSnake(int x, int y);
void freeSnake(Snake* snake);
t_move sendMySnakeMove();
void moveSnake(Snake** head, t_move dir, int grow, Arena* arena);
//void moveSnake(Snake** snake, t_move direction, int grow, Arena* arena);
void undoMoveSnake(Snake* snake, Position* originalBody, int originalLength, Arena* arena);

void markAccessibleCells(Arena* arena,Snake* s,int** distance);
t_move decideNextMove(Arena* arena, Snake* s, int** distance);
int countAccessibleCells(Arena* arena, int** distance);
int evaluateBoard(Arena* arena, Snake* mySnake, Snake* enemySnake, int** distanceMySnake, int** distanceEnemySnake);
int minimax(Arena* arena, Snake* mySnake, Snake* enemySnake, int** distanceMySnake, int** distanceEnemySnake, int depth, int alpha, int beta, int maximizingPlayer);
t_move decideMinimaxMove(Arena* arena, Snake* mySnake, Snake* enemySnake, int** distanceMySnake,int** distanceEnemySnake, int depth);
//int minimax(Arena* arena, Snake* mySnake, Snake* enemySnake, int** distanceMySnake, int** distanceEnemySnake, int depth, int alpha, int beta, int maximizingPlayer,int grow);
//t_move decideMinimaxMove(Arena* arena, Snake* mySnake, Snake* enemySnake, int** distanceMySnake, int** distanceEnemySnake, int depth,int grow);


#endif