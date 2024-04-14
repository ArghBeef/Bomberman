#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>

#include "Game.h"
#include "Map.h"
#include "Sprites.h"
#include "Player.h"
#include "Bomb.h"
#include "Block.h"
#include "Explosion.h"

//Creating all the objects we need (and making them public)
Block blocks[TILENUM_H][TILENUM_W];
int map[TILENUM_H][TILENUM_W];
Sprites sprites;
Player player1;
Player player2;
Bomb bombs[BOMB_NUM];
Explosion expl[EXPL_NUM];




int main()
{
    ////////////////INITS////////////////////
    al_init();
    al_install_keyboard();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    al_init_image_addon();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_DISPLAY* disp = al_create_display(1520, 720);

    al_init_primitives_addon();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool windowClose = false; //So the window will close
    bool redraw = true; //If something happens - redraw that something
    ALLEGRO_EVENT event;
    ////////////////INITS////////////////////

    sprite_Load(&sprites);
    bomb_ClearAll(bombs);
    explosion_ClearAll(expl);

    map_Load(map);

    player1 = player_Create(0, 1);
    player2 = player_Create(1, 3);

    al_start_timer(timer);
    while (1)
    {
        al_wait_for_event(queue, &event); 

        switch (event.type)
        {
        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_TIMER: //kinda of update, where all the logical super buper stuff happens
            player_Update(&player1, &event, bombs,blocks, expl);
            player_Update(&player2, &event, bombs,blocks,expl);
            bomb_Update(bombs,expl);
            explosion_Update(expl);
            redraw = true;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE: //If window is closed
            windowClose = true;
            break;
        }

        if (windowClose)
            break;

        if (redraw && al_is_event_queue_empty(queue)) //Draw
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            map_Draw(map, &sprites,blocks);
            player_Draw(&player1, sprites);
            player_Draw(&player2, sprites);
            bomb_Draw(bombs, sprites);
            explosion_Draw(expl,sprites);

            al_flip_display();

            redraw = false;
        }
    }

    sprites_Delete(sprites);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}