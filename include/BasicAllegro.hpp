



#ifndef BasicAllegro_HPP
#define BasicAllegro_HPP

#include "allegro5/allegro.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_opengl.h"

// #include "GL/gl.h"

extern ALLEGRO_DISPLAY* d;
extern ALLEGRO_EVENT_QUEUE* q;
extern ALLEGRO_TIMER* timer;
extern ALLEGRO_FONT* font;
extern ALLEGRO_BITMAP* buf;

extern int sw;
extern int sh;

extern double FPS;
extern double SPT;

int SetupAllegro(int screenw , int screenh);
void FreeAllegro();

bool CheckOpenGL();

unsigned int ErrCount();

extern bool bpoint;
extern bool cont;

void DumpErrors();

void eglBegin(GLenum mode);
void eglEnd();

#endif // BasicAllegro_HPP




