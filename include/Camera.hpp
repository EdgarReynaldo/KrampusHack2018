



#ifndef Camera_HPP
#define Camera_HPP



#include "SpatialInfo.hpp"



class Camera {

protected :
   SpatialInfo info;

   double hfov;
   double aspect;/// w/h
   
   bool ortho;
   
public :
   
   Camera() : info() , hfov(90.0) , aspect(4.0/3.0) {}
   
   Camera(Vec3 pos , Orient o , double hview , double aspect_ratio) : info(pos,o) , hfov(hview) , aspect(aspect_ratio) {}
   
   void SetPos(Vec3 p) {info.pos = p;}
   void SetOrientation(Orient o) {info.orient = o;}
   void SetHFOV(double v) {hfov = v;}
   void SetAspect(double a) {aspect = a;}
   
   void ResetCamera();
   
   static void Setup2D();
};




#endif // Camera_HPP
