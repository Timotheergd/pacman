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
        .gate_list = NULL,
        .ghostRespawn_list = NULL,
        .nbWall = 0,
        .nbGhost = 0,
        .nbWarp = 0,
        .nbGum = 0,
        .nbBigGum = 0,
        .nbGate = 0,
        .nbGhostRespawn = 0
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

    printf("ghosts respawn\n");
    for(int i=0;i<board->nbGhostRespawn;i++){
        print_Coords((board->ghostRespawn_list[i]).coords);
    }
    
    printf("gum_list\n");
    for(int i=0;i<board->nbGum;i++){
        print_Coords((board->gum_list[i]).coords);
    }
    
    printf("big gum\n");
    for(int i=0;i<board->nbBigGum;i++){
        print_Coords((board->bigGum_list[i]).coords);
    }

    printf("gate\n");
    for(int i=0;i<board->nbGate;i++){
        print_Coords((board->gate_list[i]).coords);
    }
}

/*
Set the position of the player
Fill arrays of walls, ghosts, ... with the correct position
*/
// Board init_board(char (*level_content)[LEVEL_SIZE], Player *player, Wall *wall_list, Ghost *ghost_list, Warp *warp_list, Gum *gum_list, BigGum *bigGum_list){
Board loadBoard(char (*level_content)[LEVEL_SIZE], Board *board, LoadType load_type){
    /* Les objets sont stockés de la manière suivante :
    nombre	| objet
    --------+---------
    0	    | vide
    1	    | mur
    2	    | pacman
    3       | fantome
    4	    | gum
    5	    | big Gum
    6       | gate
    7       | ghost respawn point
    */

    // Reset the board
    
    board->ghost_list = NULL;
    board->nbGhost = 0;
    // board->warp_list = NULL;
    // board->nbWarp = 0;
    
    if(load_type==NEW || load_type==CHANGE_LEVEL){
        board->wall_list=NULL;
        board->gum_list = NULL;
        board->bigGum_list = NULL;
        board->gate_list = NULL;
        board->ghostRespawn_list = NULL;
        board->nbWall = 0;
        board->nbGum = 0;
        board->nbBigGum = 0;
        board->nbGate = 0;
        board->nbGhostRespawn = 0;
    }

    int i,j = 0;
    for(int k=0; k<strlen(*level_content);k++){
        j=k/BOARD_WIDTH; // height
        i=k%BOARD_WIDTH; // width
        switch((*level_content)[k]){
            case WALL:
                if(load_type==NEW || load_type==CHANGE_LEVEL){
                    board->nbWall+=1;
                    board->wall_list=(Wall*)realloc(board->wall_list, board->nbWall*sizeof(Wall));
                    (board->wall_list)[board->nbWall-1]=initWall(initCoords(i*TILE_WIDTH,j*TILE_HEIGHT+WIN_SCORE_HEIGHT));
                }            
                break;
            case PLAYER:
                if(load_type==NEW){
                    board->player=initPlayer(initCoords(i*TILE_WIDTH,j*TILE_HEIGHT+WIN_SCORE_HEIGHT));
                }
                else{
                    (board->player).direction=IDLE;
                    (board->player).coords=initCoords(i*TILE_WIDTH,j*TILE_HEIGHT+WIN_SCORE_HEIGHT);                    
                }   
                break;
            case GHOST:
                board->nbGhost+=1;
                board->ghost_list=(Ghost*)realloc(board->ghost_list, board->nbGhost*sizeof(Ghost));
                (board->ghost_list)[board->nbGhost-1]=initGhost(initCoords(i*TILE_WIDTH,j*TILE_HEIGHT+WIN_SCORE_HEIGHT));               
                break;
            case GHOST_RESPAWN:
                if(load_type==NEW || load_type==CHANGE_LEVEL){
                    // load the respawn point
                    board->nbGhostRespawn+=1;
                    board->ghostRespawn_list=(GhostRespawn*)realloc(board->ghostRespawn_list, board->nbGhostRespawn*sizeof(GhostRespawn));
                    (board->ghostRespawn_list)[board->nbGhostRespawn-1]=initGhostRespawn(initCoords(i*TILE_WIDTH,j*TILE_HEIGHT+WIN_SCORE_HEIGHT)); 
                }
                if(load_type==NEW || load_type==CHANGE_LEVEL || load_type==RELOAD){
                    // load a ghost on it
                    board->nbGhost+=1;
                    board->ghost_list=(Ghost*)realloc(board->ghost_list, board->nbGhost*sizeof(Ghost));
                    (board->ghost_list)[board->nbGhost-1]=initGhost(initCoords(i*TILE_WIDTH,j*TILE_HEIGHT+WIN_SCORE_HEIGHT));    
                }    
                break;
            case GUM:
                if(load_type==NEW || load_type==CHANGE_LEVEL){
                    board->nbGum+=1;
                    board->gum_list=(Gum*)realloc(board->gum_list, board->nbGum*sizeof(Gum));
                    (board->gum_list)[board->nbGum-1]=initGum(initCoords(i*TILE_WIDTH+GUM_OFFSET,j*TILE_HEIGHT+WIN_SCORE_HEIGHT+GUM_OFFSET));
                }
                break;
            case BIGGUM:
                if(load_type==NEW || load_type==CHANGE_LEVEL){
                    board->nbBigGum+=1;
                    board->bigGum_list=(BigGum*)realloc(board->bigGum_list, board->nbBigGum*sizeof(BigGum));
                    (board->bigGum_list)[board->nbBigGum-1]=initBigGum(initCoords(i*TILE_WIDTH+BIGGUM_OFFSET,j*TILE_HEIGHT+WIN_SCORE_HEIGHT+BIGGUM_OFFSET)); 
                }              
                break;
            case GATE:
                if(load_type==NEW || load_type==CHANGE_LEVEL){
                    board->nbGate+=1;
                    board->gate_list=(Gate*)realloc(board->gate_list, board->nbGate*sizeof(Gate));
                    (board->gate_list)[board->nbGate-1]=initGate(initCoords(i*TILE_WIDTH,j*TILE_HEIGHT+WIN_SCORE_HEIGHT)); 
                }              
                break;
            // case WARP: // Waiting a solution to store it....
            //     board->nbWarp+=1;
            //     board->warp_list=(Warp*)realloc(board->warp_list, board->nbWarp*sizeof(Warp));
            //     (board->warp_list)[board->nbWarp-1]=initWarp(initCoords(i*TILE_WIDTH,j*TILE_HEIGHT+WIN_SCORE_HEIGHT), ini);               
            //     break;
            default:
                break;
        }
    }
    if(board->nbGhostRespawn>0){
        for(int k=0; k<board->nbGhost; k++){
            // Set respawn point to the first for now
            // TODO : Set respawn point to the closest 
            ((board->ghost_list)[k]).respawnPoint=((board->ghostRespawn_list)[0]).coords;
        }
    }
}

void renderWalls(Board *board, SDL_Texture *tex, SDL_Renderer *rend){
    for(int i=0; i<board->nbWall;i++){
        renderTexture(tex, rend, (board->wall_list)[i].coords.x, (board->wall_list)[i].coords.y, TILE_WIDTH+1, TILE_HEIGHT);
    }
}

bool wallCollision(Coords coords, Board *board){
    for(int i=0; i<board->nbWall;i++){
        if(collision(coords, TILE_HEIGHT, TILE_WIDTH, (board->wall_list)[i].coords, TILE_HEIGHT, TILE_WIDTH)){
            return true;
        }
    }
    return false;
}

bool gateCollision(Coords coords, Board *board){
    for(int i=0; i<board->nbGate;i++){
        if(collision(coords, TILE_HEIGHT, TILE_WIDTH, (board->gate_list)[i].coords, TILE_HEIGHT, TILE_WIDTH)){
            return true;
        }
    }
    return false;
}

int ghostCollision(Coords coords, Board *board){
    for(int i=0; i<board->nbGhost;i++){
        if(collision(coords, TILE_HEIGHT, TILE_WIDTH, (board->ghost_list)[i].coords, TILE_HEIGHT, TILE_WIDTH)){
            return i;
        }
    }
    return -1;
}

// Return true if the player as moved
bool movePlayer(Board *board, Direction direction){
    /* Algo random direction
    key direction posible ?
        yes -> change direction, move and exit
        no  -> continue
    player direction posible ?
        yes -> move and exit
        no  -> IDLE and exit
    */

    /*
    TODO : implement :
    -key direction posible ?
        yes -> change direction, move and exit
        no  -> continue
    player direction posible ?
        yes -> 
            intersection near ?
                -> align and exit
                -> move and exit
        no  -> IDLE and exit
    */

    if(direction!=(board->player).direction){
        int align_speed=(board->player).speed; // speed needed to be align to move to an other direction 
        do{
            Coords align_coords_keyboard_direction = incrCoords((board->player).coords, (board->player).direction, align_speed);
            Coords next_coords_keyboard_direction = incrCoords(align_coords_keyboard_direction, direction, (board->player).speed);
            if(!wallCollision(next_coords_keyboard_direction, board) && !gateCollision(next_coords_keyboard_direction, board)){
                (board->player).direction=direction;
                (board->player).coords=next_coords_keyboard_direction;
                return true;
            }
            align_speed--;
        }while(align_speed>1);
    }
    int speed = (board->player).speed;
    do{
        Coords next_coords_player_direction = incrCoords((board->player).coords, (board->player).direction, speed);
        if(!wallCollision(next_coords_player_direction, board) && !gateCollision(next_coords_player_direction, board)){
            (board->player).coords=next_coords_player_direction;
            return true;
        }
        speed--; // Ajust speed until the player touch perfectly the wall
    }while(speed>1);
    (board->player).direction=IDLE;
    // printf("collision player !");
    return false;


}

void renderGhosts(Board *board, SDL_Texture *tex, SDL_Renderer *rend){
    for(int i=0; i<board->nbGhost;i++){
        renderTexture(tex, rend, (board->ghost_list)[i].coords.x, (board->ghost_list)[i].coords.y, TILE_WIDTH, TILE_HEIGHT);
    }
}

bool moveAGhost(Board *board, int i){
    /*
    i = i-th ghost of the board list
    */
    int align_speed=((board->ghost_list)[i]).speed; // speed needed to be align to move to an other direction 
                
    Direction relRight, relLeft;
    relativeRightLeftDir(((board->ghost_list)[i]).direction, &relRight, &relLeft);
    Direction relativeRL[2] = {relRight, relLeft};
    do{
        for(int j=0;j<2;j++){ // relative right and left check
            Coords align_coords = incrCoords(((board->ghost_list)[i]).coords, ((board->ghost_list)[i]).direction, align_speed);
            Coords next_coords_keyboard_direction = incrCoords(align_coords, relativeRL[j], ((board->ghost_list)[i]).speed);
            if(!wallCollision(next_coords_keyboard_direction, board)){
                // move to the intersection
                ((board->ghost_list)[i]).coords=align_coords;
                return true;
            }
        }
        align_speed--;
    }while(align_speed>1);

    // if intersection not in speed range, move
    int speed = ((board->ghost_list)[i]).speed;
    do{
        Coords next_coords_ghost_direction = incrCoords(((board->ghost_list)[i]).coords, ((board->ghost_list)[i]).direction, speed);
        if(!wallCollision(next_coords_ghost_direction, board)){
            ((board->ghost_list)[i]).coords=next_coords_ghost_direction;
            return true;
        }
        speed--; // Ajust speed until the ghost touch perfectly the wall
    }while(speed>1);
    
    return false;
}

void moveGhosts(Board *board){
    srand(time(0));
    for(int i=0; i<board->nbGhost;i++){
        /*
        IDLE ? => random direction
        On intersect ? (check possibilities other than back >=2)
            - yes : change direction, move, exit
            - no : continue

            same direction posible ?
                - yes :
                    intersect in range ?
                        - yes : align(move) and exit
                        - no : move, exit
                - no : 
                    back direction possible ?
                        - yes : move, exit
                        - no : IDLE, ERROR
        */

        // Get a random direction if IDLE
        if(((board->ghost_list)[i]).direction==IDLE){
            ((board->ghost_list)[i]).direction=rand()%4;
        }

        // Check if the ghost is on an intersection
        // Check available direction
        Direction *available_direction = NULL;
        int nb_available_direction = 0;
        bool straight_available=false;

        // for each derection (0 to 3), check if can move : yes -> add it to the list of available directions
        for(int j=0; j<4;j++){
            if(j!=opositeDirection(((board->ghost_list)[i]).direction)){ // Do not consider going back for now
                if(!wallCollision(incrCoords(((board->ghost_list)[i]).coords, j, ((board->ghost_list)[i]).speed), board)){
                    nb_available_direction++;
                    available_direction=(Direction*)realloc(available_direction, nb_available_direction*sizeof(Direction));
                    (available_direction)[nb_available_direction-1]=j;
                    if(j==((board->ghost_list)[i]).direction){
                        straight_available=true;
                    }
                }
            }
        }
        
        if(nb_available_direction>0){ // On intersect ?
            // Get a ramdom direction from the list
            ((board->ghost_list)[i]).direction=(available_direction)[rand()%nb_available_direction];
            //move
            ((board->ghost_list)[i]).coords=incrCoords(((board->ghost_list)[i]).coords, ((board->ghost_list)[i]).direction, ((board->ghost_list)[i]).speed);
            continue;
        }
        else{
            if(straight_available){
                moveAGhost(board, i);
                continue;
            } // end if(straight_available)
            else{
                // Try to go back
                ((board->ghost_list)[i]).direction = opositeDirection(((board->ghost_list)[i]).direction);

                if(!moveAGhost(board, i)){ // if going back is not possible 
                    ((board->ghost_list)[i]).direction = IDLE;
                }
                continue;
            }
        }
    }     
}

void renderPlayerHealth(Board *board, SDL_Texture *tex, SDL_Renderer *rend){
    /*
    Render the texture under the board for each health of the player
    */
    for(int i=0;i<(board->player).health;i++){
        renderTexture(tex, rend, i*(TILE_WIDTH+OFFSET), WIN_SCORE_HEIGHT+WIN_BOARD_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
    }

}

void renderGum(Board *board, SDL_Texture *tex, SDL_Renderer *rend){
    for(int i=0; i<board->nbGum;i++){
        renderTexture(tex, rend, (board->gum_list)[i].coords.x, (board->gum_list)[i].coords.y, GUM_SIZE, GUM_SIZE);
    }
}

bool eatGum(Board *board){
    for(int i=0; i<board->nbGum;i++){
        if(collision((board->player).coords, TILE_HEIGHT, TILE_WIDTH, (board->gum_list)[i].coords, GUM_SIZE, GUM_SIZE)){
            // delete the gum
            for(int j=i; j < board->nbGum; j++){
                (board->gum_list)[j]=(board->gum_list)[j+1];
            }
            board->nbGum--;
            (board->player).points+=GUM_POINTS;
            // no realloc because I don't care :)
        }
    }
}

void renderPoints(Board *board, TTF_Font* font, SDL_Color color, SDL_Renderer *rend){
    char buffer[50];
    sprintf(&buffer, "Points : %d\n", (board->player).points);
    SDL_Texture* points_tex = loadText(buffer, font, color, rend);
    renderTexture(points_tex, rend, OFFSET, OFFSET, WIN_WIDTH/3, WIN_SCORE_HEIGHT/2);
}

void renderBigGum(Board *board, SDL_Texture *tex, SDL_Renderer *rend){
    for(int i=0; i<board->nbBigGum;i++){
        renderTexture(tex, rend, (board->bigGum_list)[i].coords.x, (board->bigGum_list)[i].coords.y, BIGGUM_SIZE, BIGGUM_SIZE);
    }
}

bool eatBigGum(Board *board, time_t *super_mode){
    for(int i=0; i<board->nbBigGum;i++){
        if(collision((board->player).coords, TILE_HEIGHT, TILE_WIDTH, (board->bigGum_list)[i].coords, BIGGUM_SIZE, BIGGUM_SIZE)){
            // delete the gum
            for(int j=i; j < board->nbGum; j++){
                (board->bigGum_list)[j]=(board->bigGum_list)[j+1];
            }
            board->nbBigGum--;
            // no realloc because I don't care :)
            *super_mode=time(NULL);
        }
    }
}

void renderGate(Board *board, SDL_Texture *tex, SDL_Renderer *rend){
    for(int i=0; i<board->nbGate;i++){
        renderTexture(tex, rend, (board->gate_list)[i].coords.x, (board->gate_list)[i].coords.y, TILE_WIDTH, TILE_HEIGHT);
    }
}