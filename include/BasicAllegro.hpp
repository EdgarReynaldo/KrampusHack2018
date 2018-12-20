



#ifndef BasicAllegro_HPP
#define BasicAllegro_HPP



#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_image.h"




extern ALLEGRO_DISPLAY* d;
extern ALLEGRO_EVENT_QUEUE* q;
extern ALLEGRO_TIMER* t;
extern ALLEGRO_FONT* f;
extern ALLEGRO_BITMAP* buf;

extern int sw;
extern int sh;

extern double FPS;
extern double SPT;

int SetupAllegro(int screenw , int screenh);
void FreeAllegro();






#endif // BasicAllegro_HPP




