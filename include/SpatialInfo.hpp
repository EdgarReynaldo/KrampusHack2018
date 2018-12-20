



#ifndef SpatialInfo_HPP
#define SpatialInfo_HPP



#include "Vec3.hpp"
#include "Orient.hpp"



class SpatialInfo {
   
public :
   Vec3 pos;
   Orient orient;
   
   SpatialInfo() : pos() , orient() {}
   SpatialInfo(Vec3 p , Orient o) : pos(p) , orient(o) {}
};



inline SpatialInfo START() {return SpatialInfo(ORIGIN() , Orient(Vec3(1,0,0) , Vec3(0,1,0) , Vec3(0,0,1)));}


#endif // SpatialInfo_HPP
