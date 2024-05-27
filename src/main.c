
#include <stdio.h>
#include <stdlib.h>
#include "clientAPI.h"
#include "snakeAPI.h"
#include "arena.h"
#include "snake.h"


int main(){
    
	connectToServer("localhost",1234,"iness");
    int y;
    Arena* arena = initArena("TRAINING SUPER_PLAYER",&y);
    Snake* s=NULL;
    if (y==0){
        printf("You are the first player\n");
        s =initSnake(2,arena->sizeY/2,3);
    }
    else if (y==1){
        printf("You are the second player\n");
        s =initSnake(arena->sizeX-3,arena->sizeY/2,3);
    }
    
    int Gamerunning = 1;
    t_move x;
    t_return_code moveSent;
    t_return_code moveReceived;
    
    
    int moveInt;
    t_move move;
    
    printArena();
    printArenax(arena);
    while (Gamerunning){
        s->dir = dirSnake(s, arena);
        updateSnakePosition(s);
        
        if (y==0){
            
            y=1;
            
            moveInt = dirSnake(s,arena);
            printf("moveInt : %d\n",moveInt);
            move = (t_move)moveInt;
    
            moveSent=sendMove(move);
            
            if (moveSent == LOSING_MOVE) {
                printf("You lost :(\n");
                Gamerunning=0;
            }
            else printArena();
           
        }
        else if (y==1){
            y=0;
            moveReceived=getMove(&x);
            if (moveReceived == LOSING_MOVE){
                printf("You won!! :)\n");
                 Gamerunning=0;
            }
            else printArena();
            
        }
    }
    freeArena(arena);
    freeSnake(s);
    closeConnection();
	return 0;
}