



#include "Editor.hpp"
#include "BasicAllegro.hpp"



Editor::Editor() : 
      Scene(),
      cam(),
      track()
{
///   track.AddSegment(TrackSegment(new TrackSegmentGenerator<Curve>(START() , Curve(2.0*M_PI , M_PI , 100.0))));
///   track.AddSegment(TrackSegment(new TrackSegmentGenerator<Curve>(START() , Curve(-2.0*M_PI , M_PI , 100.0))));
   
   track.AddSegment(TrackSegment(new TrackSegmentGenerator<StraightAway>(StraightAway(100.0))));
   track.AddSegment(TrackSegment(new TrackSegmentGenerator<Turn>(Turn(-50 , 150))));
   track.AddSegment(TrackSegment(new TrackSegmentGenerator<Turn>(Turn(150 , 50))));
   track.AddSegment(TrackSegment(new TrackSegmentGenerator<Curve>(Curve(-M_PI , 0.0 , 315))));
   
   
   
   if (!track.BuildTrack()) {
      printf("Failed to build track.\n");
   }
}



STATUS Editor::HandleEvent(ALLEGRO_EVENT ev) {
   if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      return STATUS_QUIT;
   }
   if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
      return STATUS_QUIT;
   }
   return STATUS_OK;
}



void Editor::Display() {
   cam.ResetCamera();
   track.Draw();
   redraw = false;
}



STATUS Editor::Update(double dt) {
   if (dt > 0.0) {redraw = true;}
   return STATUS_OK;
}
