


#include "BasicAllegro.hpp"

#include <cstdio>


#include "allegro5/allegro_color.h"

#include "SpatialInfo.hpp"

#include "Intro.hpp"
#include "Editor.hpp"
#include "Mesh.hpp"

#include "GL/gl.h"



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
   
   printf("GLSL VERTEX SHADER Source :\n%s\n\n" , glvs);
   printf("GLSL PIXEL SHADER Source :\n%s\n\n" , glps);
   
      
   al_start_timer(t);
   
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
   
   
   UnitCube cube;
   
   while (!quit) {
      if (scene->Redraw()) {
         al_clear_to_color(al_map_rgb(0,0,0));
         
         glClear(GL_DEPTH_BUFFER_BIT);
         glEnable(GL_DEPTH_TEST);
         
         scene->Display();
         
         glFrontFace(GL_CCW);
         glCullFace(GL_BACK);
         glEnable(GL_CULL_FACE);
         glEnable(GL_COLOR);
         
//         pyramid.RenderFaces(SpatialInfo() , Vec3(1,1,1));
         cube.GetMesh().RenderFaces(SpatialInfo() , Vec3(30,30,30));
         cube.GetMesh().RenderEdges(SpatialInfo() , Vec3(30,30,30) , al_map_rgb(0,0,255));
         
         glDisable(GL_COLOR);
         glDisable(GL_DEPTH_TEST);
         Camera::Setup2D();
         al_draw_textf(f , al_map_rgb(255,255,255) , 10 , 10 , 0 , "%2.3lf" , al_get_time());
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

