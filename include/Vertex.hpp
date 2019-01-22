



#ifndef Vertex_HPP
#define Vertex_HPP


#include "allegro5/allegro.h"

#include "Vec3.hpp"




class Vertex {

///   void CalcNormal();
///   void CalcNormal() {}
public :
   
   Vertex(Vec3 p);
   Vertex(Vec3 p , ALLEGRO_COLOR c);
   Vertex(Vec3 p , Vec3 n , ALLEGRO_COLOR c);

   
   Vec3 pos;
   Vec3 nml;
//   std::vector<unsigned int> edge_list;
   ALLEGRO_COLOR col;
};



typedef Vertex VERTEX;



#endif // Vertex_HPP





