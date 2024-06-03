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
    int y;
    Arena* arena = initArena("TRAINING SUPER_PLAYER difficulty=1 seed=2002", &y);
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

    printArena();
    printArenax(arena);

    int myTurn = 0;
    int enemyTurn = 0;


    while (Gamerunning) {
        //tour counter
        if (tour % 10 == 0) {
                grow=1;
            }
        else{
                grow=0;
            }


        if (y == 0 && !myTurn) {
                t_move dir=sendMySnakeMove();
                moveSnake(&mySnake, dir,grow);
                ///////////////////////////////////////////
                //some tests to check if the snake is moving correctly
                Snake* tmp = mySnake;
                while (tmp != NULL) {
                    printf("x1: %d\n", tmp->x);
                    printf("y1: %d\n", tmp->y);
                    tmp = tmp->suivant;
                }
            ///////////////////////////////////////////
                myTurn = 1;



        } else if (y == 1 && !enemyTurn) {
                t_move enemyMove;
                t_return_code moveReceived = getMove(&enemyMove);
                //int j=getEnemySnakePosition(enemySnake);
                moveSnake(&enemySnake, enemyMove,grow);
                ///////////////////////////////////////////
                //some tests to check if the snake is moving correctly
                Snake* tmp2 = enemySnake;
                while (tmp2 != NULL) {
                    printf("x2: %d\n", tmp2->x);
                    printf("y2: %d\n", tmp2->y);
                    tmp2 = tmp2->suivant;
                }
                ///////////////////////////////////////////

                enemyTurn = 1;

    
        }
        y = (y + 1) % 2;
   
        if (myTurn && enemyTurn) {
            tour++;
            printf("tour: %d\n", tour);
            myTurn = 0;
            enemyTurn = 0;
            printArena();
        }

    }

    freeArena(arena);
    freeSnake(mySnake);
    freeSnake(enemySnake);
    closeConnection();
    return 0;
}





