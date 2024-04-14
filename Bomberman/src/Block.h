#ifndef BLOCK
#define BLOCK

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "Sprites.h"

typedef struct BLOCK {
    int x;
    int y;
    //bool destructable;
    bool collide;
    //bool isDestroyed;
}Block;






#endif