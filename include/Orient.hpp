



#ifndef Orient_HPP
#define Orient_HPP

#include "Vec3.hpp"


class Orient {
public :
   
   Vec3 theta;/// yaw,pitch,roll
   
   Vec3 fw,rt,up;
   
   Orient() : theta(0,0,0) , fw(FORWARD) , rt(RIGHT) , up(UP) {}
   
   
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
