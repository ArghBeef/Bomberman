#ifndef GAME
#define GAME

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

//Gamestates will be in enum or smth. Later will be used to change scenes: Menu, Game, Endgame, maybe even something more


//methods i would like to use anywhere that would not be connected to any unrelated header file
bool game_Collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {

    if (ax1 > bx2) return false;
    if (ax2 < bx1) return false;
    if (ay1 > by2) return false;
    if (ay2 < by1) return false;

    return true;
}



#endif