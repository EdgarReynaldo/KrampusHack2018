



#include "Camera.hpp"

#include "allegro5/allegro.h"



void Camera::ResetCamera() {
   ALLEGRO_TRANSFORM proj;
   ALLEGRO_TRANSFORM cam;
   
   const double near = 10.0;
   const double w = near*tan(hfov/2.0);
   const double l = -w;
   const double r = w;
   const double top = w/aspect;
   const double bot = -w/aspect;
   const double far = 2000.0;

   al_identity_transform(&proj);
   al_perspective_transform(&proj , l , top , near , r , bot , far);
   al_use_projection_transform(&proj);
   
   Vec3 eye = info.pos;
   Vec3 look = info.pos + info.orient.fw;
   Vec3 up = info.orient.up;
   
   al_identity_transform(&cam);
   al_build_camera_transform(&cam , eye.x , eye.y , eye.z , look.x , look.y , look.z , up.x , up.y , up.z);
   al_use_transform(&cam);
}

