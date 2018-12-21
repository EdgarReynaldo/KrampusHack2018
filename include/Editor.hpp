



#ifndef Editor_HPP
#define Editor_HPP


#include "Scene.hpp"
#include "Camera.hpp"
#include "Track.hpp"
#include "TrackGen.hpp"



class Editor : public Scene {

protected :
   Camera cam;
   Track track;
   
   double cam_speed;
   double cam_turn_rate;
   
   
public :
   
//   Editor();
   Editor();
   
   virtual STATUS HandleEvent(ALLEGRO_EVENT ev);
   virtual void Display();
   virtual STATUS Update(double dt);
};



#endif // Editor_HPP

