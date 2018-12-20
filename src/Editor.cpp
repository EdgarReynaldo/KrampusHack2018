



#include "Editor.hpp"
#include "BasicAllegro.hpp"



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
