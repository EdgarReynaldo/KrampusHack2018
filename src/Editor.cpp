



#include "Editor.hpp"
#include "BasicAllegro.hpp"
#include "Input.hpp"



Editor::Editor() : 
      Scene(),
      cam(),
      track(),
      cam_speed(100.0),
      cam_turn_rate(2.0*M_PI/5.0)
{
///   track.AddSegment(TrackSegment(new TrackSegmentGenerator<Curve>(START() , Curve(2.0*M_PI , M_PI , 100.0))));
///   track.AddSegment(TrackSegment(new TrackSegmentGenerator<Curve>(START() , Curve(-2.0*M_PI , M_PI , 100.0))));
   
///   track.AddSegment(TrackSegment(new TrackSegmentGenerator<Curve>(Curve(-M_PI , -M_PI/2.0 , 315))));
   track.AddSegment(TrackSegment(new TrackSegmentGenerator<StraightAway>(StraightAway(100.0))));
   track.AddSegment(TrackSegment(new TrackSegmentGenerator<Turn>(Turn(-50 , 150))));
   track.AddSegment(TrackSegment(new TrackSegmentGenerator<Turn>(Turn(150 , 50))));
   
   
   
   if (!track.BuildTrack()) {
      printf("Failed to build track.\n");
   }
}



STATUS Editor::HandleEvent(ALLEGRO_EVENT ev) {
   STATUS s = Scene::HandleEvent(ev);
   if (s == STATUS_QUIT) {return s;}
   
   /// INPUT HANDLING
   if (ev.type == ALLEGRO_EVENT_TIMER) {
      /// X movement
      if (keys[ALLEGRO_KEY_LEFT] || keys[ALLEGRO_KEY_RIGHT]) {
         cam.Move(Vec3((keys[ALLEGRO_KEY_LEFT])?-cam_speed:cam_speed , 0 , 0) , SPT);
      }
      /// Y movement
      if (keys[ALLEGRO_KEY_PGDN] || keys[ALLEGRO_KEY_PGUP]) {
         cam.Move(Vec3(0 , cam_speed*((keys[ALLEGRO_KEY_PGDN] || keys[ALLEGRO_KEY_RSHIFT])?-1:1) , 0) , SPT);
      }
      /// Z movement 
      if (keys[ALLEGRO_KEY_UP] || keys[ALLEGRO_KEY_DOWN]) {
         cam.Move(Vec3(0 , 0 , (keys[ALLEGRO_KEY_DOWN])?-cam_speed:cam_speed) , SPT);
      }
      /// YAW
      if (keys[ALLEGRO_KEY_PAD_4] || keys[ALLEGRO_KEY_PAD_6]) {
         cam.Turn(Vec3((keys[ALLEGRO_KEY_PAD_4]?-cam_turn_rate:cam_turn_rate) , 0 , 0) , SPT);
      }
      /// PITCH
      if (keys[ALLEGRO_KEY_PAD_2] || keys[ALLEGRO_KEY_PAD_8]) {
         cam.Turn(Vec3(0 , (keys[ALLEGRO_KEY_PAD_2]?-cam_turn_rate:cam_turn_rate) , 0) , SPT);
      }
      /// ROLL
      if (keys[ALLEGRO_KEY_PAD_7] || keys[ALLEGRO_KEY_PAD_9]) {
         cam.Turn(Vec3(0 , 0 , (keys[ALLEGRO_KEY_PAD_7]?-cam_turn_rate:cam_turn_rate)) , SPT);
      }
   }
   return STATUS_OK;
}



void Editor::Display() {
///   cam.SetPos(track.Bounds().Center());
   cam.Setup3D(false);
   track.Draw();
   
   Camera::Setup2D();
   Vec3 campos = cam.Pos();
   al_draw_textf(f , al_map_rgb(255,255,255) , 10 , sh - (10 + al_get_font_line_height(f)) , ALLEGRO_ALIGN_LEFT , 
                 "CamPos = %1.2lf , %1.2lf , %1.2lf" , campos.x , campos.y , campos.z);
   
   redraw = false;
}



STATUS Editor::Update(double dt) {
   if (dt > 0.0) {redraw = true;}
   return STATUS_OK;
}
