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

//initialise un snake
Snake* initSnake(int x, int y);
//libère la mémoire allouée pour un snake
void freeSnake(Snake* snake);
//envoie un movement fait par l'utilisateur
t_move sendMySnakeMove();
//bouge le snake
void moveSnake(Snake** head, t_move dir, int grow, Arena* arena);
//fonction de coloriage
void markAccessibleCells(Arena* arena,Snake* s,int** distance);
//algorithme qui décide le prochain coup par rapport à la distance
t_move decideNextMove(Arena* arena, Snake* s, int** distance);
//fonction qui compte le nombre de cases accessibles
int countAccessibleCells(Arena* arena, int** distance);
//fonction qui compte le score de la partie
int evaluateBoard(Arena* arena, Snake* mySnake, Snake* enemySnake, int** distanceMySnake, int** distanceEnemySnake);
//fonction qui implémente l'algorithme minimax
int minimax(Arena* arena, Snake* mySnake, Snake* enemySnake, int** distanceMySnake, int** distanceEnemySnake, int depth, int alpha, int beta, int maximizingPlayer,int grow);
//fonction qui décide le prochain coup en utilisant l'algorithme minimax
t_move decideMinimaxMove(Arena* arena, Snake* mySnake, Snake* enemySnake, int** distanceMySnake, int** distanceEnemySnake, int depth,int grow);


#endif