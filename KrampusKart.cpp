


#include "BasicAllegro.hpp"

#include <cstdio>



int main(int argc , char** argv) {
   
   
   (void)argc;
   (void)argv;
   
   
   int setup = SetupAllegro(900,600);
   if (setup != 0) {
      printf("Setup returned %d\n" , setup);
      return setup;
   }
   
   
   al_clear_to_color(al_map_rgb(0,0,0));
   al_draw_textf(f , al_map_rgb(255,255,255) , sw/2 , sh/2 - al_get_font_ascent(f)/2 , ALLEGRO_ALIGN_CENTER , "KrampusHack 2018!");
   al_flip_display();
   
   
   
   al_rest(3.0);
   
   
   
   return 0;
}

