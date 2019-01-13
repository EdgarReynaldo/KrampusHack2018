



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



SpatialInfo Track::GetRealInfoFromLocal(const SpatialInfo& info , const Vec2& csxy , const double& roll);
   
   const Vec3& pos = info.pos;
   const Orient& o = info.orient;
   
   Vec3 realpos = pos + csxy.x*o.Rt() + csxy.y*o.Up();
   Orient realo = o;
   o.TurnLocal(Vec3(0,0,roll) , 1.0);
   
   return SpatialInfo(realpos , o);
}



void Track::ClearMeshes() {
   uppermesh.ClearAll();
   lowermesh.ClearAll();
   sidemesh.ClearAll();
}



double Track::CalcLength() {
   length = 0.0;
   for (unsigned int i = 0 ; i < segments.size() ; ++i) {
      length += segments[i].Length();
   }
   return length;
}



bool Track::GenerateTrack(double dz) {
   if (segments.empty()) {return false;}
   
   dz = fabs(dz);
   track.clear();
   const double l = CalcLength();
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




bool Track::GenerateTrackMesh() {
   
   ClearMeshes();
   
   assert(track.size() > 1);
   
   for (unsigned int i1 = 0 ; i1 < track.size() - 1 ; ++i1) {

      const TrackInfo& tinfo1 = track[i1];
      const TrackInfo& tinfo2 = track[i1+1];
   
      const SpatialInfo& info1 = tinfo1.Info();
      const SpatialInfo& info2 = tinfo2.Info();
      
      const Vec3& tpos1 = info1.pos;
      const Vec3& tpos2 = info2.pos;
      
      const Orient& torient1 = info1.orient;
      const Orient& torient2 = info2.orient;

      const CrossSection& cs1 = tinfo1.CSection();
      const CrossSection& cs2 = tinfo2.CSection();
   
      const std::vector<Vec2>&   xypts1 = cs1.XYPts();
      const std::vector<double>& ldist1 = cs1.LatDist();
      const std::vector<double>& rvals1 = cs1.RollValues();

      const std::vector<Vec2>&   xypts2 = cs2.XYPts();
      const std::vector<double>& ldist2 = cs2.LatDist();
      const std::vector<double>& rvals2 = cs2.RollValues();
   
      
      assert(xypts1.size() == NSEGSWIDE + 1);
      assert(xypts2.size() == NSEGSWIDE + 1);
      
      for (unsigned int i2 = 0 ; i2 < NSEGSWIDE ; ++i2) {
         const Vec2& xy1a = xypts1[i2];
         const Vec2& xy1b = xypts1[i2+1];
         const Vec2& xy2a = xypts2[i2];
         const Vec2& xy2b = xypts2[i2+1];
         
         const SpatialInfo rinfo1a = GetRealInfoFromLocal(info1 , xy1a , rvals1[i2]);
         const SpatialInfo rinfo1b = GetRealInfoFromLocal(info1 , xy1b , rvals1[i2 + 1]);
         const SpatialInfo rinfo2a = GetRealInfoFromLocal(info2 , xy2a , rvals2[i2]);
         const SpatialInfo rinfo2b = GetRealInfoFromLocal(info2 , xy2b , rvals2[i2 + 1]);
         
         const Vec3 dnlocal1a = -rinfo1a.orient.Up();
         const Vec3 dnlocal1b = -rinfo1b.orient.Up();
         const Vec3 dnlocal2a = -rinfo2a.orient.Up();
         const Vec3 dnlocal2b = -rinfo2b.orient.Up();
         
         const Vec3 zrinfo1a = rinfo1a.pos + dnlocal1a*TRACK_THICKNESS;
         const Vec3 zrinfo1b = rinfo1b.pos + dnlocal1b*TRACK_THICKNESS;
         const Vec3 zrinfo2a = rinfo2a.pos + dnlocal2a*TRACK_THICKNESS;
         const Vec3 zrinfo2b = rinfo2b.pos + dnlocal2b*TRACK_THICKNESS;
         
         const ALLEGRO_COLOR col = al_map_rgba(255,255,255,255);
         
         const VERTEX vtx[8] = {
            Vertex(rinfo1a.pos , col),
            Vertex(rinfo1b.pos , col),
            Vertex(rinfo2b.pos , col),
            Vertex(rinfo2a.pos , col),
            Vertex(zrinfo1a , col),
            Vertex(zrinfo1b , col),
            Vertex(zrinfo2b , col),
            Vertex(zrinfo2a , col),
         }
         
         const double x1a = ldist1[i2];
         const double x1b = ldist1[i2 + 1];
         const double x2a = ldist2[i2];
         const double x2b = ldist2[i2 + 1];
         
         const double y1 = Length()*(double)( i )/(double)(track.size() - 2);
         const double y2 = Length()*(double)(i+1)/(double)(track.size() - 2);
         
         const Vec2 uv[4] = {
            Vec2(x1a , y1),
            Vec2(x1b , y1),
            Vec2(x2b , y2),
            Vec2(x2a , y2)
         };
         
         const TEXTEX texvtx[4] = {
            TextureVertex(trackbmp , uv[0]),
            TextureVertex(trackbmp , uv[1]),
            TextureVertex(trackbmp , uv[2]),
            TextureVertex(trackbmp , uv[3])
         };
         
         /// Side mesh
         
         const ALLEGRO_COLOR sidecol = al_map_rgba(255,255,0,255);
         
         /// Front 
         if ((i1 == 0) && (i2 == 0)) {
            unsigned int v0 = sidemesh.AddVertex(VERTEX(vtx[3].pos , sidecol));
            unsigned int v1 = sidemesh.AddVertex(VERTEX(vtx[7].pos , sidecol));
            unsigned int v2 = sidemesh.AddVertex(VERTEX(vtx[4].pos , sidecol));
            unsigned int v3 = sidemesh.AddVertex(VERTEX(vtx[0].pos , sidecol));
            sidemesh.AddFlatQuadFace(v0,v1,v2,v3);
         }
         /// Back
         else if ((i1 == (track.size() - 2)) && (i2 == 0)) {
            unsigned int v0 = sidemesh.AddVertex(VERTEX(vtx[1].pos , sidecol));
            unsigned int v1 = sidemesh.AddVertex(VERTEX(vtx[5].pos , sidecol));
            unsigned int v2 = sidemesh.AddVertex(VERTEX(vtx[6].pos , sidecol));
            unsigned int v3 = sidemesh.AddVertex(VERTEX(vtx[2].pos , sidecol));
            sidemesh.AddFlatQuadFace(v0,v1,v2,v3);
         }
         
         /// Sides
         
         /// Left
         if (i2 == 0) {
            unsigned int v0 = sidemesh.AddVertex(VERTEX(vtx[3].pos , sidecolor));
            unsigned int v1 = sidemesh.AddVertex(VERTEX(vtx[7].pos , sidecolor));
            unsigned int v2 = sidemesh.AddVertex(VERTEX(vtx[4].pos , sidecolor));
            unsigned int v3 = sidemesh.AddVertex(VERTEX(vtx[0].pos , sidecolor));
            sidemesh.AddFlatQuadFace(v0 , v1 , v2 , v3);
         }
         /// Right
         else if (i2 == NSEGSWIDE - 1) {
            unsigned int v0 = sidemesh.AddVertex(VERTEX(vtx[1].pos , sidecolor));
            unsigned int v1 = sidemesh.AddVertex(VERTEX(vtx[5].pos , sidecolor));
            unsigned int v2 = sidemesh.AddVertex(VERTEX(vtx[6].pos , sidecolor));
            unsigned int v3 = sidemesh.AddVertex(VERTEX(vtx[2].pos , sidecolor));
            sidemesh.AddFlatQuadFace(v0 , v1 , v2 , v3);
         }
         
         /// Top and bottom meshes
         
         for (unsigned int n = 0 ; n < 4 ; ++n) {
            uppermesh.AddVertex(vtx[n]);
            lowermesh.AddVertex(vtx[n+4]);
         }
         
         for (unsigned int n = 0 ; n < 4 ; ++n) {
            uppermesh.AddEdge(n , (n+1)%4);
            lowermesh.AddEdge((n+4) , 4 + (n+1)%4);
         }
         
         
         
      }
      
   }
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
   bool ret = GenerateTrack(5.0);
   ret = ret && GenerateTrackMesh();
   bounds = GetBoundingPrism();
   return ret;
}



void Track::Draw() {
   DrawTrackOutlines(*this);
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



