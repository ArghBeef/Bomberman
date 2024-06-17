#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>

///Rozmiar sprajtu w pixelach
#define TILEBLOCK_SPRITE_SIZE 63

//! Struktura zawierajaca wszystki mozliwe sprajty
typedef struct SPRITES {
    ALLEGRO_BITMAP* spritesheet;

    ALLEGRO_BITMAP* GRASS;
    ALLEGRO_BITMAP* NIKITA;
    ALLEGRO_BITMAP* BRICK;
    ALLEGRO_BITMAP* DESTRUCTABLE;
    ALLEGRO_BITMAP* PLAYER0;
    ALLEGRO_BITMAP* PLAYER1;
    ALLEGRO_BITMAP* BOMBA;
    ALLEGRO_BITMAP* EXPLOSIONE;
    ALLEGRO_BITMAP* GAMEBACK;
} Sprites;


///Zmiena dla sprajtow
Sprites sprites;

//! Funkcja wyodrebniania wszystkich sprajtow z arkusza sprajtow
ALLEGRO_BITMAP* sprite_ExtractBitmap(int x, int y, int w, int h, Sprites* spriteS)
{
    ALLEGRO_BITMAP* sprite = al_create_sub_bitmap(spriteS->spritesheet, x, y, w, h);

    if (!sprite) {
        printf("FAIL: Couldnt load spritesheet-bitmap!");
        exit(1);
    }
    return sprite;
}

//! Ladowanie sprajtow z arkusza sprajtow
void sprite_Load(Sprites* spriteS) {
    spriteS->spritesheet = al_load_bitmap("resources/spritesheet.png");
    spriteS->GAMEBACK = al_load_bitmap("resources/gameback.png");

    if (!spriteS->spritesheet) {
        printf("FAIL: Couldnt load spritesheet!");
        exit(1);
    }

    spriteS->BRICK = sprite_ExtractBitmap(0, 0, TILEBLOCK_SPRITE_SIZE, TILEBLOCK_SPRITE_SIZE, spriteS);
    spriteS->DESTRUCTABLE = sprite_ExtractBitmap(65, 0, TILEBLOCK_SPRITE_SIZE, TILEBLOCK_SPRITE_SIZE, spriteS);
    spriteS->GRASS = sprite_ExtractBitmap(0, 65, TILEBLOCK_SPRITE_SIZE, TILEBLOCK_SPRITE_SIZE, spriteS);

    spriteS->PLAYER0 = sprite_ExtractBitmap(129, 0, TILEBLOCK_SPRITE_SIZE, TILEBLOCK_SPRITE_SIZE, spriteS);
    spriteS->PLAYER1 = sprite_ExtractBitmap(129, 65, TILEBLOCK_SPRITE_SIZE, TILEBLOCK_SPRITE_SIZE, spriteS);

    spriteS->BOMBA = sprite_ExtractBitmap(193, 0, TILEBLOCK_SPRITE_SIZE, TILEBLOCK_SPRITE_SIZE, spriteS);
    spriteS->EXPLOSIONE = sprite_ExtractBitmap(193, 65, TILEBLOCK_SPRITE_SIZE, TILEBLOCK_SPRITE_SIZE, spriteS);

    spriteS->NIKITA = sprite_ExtractBitmap(65, 65, TILEBLOCK_SPRITE_SIZE, TILEBLOCK_SPRITE_SIZE, spriteS);


}

//! Usuwanie wszystkich sprajtow
void sprites_Delete(Sprites spriteS) {

    al_destroy_bitmap(spriteS.BOMBA);
    al_destroy_bitmap(spriteS.BRICK);
    al_destroy_bitmap(spriteS.DESTRUCTABLE);
    al_destroy_bitmap(spriteS.EXPLOSIONE);
    al_destroy_bitmap(spriteS.GRASS);
    al_destroy_bitmap(spriteS.PLAYER0);
    al_destroy_bitmap(spriteS.PLAYER1);
    al_destroy_bitmap(spriteS.NIKITA);
    al_destroy_bitmap(spriteS.GAMEBACK);

    al_destroy_bitmap(spriteS.spritesheet);

}

#endif