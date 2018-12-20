


#include "BasicAllegro.hpp"

#include <cstdio>


#include "allegro5/allegro_color.h"

#include "SpatialInfo.hpp"

#include "Intro.hpp"
#include "Editor.hpp"



int main(int argc , char** argv) {
   
   
   (void)argc;
   (void)argv;
   
   
   int setup = SetupAllegro(900,600);
   if (setup != 0) {
      printf("Setup returned %d\n" , setup);
      return setup;
   }
   
   
   al_start_timer(t);
   
   Intro();
   
   
   do {
      ALLEGRO_EVENT ev;
      al_flush_event_queue(q);
      al_wait_for_event(q , &ev);
      if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE || ev.type == ALLEGRO_EVENT_KEY_DOWN) {break;}
   } while (1);
   
   
   Scene* scene = new Editor();
   
   bool quit = false;
   
   while (!quit) {
      if (scene->Redraw()) {
         scene->Display();
         al_flip_display();
      }
      int ticks = 0;
      do {
         ALLEGRO_EVENT ev;
         al_wait_for_event(q , &ev);
         if (ev.type == ALLEGRO_EVENT_TIMER) {
            ++ticks;
            /// Slow down gracefully
            if (ticks == 1) {
               if (scene->Update(SPT) == STATUS_QUIT) {
                  quit = true;
               }
            }
         }
         if (STATUS_QUIT == scene->HandleEvent(ev)) {
            quit = true;
         }
      } while (!al_is_event_queue_empty(q));
   }
   
   delete scene;
   
   return 0;
}

