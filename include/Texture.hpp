



#ifndef Texture_HPP
#define Texture_HPP

#include <map>
#include <string>

struct ALLEGRO_BITMAP;

class TexID {
   
public :
   GLuint tid;
   ALLEGRO_BITMAP* bmp;
};


class TexLib {
   
public :
   std::map<std::string , TexID> texlib;
};


class TextureVertex {
public :

///   TextureVertex(ALLEGRO_BITMAP* tex , Vec2 tuv);
   TextureVertex(ALLEGRO_BITMAP* tex , Vec2 tuv) :
         bmp(tex),
         uv(tuv)
   {}

   ALLEGRO_BITMAP* bmp;
   Vec2 uv;///double u,v;
   
   
   
};

typedef TextureVertex TEXTEX;




#endif // Texture_HPP
