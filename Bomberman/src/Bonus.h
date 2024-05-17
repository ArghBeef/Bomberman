#ifndef BONUS_H
#define BONUS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "Sprites.h"

#define BONUS_NUM 32
#define BONUS_LIFESPAN 300
#define BONUS_RANDOM 0.35 // 35% chance

typedef struct BONUS {
    int x;
    int y;
    int type;
    bool isDropped;
    int lifespan;
} Bonus;

Bonus bonus[BONUS_NUM];

void bonus_ClearAll() {
    for (int i = 0; i < BONUS_NUM; i++) {
        bonus[i].isDropped = false;
        bonus[i].lifespan = 0;
    }
}

void bonus_Create(int x, int y) {
    if ((rand() / (double)RAND_MAX) < BONUS_RANDOM) {
        for (int i = 0; i < BONUS_NUM; i++) {
            if (!bonus[i].isDropped) {
                bonus[i].x = x;
                bonus[i].y = y;
                bonus[i].type = rand() % 3;
                bonus[i].isDropped = true;
                bonus[i].lifespan = BONUS_LIFESPAN;
                break; // Create only one bonus and exit the loop
            }
        }
    }
}

void bonus_Update() {
    for (int i = 0; i < BONUS_NUM; i++) {
        if (bonus[i].isDropped) {
            bonus[i].lifespan--;
            if (bonus[i].lifespan <= 0) {
                bonus[i].isDropped = false; // Remove the bonus after its lifespan
            }
        }
    }
}

void bonus_Draw() {
    for (int i = 0; i < BONUS_NUM; i++) {
        if (bonus[i].isDropped) {
            al_draw_bitmap(sprites.NIKITA, bonus[i].x, bonus[i].y, 0);
        }
    }
}

#endif
