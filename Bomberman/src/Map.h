#ifndef MAP
#define MAP

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "Sprites.h"
#include "Block.h"

#define TILENUM_H 11 //Height
#define TILENUM_W 22 //Width

#define TILESTART_X 70 //Where does the level should be started in X
#define TILESTART_Y 20 //the same but for Y

//HUGE REMARK: Of course i could use enums to sort things like grass, brick and etc to make it more readable and so but im lazy and maybe somewhere, when it will be time 
//to make last fixes things for semester sdacza or how is that thing called, i will maybe re-do the system asdadadadagjgajnajajsjadsjads

//Reading a map from a text file and saving it in a parameter 2D array
//But I actually could do that using one dimensional array ;d
//whoever it looks prettier in 2D so
void map_Load(int maptab[TILENUM_H][TILENUM_W]) {

    FILE* map = fopen("maps/map.txt", "r");

    if (map == NULL) {
        printf("FAIL: Couldnt load map!");
        exit(1);
    }

    int H_count = 0;
    while (!feof(map)) {

        for (int W = 0; W < TILENUM_W; W++) {
            if (fscanf_s(map, "%d", &maptab[H_count][W]) == EOF)
                break;
        }

        H_count++;

        if (H_count == TILENUM_H)
            break;
    }

    fclose(map);
}

//  
void map_Draw(int maptab[TILENUM_H][TILENUM_W], Sprites* spriteS, Block blocks[TILENUM_H][TILENUM_W]) { //Actually, this method used in function is not practical for later uses but I will change it later
    int xLast, yLast;
    xLast = TILESTART_X;
    yLast = TILESTART_Y;
    for (int H = 0; H < TILENUM_H; H++) {
        for (int W = 0; W < TILENUM_W; W++) {

            switch (maptab[H][W]) {

            case 0:
                blocks[H][W].collide = false;
                //blocks[H][W].destructable = false;
                blocks[H][W].x = xLast;
                blocks[H][W].y = yLast;
                al_draw_bitmap(spriteS->GRASS, xLast, yLast, 0);
                break;

            case 1:
                //There was a second version of grass which i screwed and instead i put my neighbout Nikita in spritesheet and that one method which loads all sprites
                //and maybe I will put bonus (powerup sprite) here
                break;

            case 2:
                blocks[H][W].collide = true;
                //blocks[H][W].destructable = true;
                blocks[H][W].x = xLast;
                blocks[H][W].y = yLast;
                al_draw_bitmap(spriteS->DESTRUCTABLE, xLast, yLast, 0);
                break;

            case 3:
                blocks[H][W].collide = true;
                //blocks[H][W].destructable = false;
                blocks[H][W].x = xLast;
                blocks[H][W].y = yLast;
                al_draw_bitmap(spriteS->BRICK, xLast, yLast,0);
                break;
            }
            xLast += TILEBLOCK_SPRITE_SIZE;
        }
       yLast += TILEBLOCK_SPRITE_SIZE;
       xLast = TILESTART_X;
    }

}

#endif