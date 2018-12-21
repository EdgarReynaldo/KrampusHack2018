



#ifndef Prism_HPP
#define Prism_HPP



#include "Vec3.hpp"



class Prism {
   
   Vec3 tlb;
   double w;
   double h;
   double d;
   
public :
   
   Prism() : tlb() , w(1) , h(1) , d(1) {
      SetCenter(Vec3(0,0,0));
   }
   
   Prism(Vec3 center , double width , double height , double depth) : tlb() , w(abs(width)) , h(abs(height)) , d(abs(depth)) {
      SetCenter(center);
   }
   
   inline double Width()  {return w;}
   inline double Height() {return h;}
   inline double Depth()  {return d;}
   
   inline double LeftX()  const {return tlb.x;    }
   inline double RightX() const {return tlb.x + w;}
   inline double TopY()   const {return tlb.y;    }
   inline double BotY()   const {return tlb.y - h;}
   inline double BackZ()  const {return tlb.z;    }
   inline double FrontZ() const {return tlb.z - d;}
   
   inline Vec3 TopLeftBack()   const {return Vec3(LeftX()  , TopY() , BackZ()  );}
   inline Vec3 TopLeftFront()  const {return Vec3(LeftX()  , TopY() , FrontZ() );}
   inline Vec3 TopRightBack()  const {return Vec3(RightX() , TopY() , BackZ()  );}
   inline Vec3 TopRightFront() const {return Vec3(RightX() , TopY() , FrontZ() );}
   inline Vec3 BotLeftBack()   const {return Vec3(LeftX()  , BotY() , BackZ()  );}
   inline Vec3 BotLeftFront()  const {return Vec3(LeftX()  , BotY() , FrontZ() );}
   inline Vec3 BotRightBack()  const {return Vec3(RightX() , BotY() , BackZ()  );}
   inline Vec3 BotRightFront() const {return Vec3(RightX() , BotY() , FrontZ() );}
   
   inline void SetCenter(Vec3 c) {tlb = Vec3(c.x - w/2.0 , c.y + h/2.0 , c.z + d/2.0);}
   inline Vec3 Center() const {return Vec3(tlb.x + w/2.0 , tlb.y - h/2.0 , tlb.z - d/2.0);}
};

#endif // Prism_HPP
