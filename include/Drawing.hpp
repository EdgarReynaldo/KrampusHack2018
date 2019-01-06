



#ifndef Drawing_HPP
#define Drawing_HPP

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"



#include "Vec3.hpp"
//#include "Triangle.hpp"
//#include "Quad.hpp"
#include "Prism.hpp"
#include "Track.hpp"

#include "allegro5/allegro.h"
#include "GL/gl.h"

/** Not thread safe */

/// inline void DrawLine(Vec3 p1 , Vec3 p2 , ALLEGRO_COLOR c);

inline void DrawLine(Vec3 p1 , Vec3 p2 , ALLEGRO_COLOR col) {
   
   unsigned char c[4] = {0};
   glBegin(GL_LINES);
   al_unmap_rgba(col , &c[0] , &c[1] , &c[2] , &c[3]);
   glColor4ub(c[0] , c[1] , c[2] , c[3]);
   glVertex3d(p1.x , p1.y , p1.z);
   glVertex3d(p2.x , p2.y , p2.z);
   glEnd();
   
}

void OutlinePrism(const Prism& p , ALLEGRO_COLOR c);


void DrawTrackOutlines(const Track& track);


#endif // Drawing_HPP
