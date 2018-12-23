



#ifndef CrossSectionGen_HPP
#define CrossSectionGen_HPP


#include "CrossSection.hpp"



/** A span spans a straight line on the local x-axis from pos + rt*(-w/2) to pos + rt*(w/2) */

class Span : public CrossSectionBase {
   double w;

   void GenerateSpan();
public :
   Span(const SpatialInfo& spatial_info , double width , const unsigned int NSEGS);
};



class Arc : public CrossSectionBase {

protected :
   double width;
   double height;
   double tstart;
   double tdelta;

   void GenerateArc(const unsigned int NSEGS);

public :
   
   
   Arc(const SpatialInfo& spatial_info , double hradius , double vradius , double theta_start , double theta_delta , const unsigned int NSEGS);
   
   
   
};


/** A halfpipe forms an open bowl on the local x-axis from pos + rt*(-rad/2) to pos + up*(-rad) to pos + rt*(rad/2) */

class HalfPipe : public Arc {

public :

   HalfPipe(SpatialInfo spatial_info , double hradius , double vradius , const unsigned int NSEGS);

};

/** A ring forms a circle on the xy plane. It's normal is the forward vector. */

class Ring : public Arc {

protected :
   double rad;

public :

   Ring(SpatialInfo& spatial_info , double radius , const unsigned int NSEGS);

};

#endif // CrossSectionGen_HPP
