



#include "Track.hpp"
#include "Drawing.hpp"


const double NSEGSWIDE = 10;
const double STARTING_DIAMETER = 50.0;

const Curve STARTING_CURVE = new Span(STARTING_DIAMETER);

const CrossSection STARTING_LINE = STARTING_CURVE.Generate(NSEGSWIDE);


/// ------------------------     TrackInfo      --------------------------------



TrackInfo::TrackInfo(const SpatialInfo& spatial_info , const CrossSection& cross_section) :
      info(START),
      csection(STARTING_LINE)
{
   Set(spatial_info , cross_section);
}



void TrackInfo::Set(const SpatialInfo& spatial_info , const CrossSection& cross_section) {
   info = spatial_info;
   csection = cross_section;
}



/// ------------------------     Track      --------------------------------


bool Track::GenerateTrack(double dz) {
   if (segments.empty()) {return false;}
   
   dz = fabs(dz);
   track.clear();
   const double l = Length();
   double nseg = l/dz;
   if (nseg < 2.0) {nseg = 2.0;}
   const int N = ceil(nseg);
   for(int i = 0 ; i < N ; ++i) {
      /// How far along the track we are
      double l2 = i*l/N;
      /// Which track segment we are on
      int ntrack = 0;
      double l3 = l2;
      double l4 = 0.0;
      while (1) {
         l4 = segments[ntrack].Length();
         if (l4 <= l3) {
            l3 -= l4;
            ++ntrack;
         }
         else {
            break;
         }
      }
      /// How far along that track segment we are
      double pct = l3/l4;
      
      track.push_back(TrackInfo(segments[ntrack].Eval(pct) , csgenerators[ntrack].Generate(NSEGSWIDE , pct)));
   }
   return true;
}



void Track::AddSegment(TrackSegment seg , CSG csgenerator) {
   const unsigned int NSEGS = segments.size();
   TrackInfo T;/// = START;
   if (NSEGS == 0) {
      csgenerator.SetStartingCurve(STARTING_CURVE);
   }
   else if (NSEGS > 0) {
      csgenerator.SetStartingCurve(csgenerators.back().FinishCurve());
      T = TrackInfo(segments.back().Eval(1.0) , csgenerators.back().Generate(NSEGSWIDE , 1.0));
   }
   seg.SetStart(T);
   segments.push_back(seg);
   csgenerators.push_back(csgenerator);
}



bool Track::BuildTrack() {
   bool ret = GenerateTrack(1.0);
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
   for (unsigned int i = 0 ; i < track.size() ; ++i) {
      const Vec3& p = track[i].Pos();
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



