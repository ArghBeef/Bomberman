#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

#include "Sprites.h"
#include "Player.h"

///Wspolrzedne poczatku rysowanie hud`u po X
#define HUD_STARTX 550
///Wspolrzedne poczatku rysowanie hud`u po Y
#define HUD_STARTY 750

///Zmiena globalna dla tekstu
ALLEGRO_FONT* font;

//! Tablica zawierajaca tekst o wszystkich mozliwych bonusach (nazwa)
static const char* bonuses[] = { "Bomb Reload", "Bigger Radius", "Sabotage", "Emptiness"};

//! Inicjalizacja hud`a
void hud_init()
{
    font = al_load_ttf_font("resources/tf2.ttf", 22, 0);
    if (!font) {
        printf("FAIL: Couldnt load font!");
        exit(1);
    }
}

//! Rysowanie hud`a
void hud_Draw(Player* player, int positionx, int positiony) {
    al_draw_textf(font, al_map_rgb(255, 255, 255), HUD_STARTX + positionx, HUD_STARTY + positiony, ALLEGRO_ALIGN_CENTER, "Player %d:",player->ID);
    al_draw_textf(font, al_map_rgb(255, 255, 255), HUD_STARTX + positionx, HUD_STARTY + positiony + 25, ALLEGRO_ALIGN_CENTER, "Score:%d", player->score);
    al_draw_textf(font, al_map_rgb(255, 255, 255), HUD_STARTX + positionx, HUD_STARTY + positiony + 50 , ALLEGRO_ALIGN_CENTER, "Current Bonus:%s", bonuses[player->currentBonus]);
}

//! Usuniecie hud`a
void hud_Delete() {
    al_destroy_font(font);
}

#endif