#ifndef BOMB_H
#define BOMB_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "Sprites.h"
#include "Sound.h"
#include "Explosion.h"

///Ilosc mozliwych bomb na mapie
#define BOMB_NUM 8
///Najmniejsza jednostka czasu do obliczenia detonacji bomby
#define BOMB_TIME 30

//! Struktura opisujaca bombe
typedef struct BOMBS {
	int x; ///< Wspolrzedne X
	int y; ///< Wspolrzedne Y
	bool isPlaced; ///< Czy jest ustawiona
	int time; ///< Czas bomby
}Bomb;

///Zmiena dla bomb (tablica)
Bomb bombs[BOMB_NUM];


//! Ustawienie statusu wszystkich bomb "isPlaced" na "false"
void bomb_ClearAll() {
	for (int i = 0; i < BOMB_NUM; i++)
		bombs[i].isPlaced = false;
}

/**
* Funkcja dodawania bomby za kazdym razem, gdy gracz nacisnie klawisz
* @param lastX Wspolrzedne X
* @param lastY Wspolrzedne Y
*/
void bomb_Add(int lastX, int lastY) {
	
	for (int i = 0; i < BOMB_NUM; i++) {
		if (bombs[i].isPlaced)
			continue;
		bombs[i].time = 0;
		bombs[i].x = lastX;
		bombs[i].y = lastY;
		bombs[i].isPlaced = true;
		return;
	}
}

//! Rysowanie bomb na ekranie
void bomb_Draw() {
	for (int i = 0; i < BOMB_NUM; i++) {
		if (!bombs[i].isPlaced)
			continue;

		if (bombs[i].time <= BOMB_TIME*2) { //Show a normal sprite
				al_draw_bitmap(sprites.BOMBA, bombs[i].x, bombs[i].y, 0);
		}
		else {
			if (((bombs[i].time / 5) % 3) == 1) //Blink for last ticks
				al_draw_bitmap(sprites.BOMBA, bombs[i].x, bombs[i].y, 0);
		}
	}
}

//! Aktualizacja stanu bomb
void bomb_Update() {
	for (int i = 0; i < BOMB_NUM; i++) {
		if (!bombs[i].isPlaced)
			continue;

		bombs[i].time++; 
		if (bombs[i].time >= BOMB_TIME*4) { //the default is 90 (arround 3 seconds) but for powerups I will change it (To detonate faster or slower or even controled explode)
			al_play_sample(sounds.EXPLODE, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
			explosion_Add(bombs[i].x, bombs[i].y);
			bombs[i].isPlaced = false;
		}
	}
}

#endif