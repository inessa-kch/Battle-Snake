#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "clientAPI.h"
#include "snakeAPI.h"
#include "arena.h"
#include "snake.h"

/*varaibles globales*/
int grow;

int main() {
    connectToServer("localhost", 1234, "iness");

//while (1){
    //initialisation des variables
    int y;
    Arena* arena = initArena("TRAINING SUPER_PLAYER difficulty=0", &y);
    Snake* mySnake = NULL;
    Snake* enemySnake = NULL;
    if (y == 0) {
        printf("You are the first player\n");
        mySnake = initSnake(2, arena->sizeY / 2);
        enemySnake = initSnake(arena->sizeX - 3, arena->sizeY / 2);
        
    } else if (y == 1) {
        printf("You are the second player\n");
        mySnake = initSnake(arena->sizeX - 3, arena->sizeY / 2);
        enemySnake = initSnake(2, arena->sizeY / 2);
    }


    int Gamerunning = 1;
    int tour = 0;
    int grow=0;

    myprintArena(arena);

    int myTurn = 0;
    int enemyTurn = 0;

    
    int** distanceMySnake = (int**)malloc(arena->sizeY * sizeof(int*));
    for (int i = 0; i < arena->sizeY; i++) {
        distanceMySnake[i] = (int*)malloc(arena->sizeX * sizeof(int));
    }

        int** distanceEnemySnake = (int**)malloc(arena->sizeY * sizeof(int*));
    for (int i = 0; i < arena->sizeY; i++) {
        distanceEnemySnake[i] = (int*)malloc(arena->sizeX * sizeof(int));
    }


    while (Gamerunning) {
        
        if (tour % 10 == 0) {
                grow=1;
            }
        else{
                grow=0;
            }
        
        if (y == 0 && !myTurn) {
                markAccessibleCells(arena, mySnake, distanceMySnake);
                t_move dir= decideMinimaxMove(arena, mySnake, enemySnake, distanceMySnake,distanceEnemySnake, 12, grow);
                
                int i=sendMove(dir);
                if (i==LOSING_MOVE){
                    //sendComment("GG");
                    printf("You lost\n");
                    break;
                }
                moveSnake(&mySnake, dir,grow,arena);
                myTurn = 1;



        } else if (y == 1 && !enemyTurn) {
                markAccessibleCells(arena, enemySnake, distanceEnemySnake);
                t_move enemyMove;
                t_return_code moveReceived = getMove(&enemyMove);
                if (moveReceived == LOSING_MOVE) {
                    //sendComment("YOU LOST!!!");
                    printf("You won\n");
                    break;
                }
                moveSnake(&enemySnake, enemyMove,grow,arena);
                enemyTurn = 1;

    
        }
        y = (y + 1) % 2;
   
        if (myTurn && enemyTurn) {
            tour++;
            myTurn = 0;
            enemyTurn = 0;
            printArena();
        }

    }
    //on desalloue la mémoire
    for (int i = 0; i < arena->sizeY; i++) {
        free(distanceMySnake[i]);
    }
    free(distanceMySnake);

        for (int i = 0; i < arena->sizeY; i++) {
        free(distanceEnemySnake[i]);
    }
    free(distanceEnemySnake);

    freeArena(arena);
    freeSnake(mySnake);
    freeSnake(enemySnake);
//}
    closeConnection();
    return 0;
}