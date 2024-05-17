#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "Sprites.h"

#define EXPL_NUM 128
#define EXPL_TIME 30

typedef struct  {
	int x, y;
	bool isActive;
    int time;
}Explosion;

Explosion expl[EXPL_NUM];

int radius = 0;

void explosion_ClearAll() {
	for (int i = 0; i < EXPL_NUM; i++)
		expl[i].isActive = false;
}

//Method to add bomb whenever the bomb was placed
void explosion_Setup(int index, int x, int y) {
    expl[index].x = x - TILEBLOCK_SPRITE_SIZE;
    expl[index].y = y - TILEBLOCK_SPRITE_SIZE;
    expl[index].time = 0;
    expl[index].isActive = true;
}

void explosion_Add(int x, int y) {
    for (int i = 0; i < EXPL_NUM; i++) {
        if (!expl[i].isActive) {
            if (radius == 0) {
                for (int j = 0; j < 3; j++) {
                    explosion_Setup(i + j, x + TILEBLOCK_SPRITE_SIZE * j, y + TILEBLOCK_SPRITE_SIZE);
                }
                i += 3;
                for (int j = 0; j < 3; j++) {
                    explosion_Setup(i + j, x + TILEBLOCK_SPRITE_SIZE * j, y + TILEBLOCK_SPRITE_SIZE * 2);
                }
                i += 3;
                for (int j = 0; j < 3; j++) {
                    explosion_Setup(i + j, x + TILEBLOCK_SPRITE_SIZE * j, y);
                }
            }
            else {
                for (int j = 0; j < 5; j++) {
                    explosion_Setup(i + j, x + TILEBLOCK_SPRITE_SIZE * j, y + TILEBLOCK_SPRITE_SIZE);
                }
                i += 5;
                for (int j = 0; j < 5; j++) {
                    explosion_Setup(i + j, x + TILEBLOCK_SPRITE_SIZE * j, y + TILEBLOCK_SPRITE_SIZE * 2);
                }
                i += 5;
                for (int j = 0; j < 5; j++) {
                    explosion_Setup(i + j, x + TILEBLOCK_SPRITE_SIZE * j, y);
                }
                radius = 0;
            }
            return;
        }
    }
}

// Draw explosions
void explosion_Draw() {
    for (int i = 0; i < EXPL_NUM; i++) {
        if (expl[i].isActive) {
            al_draw_bitmap(sprites.EXPLOSIONE, expl[i].x, expl[i].y, 0);
        }
    }
}

// Update explosions
void explosion_Update() {
    for (int i = 0; i < EXPL_NUM; i++) {
        if (expl[i].isActive) {
            expl[i].time++;
            if (expl[i].time >= EXPL_TIME) {
                expl[i].isActive = false;
            }
        }
    }
}

#endif