



#include "Orient.hpp"



void Orient::CalcAxes() {

   Vec3 f = FORWARD;
   Vec3 r = RIGHT;
   Vec3 u = UP;

   /// Yaw rotates around the y axis pointing up
   
   f = Rotate3D(f , u , theta.yaw);
   r = Rotate3D(r , u , theta.yaw);
   
   /// Pitch rotates around the x axis pointing right
   
   f = Rotate3D(f , r , theta.pitch);
   u = Rotate3D(u , r , theta.pitch);
   
   /// Roll rotates around the z axis pointing forward
   
   r = Rotate3D(r , f , theta.roll);
   u = Rotate3D(u , f , theta.roll);
   
   fw = f;
   rt = r;
   up = u;
}



void Orient::Turn(Vec3 omega , double dt) {
   theta += omega*dt;
   CalcAxes();
}



