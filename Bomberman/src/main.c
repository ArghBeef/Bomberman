#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>

#include "Game.h"
#include "Map.h"
#include "Sprites.h"
#include "Player.h"
#include "Bomb.h"
#include "Explosion.h"
#include "Bonus.h"
#include "Menu.h"
#include "Sound.h"


///! Funkcja main
int main()
{
    srand(time(NULL));
    //! Inicjalizacja elementow Allegro
    al_init();
    al_install_keyboard();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    al_init_image_addon();
    al_init_ttf_addon();

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    ALLEGRO_DISPLAY* disp = al_create_display(1520, 860);

    al_init_primitives_addon();

    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(16);

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool windowClose = false; //So the window will close
    bool redraw = true; //If something happens - redraw that something
    ALLEGRO_EVENT event;
    ////////////////INITS////////////////////

    hud_init();
    sprite_Load(&sprites);
    sound_Load();
    bomb_ClearAll();
    explosion_ClearAll();
    bonus_ClearAll();
    map_Initialize(map_Load());
    player1 = player_Create(0, 1);
    player2 = player_Create(1, 3);
    al_start_timer(timer);

    al_play_sample(sounds.MUSIC, 0.9, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_TIMER: //Update
            switch (State) {
            case 0:
                if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                    if (event.keyboard.keycode == ALLEGRO_KEY_SPACE)
                        State = PLAYED;
                }
                break;
            case 1:
                break;
            case 2:
                player_Update(&player1, &event, blocks, expl);
                player_Update(&player2, &event, blocks, expl);
                bomb_Update();
                explosion_Update();
                bonus_Update();
                map_Update(blocks, expl);
                redraw = true;
                break;
            }
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE: //If window is closed
            windowClose = true;
            break;
        }

        if (windowClose)
            break;

        if (redraw && al_is_event_queue_empty(queue)) //Draw
        {
            switch (State) {
            case 0:
                al_draw_bitmap(sprites.GAMEBACK, 0, 0, 0);
                al_draw_text(font, al_map_rgb(0, 0, 0), 750, 820, ALLEGRO_ALIGN_CENTER, "Press SPACE to start");
                break;
            case 1:
                al_clear_to_color(al_map_rgb(255, 255, 255));
                al_draw_textf(font, al_map_rgb(0, 0, 0), 750, 420, ALLEGRO_ALIGN_CENTER, "Player-%d has lost the battle!", loserID);
                break;
            case 2:
                al_clear_to_color(al_map_rgb(0, 0, 0));
                al_draw_bitmap(sprites.GAMEBACK, 0, 0, 0);
                map_Draw(&sprites, blocks);
                player_Draw(&player1, sprites);
                player_Draw(&player2, sprites);
                hud_Draw(&player1, 0,0);
                hud_Draw(&player2, 500, 0);
                bomb_Draw();
                explosion_Draw();
                bonus_Draw();
                break;
            }

            al_flip_display();

            redraw = false;
        }
    }

    hud_Delete();
    sprites_Delete(sprites);
    al_shutdown_ttf_addon();
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
}