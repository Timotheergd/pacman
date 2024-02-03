#include "board.h"

/*
Return the num-th level stored in the file of levels
*/
void read_level(char filename[50], int level_number, char (*level_content)[LEVEL_SIZE]){
	FILE* level_file = fopen(filename, "r");
	if(level_file != NULL){
		fseek(level_file, level_number*(LEVEL_SIZE+1), SEEK_SET); // +1 to take into account the '\n' at the end of the line
		fscanf(level_file, "%s", level_content);
        fclose(level_file);
	}   
}

Board initBoard(){
	Board b = {
        .player=initPlayer(initCoords(-1,-1)), 
        .wall_list=NULL,
        .ghost_list = NULL,
        .warp_list = NULL,
        .gum_list = NULL,
        .bigGum_list = NULL,
        .nbWall = 0,
        .nbGhost = 0,
        .nbWarp = 0,
        .nbGum = 0,
        .nbBigGum = 0
    };
	return b;
}

void printBoardContent(Board *board){
    printf("Board content :\n");

    printf("walls\n");
    for(int i=0;i<board->nbWall;i++){
        print_Coords((board->wall_list[i]).coords);
    }

    printf("player\n");
    print_Coords(board->player.coords);
    
    printf("ghosts\n");
    for(int i=0;i<board->nbGhost;i++){
        print_Coords((board->ghost_list[i]).coords);
    }
    
    printf("gum_list\n");
    for(int i=0;i<board->nbGum;i++){
        print_Coords((board->gum_list[i]).coords);
    }
    
    printf("big gum\n");
    for(int i=0;i<board->nbBigGum;i++){
        print_Coords((board->bigGum_list[i]).coords);
    }
}

/*
Set the position of the player
Fill arrays of walls, ghosts, ... with the correct position
*/
// Board init_board(char (*level_content)[LEVEL_SIZE], Player *player, Wall *wall_list, Ghost *ghost_list, Warp *warp_list, Gum *gum_list, BigGum *bigGum_list){
Board loadBoard(char (*level_content)[LEVEL_SIZE], Board *board){
    /* Les objets sont stockés de la manière suivante :
    nombre	| objet
    --------+---------
    0	    | vide
    1	    | mur
    2	    | pacman
    3       | fantome
    4	    | gum
    5	    | big Gum
    6       | warp
    */
    int i,j = 0;
    for(int k=0; k<strlen(*level_content);k++){
        i=k/BOARD_WIDTH; // height
        j=k%BOARD_WIDTH; // width
        switch((*level_content)[k]){
            case WALL:
                board->nbWall+=1;
                board->wall_list=(Wall*)realloc(board->wall_list, board->nbWall*sizeof(Wall));
                (board->wall_list)[board->nbWall-1]=initWall(initCoords(i,j));               
                break;
            case PLAYER:
                board->player=initPlayer(initCoords(i,j));               
                break;
            case GHOST:
                board->nbGhost+=1;
                board->ghost_list=(Ghost*)realloc(board->ghost_list, board->nbGhost*sizeof(Ghost));
                (board->ghost_list)[board->nbGhost-1]=initGhost(initCoords(i,j));               
                break;
            case GUM:
                board->nbGum+=1;
                board->gum_list=(Gum*)realloc(board->gum_list, board->nbGum*sizeof(Gum));
                (board->gum_list)[board->nbGum-1]=initGum(initCoords(i,j));               
                break;
            case BIGGUM:
                board->nbBigGum+=1;
                board->bigGum_list=(BigGum*)realloc(board->bigGum_list, board->nbBigGum*sizeof(BigGum));
                (board->bigGum_list)[board->nbBigGum-1]=initBigGum(initCoords(i,j));               
                break;
            // case WARP: // Waiting a solution to store it....
            //     board->nbWarp+=1;
            //     board->warp_list=(Warp*)realloc(board->warp_list, board->nbWarp*sizeof(Warp));
            //     (board->warp_list)[board->nbWarp-1]=initWarp(initCoords(i,j), ini);               
            //     break;
            default:
                break;
        }
    }
}