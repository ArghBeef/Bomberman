#ifndef SOUND_H
#define SOUND_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//! Struktura zawierajaca wszystki mozliwych dzwiekow
typedef struct SOUNDS {
	ALLEGRO_SAMPLE* SABOTAGE;
	ALLEGRO_SAMPLE* EXPLODE;
	ALLEGRO_SAMPLE* KILL;
	ALLEGRO_SAMPLE* BONUS;
	ALLEGRO_SAMPLE* BOMB;
	ALLEGRO_SAMPLE* RELOAD;
	ALLEGRO_SAMPLE* MUSIC;

}Sound;

///Zmiena dla dzwiekow
Sound sounds;

//! Ladowanie dzwiekow
void sound_Load() {
	sounds.SABOTAGE = al_load_sample("sounds/sabotage.wav");
	sounds.EXPLODE = al_load_sample("sounds/explode.wav");
	sounds.KILL = al_load_sample("sounds/kill.wav");
	sounds.BONUS = al_load_sample("sounds/bonus.wav");
	sounds.BOMB = al_load_sample("sounds/bomb.wav");
	sounds.RELOAD = al_load_sample("sounds/reload.wav");
	sounds.MUSIC = al_load_sample("sounds/music.mp3");
}




#endif