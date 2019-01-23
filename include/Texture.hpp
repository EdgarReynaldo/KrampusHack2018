



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


   inline bool operator!=(const TexID& tid) {return (this->tid != tid.tid) && (this->bmp != tid.bmp);}
};


extern const TexID BAD_TEXID;


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
   TextureVertex(TexID texid , Vec2 tuv) :
         tid(texid),
         uv(tuv)
   {}

   TexID tid;
   
   Vec2 uv;///double u,v;
   
   
   
};

typedef TextureVertex TEXTEX;




#endif // Texture_HPP
