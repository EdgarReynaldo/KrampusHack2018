



#ifndef CrossSection_HPP
#define CrossSection_HPP



#include <vector>
#include "Vec3.hpp"


class CrossSection {
protected :

   double lateral_width;/// lateral x width of track

   /** pts is a collection of points on the xy plane with up corresponding to up and right corresponding to right */
   std::vector<Vec3> xypts;
   std::vector<double> rvals;

public :
//   CrossSection(CrossSectionBase* new_cs);
   CrossSection() : lateral_width(0.0) , xypts() {}
   
   void Clear();

   void AddPoint(Vec3 xy , double roll);
   
   double Width() const {return lateral_width;}
   const std::vector<Vec3>& XYPts() const {return xypts;}
   unsigned int NPTS() const {return xypts.size();}

   Vec3 XYPosition(double xpct) const;/// pct is from [-1.0 , 1.0], represents how far along x - axis we are on the cross section
   double RollValue(double xpct) const;
};




#endif // CrossSection_HPP
