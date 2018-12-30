



#include "Drawing.hpp"




void OutlinePrism(const Prism& p , ALLEGRO_COLOR c) {
   
   Vec3 pts[4] = {
      p.TopLeftFront(),
      p.BotRightFront(),
      p.TopRightBack(),
      p.BotLeftBack()
   };
   
   Vec3 pts2[4][3] = {
      {
         p.TopRightFront(),
         p.BotLeftFront(),
         p.TopLeftBack()
      },
      {
         p.TopRightFront(),
         p.BotLeftFront(),
         p.BotRightBack()
      },
      {
         p.TopLeftBack(),
         p.BotRightBack(),
         p.TopRightFront(),
      },
      {
         p.TopLeftBack(),
         p.BotRightBack(),
         p.BotLeftFront()
      }
   };
   
   for (unsigned int i = 0 ; i < 4 ; ++i) {
      for (unsigned int j = 0 ; j < 3 ; ++j) {
         DrawLine(pts[i] , pts2[i][j] , c);
      }
   }
}



void DrawTrackOutlines(const Track& track) {
   OutlinePrism(track.Bounds() , al_map_rgb(255,255,255));
   
   const std::vector<TrackInfo>& trackpath = track.TrackInfoVec();
   for (unsigned int i = 0 ; i < trackpath.size() - 1 ; ++i) {
         
      Prism p;
      p.SetCenter(trackpath[i].Pos());
      OutlinePrism(p , al_map_rgb(255,255,255));
         
      Vec3 p1 = trackpath[i].Pos();
      Vec3 p2 = trackpath[i+1].Pos();
      DrawLine(p1 , p2 , al_map_rgb(0,255,255));
   }
}









