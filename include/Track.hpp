



#ifndef Track_HPP
#define Track_HPP

#include "Prism.hpp"
#include "SpatialInfo.hpp"
#include "CrossSection.hpp"
#include "CrossSectionGen.hpp"

#include <memory>
#include <vector>



class TrackInfo {
   
protected :
   SpatialInfo info;
   CrossSection csection;
public :
   
///   TrackInfo();
   TrackInfo() :
         info(START),
         csection()
   {}
   TrackInfo(const SpatialInfo& spatial_info , const CrossSection& cross_section);
   void Set(const SpatialInfo& spatial_info , const CrossSection& cross_section);
   
   SpatialInfo Info()      const {return info;}
   Vec3 Pos()              const {return info.pos;}
   Orient Orientation()    const {return info.orient;}
   double Width()          const {return csection.Width();}
   CrossSection CSection() const {return csection;}
   
};

class TrackSegmentBase {
   
protected :
   TrackInfo start;
public :
   TrackSegmentBase() : start() {}
   virtual ~TrackSegmentBase() {}
   
   void SetStart(const TrackInfo& info) {start = info;}

   virtual SpatialInfo Eval(double dt)=0;
   
   virtual double Length()=0;
};




template <class TGENERATOR>
class TSG : public TrackSegmentBase {
   
protected :
   TGENERATOR tg;
   double length;

public :
//   TSG(GENERATOR generator);
   
   TSG(TGENERATOR tgenerator) : 
         TrackSegmentBase(),
         tg(tgenerator),
         length(tgenerator.Length())
   {}
   
   SpatialInfo Eval(double dt);
   
   double Length() {return length;}
};





template<class TGENERATOR>
SpatialInfo TSG<TGENERATOR>::Eval(double dt) {
//   SpatialInfo info = tg.Eval(start.info , dt);
//   CrossSection cs = csg.Eval(start.csection , dt);
   return tg.Eval(start.Info() , dt);
}






class TrackSegment {
   
protected :
   std::shared_ptr<TrackSegmentBase> pgen;
   
public :
   TrackSegment(TrackSegmentBase* tbase) : pgen(tbase) {}
   
   void SetStart(const TrackInfo& tinfo) {pgen->SetStart(tinfo);}

   SpatialInfo Eval(double dt) {return pgen->Eval(dt);}
   
   double Length() {return pgen->Length();}
   
};



class Track {

protected :
   
   TrackInfo start;
   Prism bounds;
   
   std::vector<TrackSegment> segments;
   std::vector<CSG> csgenerators;
   std::vector<TrackInfo> track;



   bool GenerateTrack(double dz);
   
   Prism GetBoundingPrism();

public :
   
   Track() : start() , bounds() , segments() , track() {}
   
   void AddSegment(TrackSegment seg , CSG csgenerator);
   
   bool BuildTrack();
   
   void Draw();
   void DrawOutlines();
   
   const std::vector<TrackInfo>& TrackInfoVec() const {return track;}
   double Length();
   
   const Prism& Bounds() const {return bounds;}
};



#endif // Track_HPP





