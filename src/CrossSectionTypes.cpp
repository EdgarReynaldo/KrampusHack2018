



#include "CrossSectionGen.hpp"


#include <cassert>


#include "allegro5/allegro_primitives.h"








CrossSection CrossSectionBase::Generate(const unsigned int NSEGS) {
   assert(NSEGS > 0);

   const unsigned int NPOINTS = NSEGS + 1;
   
   CrossSection cs;
   for (unsigned int i = 0 ; i < NPOINTS ; ++i) {
      double pct = (double)i/(NPOINTS-1);
      cs.AddPoint(XYPosition(pct) , Roll(pct));
   }
   return cs;
}






/// --------------------------     Arc     ----------------------------------



/**
CrossSection Arc::Generate(const unsigned int NSEGS) {
   
   const unsigned int NPOINTS = NSEGS + 1;

   /// Calculate XY coords of cross section
   /// void al_calculate_arc (float* dest, int stride, float cx, float cy, float rx, float ry,
   ///                        float start_theta, float delta_theta, float thickness, int num_points);

   float coords[NPOINTS][2] = {0.0f};
   al_calculate_arc(&coords[0][0] , 2*sizeof(float) , 0 , 0 , hrad , vrad , tstart , tdelta , 0.0f , NPOINTS);

   CrossSection cs;
   for (unsigned int i = 0 ; i < NPOINTS ; ++i) {
      cs.AddPoint(Vec3(coords[i][0] , coords[i][1] - ypos , 0.0));
   }
   return cs;
}
//*/



ArcBase::ArcBase(double hdiameter , double vradius , double ycenter , double theta_width) :
      hrad(fabs(hdiameter/2.0)),
      vrad(fabs(vradius)),
      tstart(0.0),
      tcenter(0.0),
      twidth(0.0),
      ypos(ycenter)
{
   twidth = fabs(theta_width);
   if (twidth > 2.0*M_PI) {
      twidth = 2.0*M_PI;
   }
   if (ycenter > 0.0) {
      /// open bowl
      tcenter = -M_PI/2.0;
   }
   else {
      /// mound
      tcenter = M_PI/2.0;
   }
}



Vec3 ArcBase::XYPosition(double xpct) const {
   if (xpct < -1.0) {xpct = -1.0;}
   if (xpct > 1.0) {xpct = 1.0;}
   if (ypos > 0.0) {xpct = -xpct;}
   double theta = tcenter + xpct*twidth/2.0;
   return Vec3(hrad*cos(theta) , vrad*sin(theta) - ypos , 0);
}



double ArcBase::Roll(double xpct) const {
   if (xpct < -1.0) {xpct = -1.0;}
   if (xpct > 1.0) {xpct = 1.0;}
   if (ypos > 0.0) {xpct = -xpct;}
   return xpct*twidth/2.0;/// TODO : This is only true for circular shapes, not ellipsis FIXME
}



/// -----------------------------     Ring      --------------------------------------



Ring::Ring(double ycenter , double radius) :
      ArcBase(radius*2.0 , radius , ycenter , 2.0*M_PI),
      rad(radius)
{}



Tunnel::Tunnel(double radius) :
      Ring(-radius , radius)
{}



Mound::Mound(double radius) :
      Ring(radius , radius)
{}



/// -------------------------------     CurvedSpan      --------------------------------



CurvedSpan::CurvedSpan(double hdiameter , double deltay) :
      ArcBase(hdiameter , fabs(deltay) , deltay , M_PI)
{}



HalfPipe::HalfPipe(double hradius , double vradius) :
      CurvedSpan(hradius , fabs(vradius))
{}



HalfMound::HalfMound(double hradius , double vradius) :
      CurvedSpan(hradius , -fabs(vradius))
{}



/// -----------------------------        Span      ---------------------------------------



Span::Span(double width) :
      ArcBase(width , 0 , 0 , M_PI),
      w(width)
{}


/*
Vec3 Span::XYPosition(double xpct) {
   if (xpct < -1.0) {xpct = -1.0;}
   if (xpct > 1.0) {xpct = 1.0;}
   return Vec3(xpct*w/2.0 , 0 , 0);
}



double Span::Roll(double xpct) {
   return 0.0;
}
*/

