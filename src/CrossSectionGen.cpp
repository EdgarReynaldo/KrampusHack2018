



#include "CrossSectionGen.hpp"


#include <cassert>


#include "allegro5/allegro_primitives.h"



void Span::GenerateSpan(const unsigned int NSEGS) {
   assert(NSEGS > 0);
   
   Clear();
   const unsigned int NPOINTS = NSEGS + 1;
   
   const Vec3 p1 = info.orient.Rt()*(-w/2.0);
   const Vec3 p2 = info.orient.Rt()*(w/2.0);
   const Vec3 dpos = p2 - p1;
   for (unsigned int i = 0 ; i < NPOINTS ; ++i) {
      double pct = (double)i/(NPOINTS-1);
      pts.push_back(p1 + pct*dpos);
   }
}



Span::Span(const SpatialInfo& spatial_info , double width , const unsigned int NSEGS) :
      CrossSectionBase(spatial_info),
      w(width)
{
   GenerateSpan(NSEGS);
}



/// --------------------------     Arc     ----------------------------------



void Arc::GenerateArc(const unsigned int NSEGS) {
   Clear();
   
   const Vec3 fw = info.orient.Fw();
   const Vec3 rt = info.orient.Rt();
   const Vec3 up = info.orient.Up();
   
   const unsigned int NPOINTS = NSEGS + 1;

   /// Calculate XY coords of cross section
   /// void al_calculate_arc (float* dest, int stride, float cx, float cy, float rx, float ry,
   ///                        float start_theta, float delta_theta, float thickness, int num_points);

   float coords[NPOINTS][2] = {0.0f};
   al_calculate_arc(coords , 2*sizeof(float) , 0 , 0 , width , height , tstart , tdelta , 0.0f , NPOINTS);

   /// Translate these xy coords to xyz
   for (unsigned int i = 0 ; i < NPOINTS ; ++i) {
      pts.push_back(up*coords[i][1] + rt*coords[i][0]);
   }
}



Arc::Arc(const SpatialInfo& spatial_info , double hradius , double vradius , double theta_start , double theta_delta , const unsigned int NSEGS) :
      CrossSectionBase(spatial_info),
      width(hradius*2.0),
      height(vradius*2.0),
      tstart(theta_start),
      tdelta(fmod(theta_delta , 2.0*M_PI))
{
   assert(NSEGS > 0);
   GenerateArc(NSEGS);
}



/// ---------------------------      HalfPipe     ------------------------------



HalfPipe::HalfPipe(SpatialInfo spatial_info , double hradius , double vradius , const unsigned int NSEGS) :
      Arc(hradius , vradius , 0.0*M_PI , M_PI , NSEGS)
{}




/// -----------------------------     Ring      --------------------------------------



Ring::Ring(SpatialInfo& spatial_info , double radius , const unsigned int NSEGS) :
      Arc(spatial_info , radius , radius , -M_PI/2.0 , 2.0*M_PI , NSEGS),
      rad(radius)
{}






