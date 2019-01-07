



#ifndef Skybox_HPP
#define Skybox_HPP


#include "Cube.hpp"
#include "allegro5/allegro.h"


#include "Cube.hpp"



class Skybox {
   
   TexturedUnitCube sbcube;
   
   ALLEGRO_BITMAP* sbimage;
   ALLEGRO_BITMAP* sbfaces[NUM_CUBE_FACES];
   
   void Clear();

   void MakeSkybox(const char* skybox_file);
   
public :
   Skybox(const char* skybox_file);
   ~Skybox() {Clear();}
   
   void Render() {
      sbcube.Inside().RenderFaces(SpatialInfo() , Vec3(1000,1000,1000));
      sbcube.Outside().RenderFaces(SpatialInfo() , Vec3(10,10,10));
   }
};

#endif // Skybox_HPP



