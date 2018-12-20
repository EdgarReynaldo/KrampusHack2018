



#ifndef Orient_HPP
#define Orient_HPP

#include "Vec3.hpp"


class Orient {
public :
   
   Vec3 fw,rt,up;
   
   Orient() : fw(0.0 , 0.0 , 1.0) , rt(0 , 0 , 0) , up(0 , 0 , 0) {}
   Orient(Vec3 vfw , Vec3 vrt , Vec3 vup) : fw(vfw) , rt(vrt) , up(vup) {}
   
};


class TurnMove {
public :
   Vec3 pos,vel,acc;
   
   TurnMove() : pos() , vel() , acc() {}
   TurnMove(Vec3 p) : pos(p) , vel() , acc() {}
   TurnMove(Vec3 p , Vec3 v , Vec3 a) : pos(p) , vel(v) , acc(a) {}
   
   
   inline TurnMove Future(double dt) const {
      return TurnMove(pos + vel*dt + acc*0.5*dt*dt , acc*dt , acc);
   }
   
   void Update(double dt) {
      *this = Future(dt);
   }
};


Orient AlterPath(const Orient& o , const Vec3& m);



#endif // Orient_HPP
