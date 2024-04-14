#ifndef BOMB
#define BOMB

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "Sprites.h"
#include "Player.h"
#include "Explosion.h"

#define BOMB_NUM 8
#define BOMB_TIME 30

typedef struct BOMB {
	int x, y;
	bool isPlaced;
	int time;
}Bomb;


//Set all bombs status isPlaced to false
void bomb_ClearAll(Bomb bombs[BOMB_NUM]) {
	for (int i = 0; i < BOMB_NUM; i++)
		bombs[i].isPlaced = false;
}

//Method to add bomb whenever the player presses the key
void bomb_Add(Bomb bombs[BOMB_NUM], int lastX, int lastY,Explosion* expl) {
	
	for (int i = 0; i < BOMB_NUM; i++) {
		if (bombs[i].isPlaced)
			continue;
		//Later add bomb_place sound 
		bombs[i].time = 0;
		bombs[i].x = lastX;
		bombs[i].y = lastY;
		bombs[i].isPlaced = true;
		return;
	}
}

//Method for rendering bomb
void bomb_Draw(Bomb bombs[BOMB_NUM], Sprites spriteP) {
	for (int i = 0; i < BOMB_NUM; i++) {
		if (!bombs[i].isPlaced)
			continue;

		if (bombs[i].time <= BOMB_TIME*2) { //Show a normal sprite
				al_draw_bitmap(spriteP.BOMBA, bombs[i].x, bombs[i].y, 0);
		}
		else {
			if (((bombs[i].time / 5) % 3) == 1) //Blink for last ticks
				al_draw_bitmap(spriteP.BOMBA, bombs[i].x, bombs[i].y, 0);
		}
	}
}

//Method for updating bomb state and later explosion (explosion in Explosion.h)
void bomb_Update(Bomb bombs[BOMB_NUM], Explosion* expl) {
	for (int i = 0; i < BOMB_NUM; i++) {
		if (!bombs[i].isPlaced)
			continue;

		bombs[i].time++; 
		if (bombs[i].time >= BOMB_TIME*4) { //the default is 90 (arround 3 seconds) but for powerups I will change it (To detonate faster or slower or even controled explode)
			//Do explosion method here when ready
			//and also the sounds
			explosion_Add(expl, bombs[i].x, bombs[i].y);
			bombs[i].isPlaced = false;
		}
	}
}

#endif