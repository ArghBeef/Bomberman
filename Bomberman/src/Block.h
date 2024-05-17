#ifndef BLOCK_H
#define BLOCK_H

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>


//#define EXPL_NUM 128
//#define TILENUM_H 11 //Height
//#define TILENUM_W 22 //Width

typedef struct BLOCKS {
    int x;
    int y;
    int type;
    bool destructable;
    bool collide;
}Block;






#endif