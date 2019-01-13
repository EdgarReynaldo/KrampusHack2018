



#include "TrackGen.hpp"
#include "Exception.hpp"




SpatialInfo StraightAway::Eval(const SpatialInfo& start , double pct) {
   SpatialInfo current = start;
   current.pos += start.orient.Fw()*l*pct;
   return current;
}



SpatialInfo Turn::Eval(const SpatialInfo& start , double pct) {
   if (pct <= 0.0) {return start;}
   if (pct > 1.0) {pct = 1.0;}
   
   SpatialInfo current = start;

   const double yaw = pct*M_PI/2.0;
   
///   double rad = w + (h-w)*pct;
   
   current.pos += start.orient.Rt()*w*(cos(pct*M_PI/2.0) - 1.0);
   current.pos += start.orient.Fw()*h*sin(pct*M_PI/2.0);

   current.orient.Turn(Vec3(yaw , 0 , 0) , 1.0);
   
   /// X coord is w*sin(t*PI/2)
   /// Y coord is h*sin(t*PI/2)
   /// Y coord is forward movement
   /// X coord is lateral movement
   
   return current;
}



double Turn::CalcLength() {
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



SpatialInfo CurvedTrack::Eval(const SpatialInfo& start , double pct) {
   if (pct <= 0.0) {return start;}
   if (pct > 1.0) {pct = 1.0;}
   
   /// First find the radius of the curve
   EAGLE_ASSERT(t != 0.0);
   
   const double radius = l/fabs(t);
   
   const double yaw = t*pct*cos(r);
   const double pitch = t*pct*sin(r);

   SpatialInfo current = start;
   
   Orient o = start.orient;
   
   o.Turn(Vec3(yaw,pitch,0.0) , 1.0);
   
   Vec3 pos = start.pos;
   
   Vec3 fw = start.orient.Fw();
   Vec3 up = start.orient.Up();
   Vec3 rt = start.orient.Rt();
   
   up = Rotate3D(up , fw , r);
   rt = Rotate3D(rt , fw , r);

   Vec3 rad = rt*radius*((t < 0.0)?-1.0:1.0);
   Vec3 c = pos + rad;
   
   rad = Rotate3D(-rad , up , t*pct);
   
   Vec3 pos2 = c + rad;
   
   current.pos = pos2;
   current.orient = o;
   return current;
}




