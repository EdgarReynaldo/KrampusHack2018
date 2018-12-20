



#ifndef Track_HPP
#define Track_HPP

#include "Prism.hpp"
#include "SpatialInfo.hpp"



#include <memory>
#include <vector>




class TrackSegmentBase {
   
   
public :
   TrackSegmentBase() {}
   
   virtual SpatialInfo Eval(double dt)=0;
   
   virtual double Length()=0;
};




template <class GENERATOR>
class TrackSegmentGenerator : public TrackSegmentBase {
   
protected :
   SpatialInfo start;
   GENERATOR g;
   double length;

public :
   TrackSegmentGenerator(SpatialInfo startpos , GENERATOR generator) : start(startpos) , g(generator) , length(generator.Length()) {}
   
   SpatialInfo Eval(double dt);
   
   double Length() {return length;}
};





template<class GENERATOR>
SpatialInfo TrackSegmentGenerator<GENERATOR>::Eval(double dt) {
   return g.Eval(start , dt);
}






class TrackSegment {
   
protected :
   std::shared_ptr<TrackSegmentBase> pgen;
   
public :
   TrackSegment(TrackSegmentBase* tbase) : pgen(tbase) {}
   
   SpatialInfo Eval(double dt) {return pgen->Eval(dt);}
   
   double Length() {return pgen->Length();}
   
};



class Track {

protected :
   
   SpatialInfo start;
   Prism bounds;
   
   
   std::vector<TrackSegment> segments;
   std::vector<SpatialInfo> path;

   bool GeneratePath(double dz);
   
   Prism GetBoundingPrism();

public :
   
   Track() : start() , bounds() , segments() , path() {}
   
   void AddSegment(TrackSegment seg);
   
   bool BuildTrack();
   
   void Draw();
   void DrawOutlines();
   
   const std::vector<SpatialInfo>& Path() const {return path;}
   double Length();
   
   const Prism& Bounds() const {return bounds;}
};



#endif // Track_HPP





