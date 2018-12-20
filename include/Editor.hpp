



#ifndef Editor_HPP
#define Editor_HPP


#include "Scene.hpp"
#include "Camera.hpp"
#include "Track.hpp"



class Editor : public Scene {

protected :
   Camera cam;
   Track track;
   
public :
   
   Editor() : Scene() , cam() , track() {
      track.AddSegment((TrackSegment(new TrackSegmentGenerator<Curve>()
   }
   
   virtual STATUS HandleEvent(ALLEGRO_EVENT ev);
   virtual void Display();
   virtual STATUS Update(double dt);
};



#endif // Editor_HPP

