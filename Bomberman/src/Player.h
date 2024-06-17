#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "Sprites.h"
#include "Bomb.h"
#include "Map.h"
#include "Sound.h"

///Czas dzialania bonusu
#define BONUS_TIMERP 250;

//! Struktura opisujaca gracza
typedef struct PLAYERS {
    int ID; ///< ID gracza
    bool alive; ///< Czy gracz zyje (istnieje)
    bool bombPlaced; ///< Czy gracz podlozyl bombe
    int x; ///< Wspolrzedne X
    int y; ///< Wspolrzedne Y
    int xBomb; ///< Okreslic kierunek, w ktorym nalezy umiescic bombe po X
    int yBomb; ///< Okreslic kierunek, w ktorym nalezy umiescic bombe po Y
    int reload; ///< Przeladowanie bomby
    int currentBonus; ///< Jaki bonus ma gracz
    int bonusTimer; ///< Czas dzialania bonusu
    int isBonus; ///< Czy gracz ma bonus
    int score; ///< Wynik na podstawie zebranych bonusow
} Player;

int loserID; ///< Zmiana dla przegranego gracza
Player player1; ///< Zmiana gracza 1
Player player2; ///< Zmiana gracza 2

/**
* Funkcja do stworzenia gracza
* @param pID ID gracza
* @param pStartPosition Pozycja poczatkowa
* @retval Zwracanie stworzonego gracza
*/
Player player_Create(int pID, int pStartPosition) {

    if (pID > 1) {
        printf("FAIL:Only 0 and 1 ID are possible for the player");
        exit(1);
    }

    Player player;
    player.ID = pID;
    player.alive = true;
    player.currentBonus = 3;
    player.score = 0;
    player.isBonus = false;
    player.bonusTimer = BONUS_TIMERP;
    player.bombPlaced = false;
    player.reload = BOMB_TIME * 3; // I know this method of making reload time isnt great but its ok for now (at least na pierwszy kamien mielowy)

    switch (pStartPosition) {
    case 1:
        player.x = 130;
        player.y = 80;
        break;
    case 2:
        player.x = 130;
        player.y = 584;
        break;
    case 3:
        player.x = 1327;
        player.y = 584;
        break;
    case 4:
        player.x = 1327;
        player.y = 80;
        break;
    default:
        printf("FAIL:No such position. Should be 1, 2, 3 or 4");
        exit(1);
    }
    return player;
}

/**
* Sprawdzenie kolizji gracza miedzy blokami
* @param nextX Wspolrzedne X dla przyszlosci
* @param nextY Wspolrzedne Y dla przyszlosci
* @retval TRUE: Jezeli blok i gracz znajduja sie w tym samym miejscu
* @retval FALSE: Przeciwny wypadek
*/
bool player_CheckCollision(int nextX, int nextY) {
    for (int H = 0; H < TILENUM_H; H++) {
        for (int W = 0; W < TILENUM_W; W++) {
            if (blocks[H][W].collide) { //If block is collidable
                if (game_Collide(nextX, nextY, nextX + TILEBLOCK_SPRITE_SIZE, nextY + TILEBLOCK_SPRITE_SIZE, blocks[H][W].x, blocks[H][W].y, blocks[H][W].x, blocks[H][W].y)) {
                    return true; //If it collides return true
                }
            }
        }
    }
    return false;
}

/**
* Sprawdzenie kolizji gracza z explozja
* @param player Gracz
* @retval TRUE: Jezeli explozja i gracz znajduja sie w tym samym miejscu
* @retval FALSE: Przeciwny wypadek
*/
bool player_CheckExplode(Player* player) {
    for (int i = 0; i < EXPL_NUM; i++) {
        if (expl[i].isActive) {

                if (game_Collide(player->x, player->y, player->x, player->y, expl[i].x, expl[i].y, expl[i].x, expl[i].y))
                    return true; //If it collides with explosion

        }
    }
    return false;
}

/**
* Sprawdzenie kolizji gracza z bonusami
* @param player Gracz
*/
bool player_CheckBonus(Player* player) {
    for (int i = 0; i < BONUS_NUM; i++) {
        if (bonus[i].isDropped) {

            if (game_Collide(player->x, player->y, player->x + TILEBLOCK_SPRITE_SIZE, player->y + TILEBLOCK_SPRITE_SIZE, bonus[i].x, bonus[i].y, bonus[i].x + TILEBLOCK_SPRITE_SIZE, bonus[i].y + TILEBLOCK_SPRITE_SIZE)) {
                player->currentBonus = bonus[i].type;
                player->bonusTimer = 0;
                player->isBonus = true;
                bonus[i].isDropped = false;
                return true; //If it collides with bonus
            }
        }
    }
    return false;
}

/**
* Aktualizacja stanu gracza
* @param player Gracz
* @param even Eventy
* @param blocks Bloki
* @param expl Explozje
*/
void player_Update(Player* player, ALLEGRO_EVENT* event, Block blocks[TILENUM_H][TILENUM_W], Explosion* expl) {
    if (!player->alive) //Set a flag for END : GameState
        return;
    if (player->reload <= 0) {
        player->bombPlaced = false;
        al_play_sample(sounds.RELOAD, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        if (player->currentBonus == 2)
            player->reload = BOMB_TIME;
        player->reload = BOMB_TIME * 3;
    }

    int nextX = player->x; //These both are made to firstly check for collisions and if so, apply nextXY if no collisions or not
    int nextY = player->y;

    // Controls
    switch (player->ID) {
    case 0:
        if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event->keyboard.keycode == ALLEGRO_KEY_W) {
                nextY -= TILEBLOCK_SPRITE_SIZE;
                player->xBomb = nextX;
                player->yBomb = nextY - TILEBLOCK_SPRITE_SIZE;
            }
            if (event->keyboard.keycode == ALLEGRO_KEY_S) {
                nextY += TILEBLOCK_SPRITE_SIZE;
                player->xBomb = nextX;
                player->yBomb = nextY + TILEBLOCK_SPRITE_SIZE;
            }
            if (event->keyboard.keycode == ALLEGRO_KEY_A) {
                nextX -= TILEBLOCK_SPRITE_SIZE;
                player->yBomb = nextY;
                player->xBomb = nextX - TILEBLOCK_SPRITE_SIZE;
            }
            if (event->keyboard.keycode == ALLEGRO_KEY_D) {
                nextX += TILEBLOCK_SPRITE_SIZE;
                player->yBomb = nextY;
                player->xBomb = nextX + TILEBLOCK_SPRITE_SIZE;
            }
            if (event->keyboard.keycode == ALLEGRO_KEY_LSHIFT) {
                if (!player->bombPlaced) { //Later I will change so player can place more than one bomb at time with the use of powerups
                    bomb_Add(player->xBomb, player->yBomb);
                    player->bombPlaced = true;
                    al_play_sample(sounds.BOMB, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);

                }
            }
        }
        break;
    case 1:
        if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event->keyboard.keycode == ALLEGRO_KEY_UP) {
                nextY -= TILEBLOCK_SPRITE_SIZE;
                player->xBomb = nextX;
                player->yBomb = nextY - TILEBLOCK_SPRITE_SIZE;
            }
            if (event->keyboard.keycode == ALLEGRO_KEY_DOWN) {
                nextY += TILEBLOCK_SPRITE_SIZE;
                player->xBomb = nextX;
                player->yBomb = nextY + TILEBLOCK_SPRITE_SIZE;
            }
            if (event->keyboard.keycode == ALLEGRO_KEY_LEFT) {
                nextX -= TILEBLOCK_SPRITE_SIZE;
                player->yBomb = nextY;
                player->xBomb = nextX - TILEBLOCK_SPRITE_SIZE;
            }
            if (event->keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                nextX += TILEBLOCK_SPRITE_SIZE;
                player->yBomb = nextY;
                player->xBomb = nextX + TILEBLOCK_SPRITE_SIZE;
            }
            if (event->keyboard.keycode == ALLEGRO_KEY_ENTER) {
                if (!player->bombPlaced) {
                    bomb_Add(player->xBomb, player->yBomb);
                    player->bombPlaced = true;
                    al_play_sample(sounds.BOMB, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                }
            }
        }
        break;
    }

    if (player_CheckBonus(player)) {
        al_play_sample(sounds.BONUS, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        switch (player->currentBonus) {
        case 0:
            player->score += 100;
            player->bombPlaced = false;
            break;
        case 1:
            player->score += 200;
            radius = 1;
            break;
        case 2:
            player->score += 300;
            switch (player->ID) {
            case 0:
                al_play_sample(sounds.SABOTAGE, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                bomb_Add(player2.x, player2.y);
                break;
            case 1:
                al_play_sample(sounds.SABOTAGE, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                bomb_Add(player1.x, player1.y);
                break;
            }
            break;
        }
    }

    if (!player_CheckCollision(nextX, nextY)) {
        player->x = nextX;
        player->y = nextY;
    }

    if (player->bombPlaced)
        player->reload--;

    if (player_CheckExplode(player)) {
        al_play_sample(sounds.KILL, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        player->alive = false; //Saying "die" is very rude so lets say this checkexplode and unalives poor player
        State = END;
        loserID = player->ID;
    }

    if (player->isBonus) {
        player->bonusTimer++;
        if (player->bonusTimer >= EXPL_TIME)
            player->isBonus = false;
        }

    if (player->score > 2000) {
        State = END;
        switch (player->ID) {
        case 0:
            loserID = 1;
            break;
        case 1:
            loserID = 0;
            break;
        }
    }
}


//! Rysowanie gracza na ekranie
void player_Draw(Player* player) {
    if (!player->alive) //Make game end (flag) depending on the player ID
        return;

    switch (player->ID) {
    case 0:
        al_draw_bitmap(sprites.PLAYER0, player->x, player->y, 0);
        break;
    case 1:
        al_draw_bitmap(sprites.PLAYER1, player->x, player->y, 0);
        break;

    }
}

#endif