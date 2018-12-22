



#ifndef TrackGen_HPP
#define TrackGen_HPP


#include "SpatialInfo.hpp"



class StraightAway {
protected :
   double l;
public :
   StraightAway(double length) : l(fabs(length)) {}
   
   SpatialInfo Eval(const SpatialInfo& start , double pct);
   
   double Length() {return l;}
};


/**
   A turn is a change in yaw, relative to the local axis
*/
class Turn {

double w,h,l;
   
   double CalcLength();
   
public :
   
   Turn(double width , double height) : w(width) , h(fabs(height)) , l(CalcLength()) {}
   
   
   SpatialInfo Eval(const SpatialInfo& start , double pct);
   double Length() {return l;}

};

class Curve {
   
   double l;
   double t;
   double r;
   
public :   
   Curve(double turn , double roll , double length) : l(abs(length)) , t(turn) , r(roll) {}
   
   
   SpatialInfo Eval(const SpatialInfo& start , double pct);
   double Length() {return l;}
};




#endif // TrackGen_HPP

