



#include "BasicAllegro.hpp"
#include "allegro5/allegro_opengl.h"
#include "allegro5/allegro_color.h"
#include "GL/gl.h"

#include <cstdio>



int maingl(int argc , char** argv) {
   
   (void)argc;
   (void)argv;
   
   if (!al_init()) {return -1;}
   
   al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_OPENGL);
   ALLEGRO_DISPLAY* d = al_create_display(640,480);
   
   printf("glGenBuffers address is : %p\n" , glGenBuffers);
   
   al_destroy_display(d);
   
   return 0;
}

#include "SpatialInfo.hpp"

#include "Intro.hpp"
#include "Editor.hpp"
#include "Mesh.hpp"
#include "Skybox.hpp"

#include <iostream>

int main(int argc , char** argv) {
   
   
   (void)argc;
   (void)argv;
   
   int setup = SetupAllegro(900,600);
   if (setup != 0) {
      printf("Setup returned %d\n" , setup);
      return setup;
   }
   

   
   const char* glvs = al_get_default_shader_source(ALLEGRO_SHADER_GLSL , ALLEGRO_VERTEX_SHADER);
   const char* glps = al_get_default_shader_source(ALLEGRO_SHADER_GLSL , ALLEGRO_PIXEL_SHADER);
   
   FILE* f1 = fopen("Vertex.shader.txt" , "w");
   FILE* f2 = fopen("Fragment.shader.txt" , "w");
   
   if (f1) {
      fprintf(f1 , "GLSL VERTEX SHADER Source :\n%s\n\n" , glvs);
   }
   if (f2) {
      fprintf(f2 , "GLSL PIXEL SHADER Source :\n%s\n\n" , glps);
   }
   fclose(f1);
   fclose(f2);
      
   al_start_timer(timer);
   
//   Intro();
   
   Scene* scene = new Editor();
   
   bool quit = false;
   
   
   Orient o;
   Mesh pyramid;
   
   ALLEGRO_COLOR c[4] = {al_map_rgb(0,0,255) , al_map_rgb(0,255,0) , al_map_rgb(255,0,0) , al_map_rgb(255,255,0)};
   
   for (unsigned int i = 0 ; i < 3 ; ++i) {
      o.Reset();
      o.Turn(Vec3(i*2.0*M_PI/3.0 , M_PI/6.0 , 0) , 1.0);
      pyramid.AddVertex(VERTEX(o.Fw()*50.0 , c[i]));
   }
   o.Reset();
   pyramid.AddVertex(VERTEX(o.Up()*50.0 , c[3]));
   
   pyramid.AddEdge(0,1);
   pyramid.AddEdge(1,2);
   pyramid.AddEdge(2,0);
   pyramid.AddEdge(0,3);
   pyramid.AddEdge(1,3);
   pyramid.AddEdge(2,3);
   
   pyramid.AddTriFace(2,1,0);
   pyramid.AddTriFace(3,0,1);
   pyramid.AddTriFace(3,1,2);
   pyramid.AddTriFace(3,2,0);
   
   
   
   
   
   while (!quit) {
      if (scene->Redraw()) {
         al_set_target_backbuffer(d);
      
         al_clear_to_color(al_map_rgb(0,0,0));
         
         glClear(GL_DEPTH_BUFFER_BIT);
         glEnable(GL_DEPTH_TEST);
         glDepthFunc(GL_LESS);///LEQUAL);
         glFrontFace(GL_CCW);
         glCullFace(GL_BACK);
         glEnable(GL_CULL_FACE);
         glEnable(GL_BLEND);

         scene->Display();
         
         
//         pyramid.RenderFaces(SpatialInfo() , Vec3(1,1,1));
///         cube.GetMesh().RenderFaces(SpatialInfo() , Vec3(30,30,30));
///         cube.GetMesh().RenderEdges(SpatialInfo() , Vec3(30,30,30) , al_map_rgb(0,0,255));
         
         
         
         glDisable(GL_BLEND);
         glDisable(GL_DEPTH_TEST);
         glDisable(GL_CULL_FACE);
         glClear(GL_DEPTH_BUFFER_BIT);
         Camera::Setup2D();
         printf("%u" , glGetError());
         al_draw_textf(font , al_map_rgb(255,255,255) , 10 , 10 , 0 , "%2.3lf" , al_get_time());
         al_flip_display();
      }
      int ticks = 0;
      do {
         ALLEGRO_EVENT ev;
         al_wait_for_event(q , &ev);
         if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_D) {
            bpoint = true;
         }
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
   
   DumpErrors();
   
   return 0;
}

