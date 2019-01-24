




#include "BasicAllegro.hpp"
#include "allegro5/allegro_opengl.h"
#include "GL/gl.h"
#include "GL/glu.h"
#undef GL_VERSION_4_3
#include "GL/glext.h"



ALLEGRO_DISPLAY* d = 0;
ALLEGRO_EVENT_QUEUE* q = 0;
ALLEGRO_TIMER* t = 0;
ALLEGRO_FONT* f = 0;
ALLEGRO_BITMAP* buf = 0;

int sw = 900;
int sh = 600;

double FPS = 60.0;
double SPT = 1.0/FPS;



#include <cstdio>


void __stdcall
MessageCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLbyte* message,
                 const void* userParam )
{
  fprintf( stdout, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}



int SetupAllegro(int screenw , int screenh) {
   
   if (!al_init()) {return -1;}
   if (!al_init_font_addon() || !al_init_ttf_addon()) {return -2;}
   if (!al_init_primitives_addon() || !al_init_image_addon()) {return -3;}
   
   if (!al_install_keyboard() || !al_install_mouse() || !al_install_joystick()) {
      return -10;
   }
   
   FreeAllegro();
   
   al_set_new_display_option(ALLEGRO_FLOAT_DEPTH , 1 , ALLEGRO_SUGGEST);
   al_set_new_display_option(ALLEGRO_DEPTH_SIZE , 32 , ALLEGRO_SUGGEST);
   
   al_set_new_display_flags(ALLEGRO_FULLSCREEN | ALLEGRO_OPENGL);
///   al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW | ALLEGRO_OPENGL);
///   al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_OPENGL);
   
   screenw = 1920;
   screenh = 1080;
   
   d = al_create_display(screenw , screenh);
   
   buf = al_create_bitmap(screenw,screenh);
   
   sw = al_get_display_width(d);
   sh = al_get_display_width(d);
   
   q = al_create_event_queue();
   
   t = al_create_timer(SPT);
   
   f = al_load_ttf_font("Verdana.ttf" , -20 , 0);
   
   if (!d || !buf || !q || !t || !f) {
      return 10;
   }
   
   al_register_event_source(q , al_get_display_event_source(d));
   al_register_event_source(q , al_get_keyboard_event_source());
   al_register_event_source(q , al_get_mouse_event_source());
   al_register_event_source(q , al_get_timer_event_source(t));
   

   // During init, enable debug output
   glEnable              ( GL_DEBUG_OUTPUT );
   glDebugMessageCallback( MessageCallback, 0 );

   if (!CheckOpenGL()) {
      return 100;
   }
   
   return 0;
}



void FreeAllegro() {
   if (t) {
      al_destroy_timer(t);
      t = 0;
   }
   if (q) {
      al_destroy_event_queue(q);
      q = 0;
   }
   if (buf) {
      al_destroy_bitmap(buf);
      buf = 0;
   }
   if (f) {
      al_destroy_font(f);
      f = 0;
   }
   if (d) {
      al_destroy_display(d);
      d = 0;
   }
}



bool CheckOpenGL() {
   return glGenBuffers && glBindBuffer && glBufferData && glCreateShader && glCreateProgram && glShaderSource;
}
