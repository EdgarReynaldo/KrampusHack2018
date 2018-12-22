



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
   
   const std::vector<SpatialInfo>& path = track.Path();
   for (unsigned int i = 0 ; i < path.size() - 1 ; ++i) {
         
      Prism p;
      p.SetCenter(path[i].pos);
      OutlinePrism(p , al_map_rgb(255,255,255));
         
      SpatialInfo p1 = path[i];
      SpatialInfo p2 = path[i+1];
      DrawLine(p1.pos , p2.pos , al_map_rgb(0,255,255));
   }
}









