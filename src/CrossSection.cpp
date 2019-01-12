



#include "CrossSection.hpp"
#include "Interpolate.hpp"




void CrossSection::Clear() {
   xypts.clear();
   
}



void CrossSection::AddPoint(Vec2 xy , double lateral_distance , double roll) {
   if (NPTS()) {
      Vec2 p1 = xypts.back();
      double d = (xy - p1).Magnitude();
      lateral_width += d;
   }
   xypts.push_back(xy);
   latdist.push_back(lateral_distance);
   rvals.push_back(roll);
}



Vec2 CrossSection::XYPosition(double xpct) const {
   if (xpct < -1.0) {xpct = -1.0;}
   if (xpct > 1.0) {xpct = 1.0;}
   
   if (!NPTS()) {return Vec2(-1,-1);}
   
   if (NPTS() == 1) {
      return xypts[0];
   }

   const unsigned int NSEGS = NPTS() - 1;
   
   double pct = ((xpct + 1.0)/2.0)*(NSEGS);
   unsigned int index1 = (int)(floor(pct));
   double frac = fmod(pct , 1.0);
   if (index1 == NSEGS) {
      index1--;
      frac = 1.0;
   }
   return Interpolate(xypts[index1] , xypts[index1 + 1] , frac);
}



double CrossSection::LatDist(double xpct) const {
   if (xpct < -1.0) {xpct = -1.0;}
   if (xpct > 1.0) {xpct = 1.0;}
   
   if (!NPTS()) {return xpct;}
   
   if (NPTS() == 1) {
      return latdist[0];
   }

   const unsigned int NSEGS = NPTS() - 1;
   
   double pct = ((xpct + 1.0)/2.0)*(NSEGS);
   unsigned int index1 = (int)(floor(pct));
   double frac = fmod(pct , 1.0);
   if (index1 == NSEGS) {
      index1--;
      frac = 1.0;
   }
   return Interpolate(latdist[index1] , latdist[index1 + 1] , frac);
}



double CrossSection::RollValue(double xpct) const {
   if (xpct < -1.0) {xpct = -1.0;}
   if (xpct > 1.0) {xpct = 1.0;}
   
   if (!NPTS()) {return -M_PI;}
   
   if (NPTS() == 1) {
      return rvals[0];
   }

   const unsigned int NSEGS = NPTS() - 1;
   
   double pct = ((xpct + 1.0)/2.0)*(NSEGS);
   unsigned int index1 = (int)(floor(pct));
   double frac = fmod(pct , 1.0);
   if (index1 == NSEGS) {
      index1--;
      frac = 1.0;
   }
   return Interpolate(rvals[index1] , rvals[index1 + 1] , frac);
}




