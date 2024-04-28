
#include <stdio.h>
#include "clientAPI.h"
#include "snakeAPI.h"



int main(){
    printf("bliblou\n");
	connectToServer("localhost",1234,"bla");
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
    
    int a=getSnakeArena(walls);
    //int b=getSnakeArena(walls);
    while (Gamerunning){
        if (a==0){
            a=1;
            moveSent=sendMove(NORTH);
            
            if (moveSent == LOSING_MOVE) Gamerunning=0;
            else printArena();
           
        }
        else if (a==1){
            a=0;
            moveReceived=getMove(&x);
            if (moveReceived == LOSING_MOVE) Gamerunning=0;
            else printArena();
            
        }
    }
	return 0;
}