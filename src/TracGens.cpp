



#include "TrackGen.hpp"





SpatialInfo StraightAway::Eval(const SpatialInfo& start , double pct) {
   SpatialInfo current = start;
   current.pos += start.orient.fw*l*pct;
   return current;
}



SpatialInfo Turn::Eval(const SpatialInfo& start , double pct) {
   if (pct <= 0.0) {return start;}
   if (pct > 1.0) {pct = 1.0;}
   
   SpatialInfo current = start;
   const double yaw = pct;
   
   current.orient = AlterPath(current.orient , Vec3(yaw , 0 , 0));
   
   /// X coord is w*sin(t*PI/2)
   /// Y coord is h*sin(t*PI/2)
   /// Y coord is forward movement
   /// X coord is lateral movement
   
   Orient o = start.orient;
   
   current.pos += o.rt*w*sin(M_PI/2.0);
   current.pos += o.fw*h*sin(M_PI/2.0);
   return current;
}



double Turn::Length() {
   const double a = abs(w);
   const double b = abs(h);
   const double h = (a-b)*(a-b)/((a+b)*(a+b));
   
   const double left = M_PI*(a+b);
   double right = 1.0;
   right += h/4.0;
   right += h*h/64.0;
   right += h*h*h/256.0;
   right += h*h*h*h*25.0/16384.0;
   right += h*h*h*h*h*49.0/65536.0;
   right += h*h*h*h*h*h*441.0/1048576.0;
   return left*right/4.0;// quarter ellipse
}



SpatialInfo Curve::Eval(const SpatialInfo& start , double pct) {
   if (pct <= 0.0) {return start;}
   if (pct > 1.0) {pct = 1.0;}
   
   /// First find the radius of the curve
   assert(t != 0.0);
   
   const double radius = l/t;
   
   const double yaw = t*pct*cos(r);
   const double pitch = t*pct*sin(r);

   SpatialInfo current = start;
   
   Orient o = start.orient;
   
   o = AlterPath(o , Vec3(yaw,pitch,0.0));
   
   Vec3 pos = start.pos;
   
   Vec3 fw = start.orient.fw;
   Vec3 up = start.orient.up;
   Vec3 rt = start.orient.rt;
   
   up = Rotate3D(up , fw , r);
   rt = Rotate3D(rt , fw , r);

   Vec3 rad = rt*radius*((t < 0.0)?-1.0:1.0);
   Vec3 c = pos + rad;
   
   rad = Rotate3D(-rad , up , -t*pct);
   
   Vec3 pos2 = c + rad;
   
   current.pos = pos2;
   current.orient = o;
   return current;
}




