



#ifndef CrossSection_HPP
#define CrossSection_HPP


#include "SpatialInfo.hpp"


#include <vector>
#include <memory>



class CrossSectionBase {
   
protected :
   SpatialInfo info;
   
   /** pts is a collection of points on the xy plane with up corresponding to up and right corresponding to right */
   std::vector<Vec3> pts;
   
   void Clear();
   
public :
   
   CrossSectionBase(const SpatialInfo& spatial_info);
   
   const SpatialInfo& Info() {return info;}
   const std::vector<Vec3>& Pts() {return pts;}
   const unsigned int N() {return pts.size();}
};



class CrossSection {
   std::shared_ptr<CrossSectionBase> sptr;
   
public :
//   CrossSection(CrossSectionBase* new_cs);
   CrossSection(CrossSectionBase* new_cs) : sptr(new_cs) {}
   
   const SpatialInfo& Info() {return sptr->Info();}
   const std::vector<Vec3>& Pts() {return sptr->Pts();}
   const unsigned int N() {return sptr->N();}
};





#endif // CrossSection_HPP
