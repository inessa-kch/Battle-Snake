#include <stdio.h>
#include <stdlib.h>
#include "snakeAPI.h"
#include "arena.h"
#include "snake.h"

#define INT_MAX 50
//le ​joueur 0 (qui joue le premier) commence à la position (2, H/2) et le ​joueur 1​ à la position ​(L-3, H/2)​.

Snake* initSnake(int x, int y) {
    Snake* s = (Snake*)malloc(sizeof(Snake));
    s->x = x;
    s->y = y;
    s->suivant = NULL;
    return s;
}


void freeSnake(Snake* snake){
    Snake* tmp = snake;
    Snake* suiv;

    while (tmp != NULL) {
        suiv = tmp->suivant;
        free(tmp);
        tmp = suiv;
    }
}



t_move sendMySnakeMove() {
    int moveInt;
    t_return_code moveSent;
    scanf("%d", &moveInt);
    t_move move = (t_move)moveInt;
    if (move == NORTH) {
        moveSent=sendMove(NORTH);
        return NORTH;
    } else if (move == EAST) {
        moveSent=sendMove(EAST);
        return EAST;
    } else if (move == SOUTH) {
        moveSent=sendMove(SOUTH);
        return SOUTH;
    } else if (move == WEST) {
        moveSent=sendMove(WEST);
        return WEST;
    }
    return -1; 
}



void moveSnake(Snake** head, t_move dir, int grow, Arena* arena) {
 
    int newX = (*head)->x;
    int newY = (*head)->y;


    switch (dir) {
        case NORTH: // Up
            newY--;
            break;
        case EAST: // Right
            newX++;
            break;
        case SOUTH: // Down
            newY++;
            break;
        case WEST: // Left
            newX--;
            break;
        default:
            return;
    }

 
    Snake* newHead = (Snake*)malloc(sizeof(Snake));
    newHead->x = newX;
    newHead->y = newY;
    newHead->suivant = *head;
    *head = newHead;

    arena->cells[newY][newX].snake=1;

    if (!grow) {
        Snake* current = *head;
        Snake* prev = NULL;
        while (current->suivant != NULL) {
            prev = current;
            current = current->suivant;
        }
        arena->cells[current->y][current->x].snake=0;
        free(current);
        if (prev != NULL)
            prev->suivant = NULL; 
    }
}



//inspired by a code i did last year on bfs

void markAccessibleCells(Arena* arena,Snake* s,int** distance){
    for (int i = 0; i < arena->sizeY; i++) {
        for (int j = 0; j < arena->sizeX; j++) {
            distance[i][j] = -1; // -1 indicates unvisited cells
        }
    }
    Position* queue=(Position*)malloc(arena->sizeX*arena->sizeY*sizeof(Position));
    int front=0;
    int rear=0;
    Position p = {s->x,s->y};
    queue[rear++]=p;
    distance[p.y][p.x]=0;

    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};

    while (front < rear){
        Position current = queue[front++];
        int curDist= distance[current.y][current.x];

        for (int i = 0; i < 4; i++){
            int nx=current.x+dx[i];
            int ny=current.y+dy[i];

            if (nx>=0 && nx<arena->sizeX && ny>=0 && ny<arena->sizeY){
                if (distance[ny][nx]==-1 && !arena->cells[ny][nx].snake &&
                    !((i==0 && arena->cells[current.y][current.x].wallTop) ||
                    (i==1 && arena->cells[current.y][current.x].wallRight) ||
                    (i==2 && arena->cells[current.y][current.x].wallBottom) ||
                    (i==3 && arena->cells[current.y][current.x].wallLeft))){
                        distance[ny][nx]=curDist+1;
                        queue[rear++]=(Position){nx,ny};
                }
            }
        }
    }
    for (int i = 0; i < arena->sizeY; i++) {
        for (int j = 0; j < arena->sizeX; j++) {
            printf("%d ", distance[i][j]);
        }
        printf("\n");
    }
    free(queue);    

}


//strat 1 : on choisit d'aller vers la case la plus eloignée
t_move decideNextMove(Arena* arena, Snake* s, int** distance){
    int bestDist = -1;
    t_move bestMove = NORTH;

    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};

    for (int i=0; i<4;i++){
        int nx=s->x+dx[i];
        int ny=s->y+dy[i];

        if (nx >= 0 && nx < arena->sizeX && ny >= 0 && ny < arena->sizeY &&
                distance[ny][nx] != -1 &&
                !arena->cells[ny][nx].snake &&
                !((i == 0 && arena->cells[s->y][s->x].wallTop) ||
                (i == 1 && arena->cells[s->y][s->x].wallRight) ||
                (i == 2 && arena->cells[s->y][s->x].wallBottom) ||
                (i == 3 && arena->cells[s->y][s->x].wallLeft))) {

                    if (distance[ny][nx]>bestDist){
                        bestDist=distance[ny][nx];
                        bestMove=(t_move)i;
                    }
        }
    }
    printf("bestDist: %d\n", bestDist);
    return bestMove;
}

//strat 2 : on choisit d'aller vers la case la plus eloignée qui est safe
t_move decideSafeMove(Arena* arena, Snake* s, int** distance) {
    int minDist = INT_MAX; 
    t_move safeMove = NORTH; 

    
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};

    
    for (int i = 0; i < 4; i++) {
        
        int nx = s->x + dx[i];
        int ny = s->y + dy[i];

        
        if (nx >= 0 && nx < arena->sizeX && ny >= 0 && ny < arena->sizeY) {
            
            if (distance[ny][nx] != -1 && distance[ny][nx] < minDist &&
                !arena->cells[ny][nx].snake &&
                !((i == 0 && arena->cells[s->y][s->x].wallTop) ||
                  (i == 1 && arena->cells[s->y][s->x].wallRight) ||
                  (i == 2 && arena->cells[s->y][s->x].wallBottom) ||
                  (i == 3 && arena->cells[s->y][s->x].wallLeft))) {
                
                minDist = distance[ny][nx];
                safeMove = (t_move)i;
            }
        }
    }

    return safeMove; 
}


