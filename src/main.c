
#include <stdio.h>
#include "clientAPI.h"
#include "snakeAPI.h"
#include "arena.h"


int main(){
    
	connectToServer("localhost",1234,"iness");
    int y;
    Arena* arena = createArena("TRAINING SUPER_PLAYER",&y);
    int Gamerunning = 1;
    t_move x;
    t_return_code moveSent;
    t_return_code moveReceived;
    
    
    int moveInt;
    t_move move;
    
    printArena();
    printArenax(arena);
    while (Gamerunning){
        
        if (y==0){
            
            y=1;
            printf("Enter a move (0 for UP, 1 for RIGHT, 2 for DOWN, 3 for LEFT): \n");
            scanf("%d", &moveInt);
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
	return 0;
}