#ifndef EXPLOSION
#define EXPLOSION

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "Sprites.h"
#include "Player.h"
#include "Bomb.h"

#define EXPL_NUM 128
#define EXPL_TIME 30

typedef struct EXPLOSION {
	int x, y;
	bool isActive;
    int time;
}Explosion;


void explosion_ClearAll(Explosion expl[EXPL_NUM]) {
	for (int i = 0; i < EXPL_NUM; i++)
		expl[i].isActive = false;
}

//Method to add bomb whenever the bomb was placed
void explosion_Add(Explosion explosions[EXPL_NUM], int x, int y) {
    for (int i = 0; i < EXPL_NUM; i++) {
        if (explosions[i].isActive)
            continue;

        explosions[i].x = x;
        explosions[i].y = y;
        explosions[i].time = 0;
        explosions[i].isActive = true;
        return;
    }
}

// Draw explosions
void explosion_Draw(Explosion explosions[EXPL_NUM], Sprites spriteP) {
    for (int i = 0; i < EXPL_NUM; i++) {
        if (explosions[i].isActive) {
            al_draw_bitmap(spriteP.EXPLOSIONE, explosions[i].x, explosions[i].y, 0);
            al_draw_bitmap(spriteP.EXPLOSIONE, explosions[i].x+TILEBLOCK_SPRITE_SIZE, explosions[i].y, 0);
            al_draw_bitmap(spriteP.EXPLOSIONE, explosions[i].x-TILEBLOCK_SPRITE_SIZE, explosions[i].y, 0);
            al_draw_bitmap(spriteP.EXPLOSIONE, explosions[i].x, explosions[i].y+TILEBLOCK_SPRITE_SIZE, 0);
            al_draw_bitmap(spriteP.EXPLOSIONE, explosions[i].x, explosions[i].y-TILEBLOCK_SPRITE_SIZE, 0);
            al_draw_bitmap(spriteP.EXPLOSIONE, explosions[i].x + TILEBLOCK_SPRITE_SIZE, explosions[i].y + TILEBLOCK_SPRITE_SIZE, 0);
            al_draw_bitmap(spriteP.EXPLOSIONE, explosions[i].x + TILEBLOCK_SPRITE_SIZE, explosions[i].y - TILEBLOCK_SPRITE_SIZE, 0);
            al_draw_bitmap(spriteP.EXPLOSIONE, explosions[i].x - TILEBLOCK_SPRITE_SIZE, explosions[i].y + TILEBLOCK_SPRITE_SIZE, 0);
            al_draw_bitmap(spriteP.EXPLOSIONE, explosions[i].x - TILEBLOCK_SPRITE_SIZE, explosions[i].y - TILEBLOCK_SPRITE_SIZE, 0);

        }
    }
}

// Update explosions
void explosion_Update(Explosion explosions[EXPL_NUM]) {
    for (int i = 0; i < EXPL_NUM; i++) {
        if (explosions[i].isActive) {
            explosions[i].time++;
            if (explosions[i].time >= EXPL_TIME) {
                explosions[i].isActive = false;
            }
        }
    }
}

#endif