



#ifndef Drawing_HPP
#define Drawing_HPP

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"



#include "Vec3.hpp"
//#include "Triangle.hpp"
//#include "Quad.hpp"
#include "Prism.hpp"
#include "Track.hpp"



/** Not thread safe */

/// inline void DrawLine(Vec3 p1 , Vec3 p2 , ALLEGRO_COLOR c);

inline void DrawLine(Vec3 p1 , Vec3 p2 , ALLEGRO_COLOR c) {
   static ALLEGRO_VERTEX pts[2];
   pts[0] = {(float)p1.x , (float)p1.y , (float)p1.z , 0 , 0 , c};
   pts[1] = {(float)p2.x , (float)p2.y , (float)p2.z , 0 , 0 , c};
   al_draw_prim(pts , 0 , 0 , 0 , 2 , ALLEGRO_PRIM_LINE_LIST);
}

void OutlinePrism(const Prism& p , ALLEGRO_COLOR c);


void DrawTrackOutlines(const Track& track);


#endif // Drawing_HPP
