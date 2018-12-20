



#include "Track.hpp"
#include "Drawing.hpp"




bool Track::GeneratePath(double dz) {
   if (segments.empty()) {return false;}
   
   dz = fabs(dz);
   path.clear();
   double l = Length();
   double nseg = l/dz;
   if (nseg < 2.0) {nseg = 2.0;}
   const int N = ceil(nseg);
   for(int i = 0 ; i < N ; ++i) {
      /// How far along the track we are
      double l2 = i*l/N;
      /// Which track segment we are on
      int ntrack = 0;
      double l3 = l2;
      while (1) {
         const double l4 = segments[ntrack].Length();
         if (l4 <= l3) {
            l3 -= l4;
            ++ntrack;
         }
         else {
            break;
         }
      }
      /// How far along that track segment we are
      double pct = l3/segments[ntrack].Length();
      
      path.push_back(segments[ntrack].Eval(pct));
   }
   return true;
}



void Track::AddSegment(TrackSegment seg) {
   segments.push_back(seg);
}



bool Track::BuildTrack() {
   bool ret = GeneratePath(1.0);
   bounds = GetBoundingPrism();
   return ret;
}



void Track::Draw() {
   DrawTrackOutlines(*this);
}



double Track::Length() {
   double l = 0.0;
   for (unsigned int i = 0 ; i < segments.size() ; ++i) {
      l += segments[i].Length();
   }
   return l;
}



Prism Track::GetBoundingPrism() {
   const double BIGVAL = 1000000;
   double minx = BIGVAL;
   double miny = BIGVAL;
   double minz = BIGVAL;
   double maxx = -BIGVAL;
   double maxy = -BIGVAL;
   double maxz = -BIGVAL;
   for (unsigned int i = 0 ; i < path.size() ; ++i) {
      const Vec3& p = path[i].pos;
      const double& x = p.x;
      const double& y = p.y;
      const double& z = p.z;
      if (x < minx) {minx = x;}
      if (y < miny) {miny = y;}
      if (z < minz) {minz = z;}
      if (x > maxx) {maxx = x;}
      if (y > maxy) {maxy = y;}
      if (z > maxz) {maxz = z;}
   }
   return Prism(Vec3((minx + maxx)/2.0 , (miny + maxy)/2.0 , (minz + maxz)/2.0) , maxx - minx , maxy - miny , maxz - minz);
}



