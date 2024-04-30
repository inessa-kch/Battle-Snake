
#include <stdio.h>
#include "clientAPI.h"
#include "snakeAPI.h"



int main(){
    
	connectToServer("localhost",1234,"bli");
    printf("bliblou\n");
    char gameName[50];
    int sizeX;
    int sizeY;
    int nbWalls;
    int walls[2000];
    int Gamerunning = 1;
    t_move x;
    t_return_code moveSent;
    t_return_code moveReceived;
    
    waitForSnakeGame("TRAINING SUPER_PLAYER",gameName,&sizeX,&sizeY,&nbWalls);
    
    int moveInt;
    t_move move;
    
    int a=getSnakeArena(walls);
    //int b=getSnakeArena(walls);
    
    while (Gamerunning){
        
        if (a==0){
            
            a=1;
            printf("Enter a move (0 for NORTH, 1 for EAST, 2 for SOUTH, 3 for WEST): \n");
            scanf("%d", &moveInt);
            printf("\n");
            move = (t_move)moveInt;
            moveSent=sendMove(move);
            
            if (moveSent == LOSING_MOVE) {
                printf("You lost :(\n");
                Gamerunning=0;
            }
            else printArena();
           
        }
        else if (a==1){
            a=0;
            moveReceived=getMove(&x);
            if (moveReceived == LOSING_MOVE){
                printf("You won!! :)\n");
                 Gamerunning=0;
            }
            else printArena();
            
        }
    }
	return 0;
}