#ifndef PLAYER
#define PLAYER

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "Game.h"
#include "Sprites.h"
#include "Bomb.h"
#include "Block.h"
#include "Explosion.h"

typedef struct PLAYER {
	int ID;
	bool alive;
    bool bombPlaced;
	int x, y;
	int xBomb, yBomb; // to determine the direction where to put the bomb
    int reload;

} Player;

Player player_Create(int pID, int pStartPosition) {

	if (pID > 1) {
		printf("FAIL:Only 0 and 1 ID are possible for the player");
		exit(1);
	}

	Player player;
	player.ID = pID;
	player.alive = true;
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

bool player_CheckCollision(int nextX, int nextY, Block blocks[TILENUM_H][TILENUM_W]) {
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
    //Idk, but it might seem logic to set another pair of cordinates for bounding box of block to y/x+SpriteSize but it doesnt work and instead
    //player collides with the block and the block arround 1 tile (an area 2X2). Setting bounding box to just x and y do a trick so I will leave it like this ;S
}

bool player_CheckExplode(Player* player, Explosion explosions[EXPL_NUM]) {
    for (int i = 0; i < EXPL_NUM; i++) {
        if (explosions[i].isActive) {

            if (game_Collide(player->x, player->y, player->x + TILEBLOCK_SPRITE_SIZE, player->y + TILEBLOCK_SPRITE_SIZE, explosions[i].x, explosions[i].y, explosions[i].x + TILEBLOCK_SPRITE_SIZE, explosions[i].y + TILEBLOCK_SPRITE_SIZE)) {
                return true; //If it collides with explosion
            }
        }
    }
    return false;
}



void player_Update(Player* player, ALLEGRO_EVENT* event, Bomb bombs[BOMB_NUM], Block blocks[TILENUM_H][TILENUM_W], Explosion* expl) {
    if (!player->alive) //Set a flag for END : GameState
        return;
    if (player->reload <= 0) {
        player->bombPlaced = false;
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
                    bomb_Add(bombs, player->xBomb, player->yBomb,expl);
                    player->bombPlaced = true;

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
                    bomb_Add(bombs, player->xBomb, player->yBomb,expl);
                   player->bombPlaced = true;
                }
            }
        }
        break;
    }

    if (!player_CheckCollision(nextX, nextY, blocks)) {
        player->x = nextX;
        player->y = nextY;
    }

    if (player->bombPlaced)
        player->reload--;

    if (player_CheckExplode(player, expl)) {
        player->alive = false; //Saying "die" is very rude so lets say this checkexplode and unalives poor player
    }
}



void player_Draw(Player* player, Sprites spriteP) {
	if (!player->alive) //Make game end (flag) depending on the player ID
		return;

	switch (player->ID) {
	case 0:
		al_draw_bitmap(spriteP.PLAYER0, player->x, player->y, 0);
		break;
	case 1:
		al_draw_bitmap(spriteP.PLAYER1, player->x, player->y, 0);
		break;

	}
}

#endif