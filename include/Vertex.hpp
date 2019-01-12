



#ifndef Vertex_HPP
#define Vertex_HPP


#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"


#include "Vec2.hpp"
#include "Vec3.hpp"
#include <vector>
#include "GL/gl.h"




class Vertex {

   void CalcNormal();
///   void CalcNormal() {}
public :
   
   Vertex(Vec3 p) : pos(p) , nml() , edge_list() , col(al_map_rgba(255,255,255,255)) {}
   Vertex(Vec3 p , ALLEGRO_COLOR c) : pos(p) , nml() , edge_list() , col(c) {}
   Vertex(Vec3 p , Vec3 n , ALLEGRO_COLOR c) : pos(p) , nml(n) , edge_list() , col(c) {}
   
   Vec3 pos;
   Vec3 nml;
   std::vector<unsigned int> edge_list;
   ALLEGRO_COLOR col;
};


class TextureVertex {
public :

///   TextureVertex(ALLEGRO_BITMAP* tex , Vec2 tuv);
   TextureVertex(ALLEGRO_BITMAP* tex , Vec2 tuv) :
         bmp(tex),
         uv(tuv)
   {}

   ALLEGRO_BITMAP* bmp;
   Vec2 uv;///double u,v;
   
   
   
};


typedef Vertex VERTEX;
typedef TextureVertex TEXTEX;

#endif // Vertex_HPP
