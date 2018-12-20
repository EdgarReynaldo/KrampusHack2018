



#include "Orient.hpp"



Orient AlterPath(const Orient& o , const Vec3& m) {
   Vec3 fw = o.fw;
   Vec3 rt = o.rt;
   Vec3 up = o.up;
   /// Yaw rotates around the y axis pointing up
   
   fw = Rotate3D(fw , up , m.yaw);
   rt = Rotate3D(rt , up , m.yaw);
   
   /// Pitch rotates around the x axis pointing right
   
   fw = Rotate3D(fw , rt , m.pitch);
   up = Rotate3D(up , rt , m.pitch);
   
   /// Roll rotates around the z axis pointing forward
   
   rt = Rotate3D(rt , fw , m.roll);
   up = Rotate3D(up , fw , m.roll);
   
   return Orient(fw,rt,up);
}
