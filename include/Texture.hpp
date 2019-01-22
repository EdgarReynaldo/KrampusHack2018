



#ifndef Texture_HPP
#define Texture_HPP

#include <map>
#include <string>

#include "Vec2.hpp"

#include "GL/gl.h"


struct ALLEGRO_BITMAP;

class TexID {
   
public :
   GLuint tid;
   ALLEGRO_BITMAP* bmp;
   
   TexID();
   
   TexID(ALLEGRO_BITMAP* tex);


};


class TexLib {
   
   std::map<std::string , TexID> texlib;

public :
   
   TexLib() : texlib() {}
   ~TexLib() {Clear();}
   
   void Clear();
   
   TexID LoadTexture(std::string image_file);

   const TexID& TID(std::string texname);


};


class TextureVertex {
public :

///   TextureVertex(ALLEGRO_BITMAP* tex , Vec2 tuv);
   TextureVertex(ALLEGRO_BITMAP* tex , Vec2 tuv) :
         tid(tex),
         uv(tuv)
   {}

   TexID tid;
   
   Vec2 uv;///double u,v;
   
   
   
};

typedef TextureVertex TEXTEX;




#endif // Texture_HPP
