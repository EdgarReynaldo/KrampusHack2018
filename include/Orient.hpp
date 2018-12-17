



#ifndef Orient_HPP
#define Orient_HPP




class Orient {
public :
   
   Vec3 fw,rt,up;
   
   Orient() : fw(),rt(),up() {}
   Orient(Vec3 vfw , Vec3 vrt , Vec3 vup) : fw(vfw) , rt(vrt) , up(vup) {}
   
};


 typedef Vec3 Turn;

class TurnMove {
public :
   Turn pos,vel,acc;
   
   TurnMove() : pos() , vel() , acc() {}
   TurnMove(Turn p) : pos(p) , vel() , acc() {}
   TurnMove(Turn p , Turn v , Turn a) : pos(p) , vel(v) , acc(a) {}
   
   
   TurnMove Future(double dt) const ;
   inline TurnMove Future(double dt) const {
      return TurnMove(pos + vel*dt + acc*0.5*dt*dt , acc*dt , acc);
   }
   
   void Update(double dt);
   void Update(double dt) {
      *this = Future(dt);
   }
};


Orient AlterPath(const Orient& o , const TurnMove& m);
Orient AlterPath(const Orient& o , const TurnMove& m) {
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



#endif // Orient_HPP
