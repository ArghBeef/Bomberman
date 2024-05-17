#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "Sprites.h"
#include "Block.h"
#include "Explosion.h"
#include "Game.h"
#include "Bonus.h"

#define TILENUM_H 11 //Height
#define TILENUM_W 22 //Width

#define TILESTART_X 70 //Where does the level should be started in X
#define TILESTART_Y 20 //the same but for Y

Block blocks[TILENUM_H][TILENUM_W];


//Check for explodes with blocks
bool block_checkexplode(Block* blocks, Explosion explosions[EXPL_NUM]) {
    for (int i = 0; i < EXPL_NUM; i++) {
        if (explosions[i].isActive) {
                if (game_Collide(blocks->x, blocks->y, blocks->x, blocks->y, explosions[i].x, explosions[i].y, explosions[i].x + TILEBLOCK_SPRITE_SIZE, explosions[i].y + TILEBLOCK_SPRITE_SIZE))
                    return true; //If it collides with explosion

        }
    }

    return false;
}

//Update and Check for Explosions and do actions based on that
void map_Update() {
    for (int H = 0; H < TILENUM_H; H++) {
        for (int W = 0; W < TILENUM_W; W++) {
            if (block_checkexplode(&blocks[H][W], expl)) {
                if (blocks[H][W].destructable) {
                    blocks[H][W].type = 0;
                    blocks[H][W].collide = false;
                    blocks[H][W].destructable = false;
                    bonus_Create(blocks[H][W].x, blocks[H][W].y);
                }
            }
        }
    }
}

//Load map from text file
int** map_Load() {
    int** maptab = calloc(TILENUM_H, sizeof(int*)); // Allocate memory for an array of int pointers

    if (maptab == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }

    for (int i = 0; i < TILENUM_H; i++) {
        maptab[i] = calloc(TILENUM_W, sizeof(int)); // Allocate memory for each row of the 2D array
        if (maptab[i] == NULL) {
            printf("Memory allocation failed!");
            exit(1);
        }
    }

    FILE* map = fopen("maps/map.txt", "r");
    if (map == NULL) {
        printf("FAIL: Couldn't load map!");
        exit(1);
    }

    for (int i = 0; i < TILENUM_H; i++) {
        for (int j = 0; j < TILENUM_W; j++) {
            if (fscanf_s(map, "%d", &maptab[i][j]) == EOF) {
                printf("Error reading map file!");
                exit(1);
            }
        }
    }

    fclose(map);

    return maptab;
}


//Initialize = Convert 2D array data to struct Block data
void map_Initialize(int** maptab) {
    int xLast = TILESTART_X;
    int yLast = TILESTART_Y;
    for (int H = 0; H < TILENUM_H; H++) {
        for (int W = 0; W < TILENUM_W; W++) {
            blocks[H][W].x = xLast;
            blocks[H][W].y = yLast;
            switch (maptab[H][W]) {
            case 0:
                blocks[H][W].type = 0;
                blocks[H][W].collide = false;
                blocks[H][W].destructable = false;
                break;
            case 1:
                blocks[H][W].type = 0;
                blocks[H][W].collide = false;
                blocks[H][W].destructable = false;
                break;
            case 2:
                blocks[H][W].type = 2;
                blocks[H][W].collide = true;
                blocks[H][W].destructable = true;
                break;
            case 3:
                blocks[H][W].type = 3;
                blocks[H][W].collide = true;
                blocks[H][W].destructable = false;
                break;
            }
            xLast += TILEBLOCK_SPRITE_SIZE;
        }
        yLast += TILEBLOCK_SPRITE_SIZE;
        xLast = TILESTART_X;
    }

    free(maptab);
}

//Draw Map
void map_Draw(Sprites* spriteS, Block blocks[TILENUM_H][TILENUM_W]) {
    for (int H = 0; H < TILENUM_H; H++) {
        for (int W = 0; W < TILENUM_W; W++) {

            switch (blocks[H][W].type) {

            case 0:
                al_draw_bitmap(spriteS->GRASS, blocks[H][W].x, blocks[H][W].y, 0);
                break;

            case 1:
                al_draw_bitmap(spriteS->NIKITA, blocks[H][W].x, blocks[H][W].y, 0);
                break;

            case 2:
                al_draw_bitmap(spriteS->DESTRUCTABLE, blocks[H][W].x, blocks[H][W].y, 0);
                break;

            case 3:
                al_draw_bitmap(spriteS->BRICK, blocks[H][W].x, blocks[H][W].y, 0);
                break;
            }
        }
    }

}

#endif