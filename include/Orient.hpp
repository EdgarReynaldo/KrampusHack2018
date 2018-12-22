



#ifndef Orient_HPP
#define Orient_HPP

#include "Vec3.hpp"


class Orient {

protected :
   Vec3 theta;/// yaw,pitch,roll
   
   Vec3 fw,rt,up;

   void CalcAxes();
   
public :
   
   
   Orient() : theta(0,0,0) , fw(FORWARD) , rt(RIGHT) , up(UP) {}
   Orient(Vec3 angle) : theta(angle) , fw(FORWARD) , rt(RIGHT) , up(UP) {}
   
   void SetTheta(Vec3 t) {theta = t;CalcAxes();}
   
   void Turn(Vec3 omega , double dt);
   
   inline Vec3 Fw() const {return fw;}
   inline Vec3 Rt() const {return rt;}
   inline Vec3 Up() const {return up;}
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



#endif // Orient_HPP
