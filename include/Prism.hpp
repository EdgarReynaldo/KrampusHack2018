



#ifndef Prism_HPP
#define Prism_HPP





class Prism {
   
   Vec3 tlb;
   double w;
   double h;
   double d;
   
   Prism(Vec3 center , double width , double height , double depth) : tlb() , w(width) , h(height) , d(depth) {
      SetCenter(center);
   }
   
   inline double LeftX() {return tlb.x;}
   inline double RightX() {return tlb.x + w;}
   inline double TopY() {return tlb.y;}
   inline double BotY() {return tlb.y - h;}
   inline double BackZ() {return tlb.z;}
   inline double FrontZ() {return tlb.z - d;}
   
   inline Vec3 TopLeftBack()   {return Vec3(LeftX()  , TopY() , BackZ()  );}
   inline Vec3 TopLeftFront()  {return Vec3(LeftX()  , TopY() , FrontZ() );}
   inline Vec3 TopRightBack()  {return Vec3(RightX() , TopY() , BackZ()  );}
   inline Vec3 TopRightFront() {return Vec3(RightX() , TopY() , FrontZ() );}
   inline Vec3 BotLeftBack()   {return Vec3(LeftX()  , BotY() , BackZ()  );}
   inline Vec3 BotLeftFront()  {return Vec3(LeftX()  , BotY() , FrontZ() );}
   inline Vec3 BotRightBack()  {return Vec3(RightX() , BotY() , BackZ()  );}
   inline Vec3 BotRightFront() {return Vec3(RightX() , BotY() , FrontZ() );}
   
   inline void SetCenter(Vec3 c) {tlb = Vec3(c.x - w/2.0 , c.y - h/2.0 , c.z - d/2.0);}
   
};

#endif // Prism_HPP
