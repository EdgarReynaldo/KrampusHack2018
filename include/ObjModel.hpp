



#ifndef ObjModel_HPP
#define ObjModel_HPP


#include <string>
#include <vector>


#include "FileWork.hpp"
#include "Vec3.hpp"

#include <string>
#include <map>

class Material {
   
protected :
   std::string matname;/// Material name
   
public :
   
///   Material(std::string name);
   Material(std::string name) : 
         matname(name),
         acol(),
         dcol(),
         scol(),
         alpha(1.0),
         shine(0.0),
         illumination_model((unsigned int)-1),
         diffuse_texmap_fp()
   {}
   
   Vec3 acol;/// Ka, ambient light color
   Vec3 dcol;/// Kd, diffuse light color
   Vec3 scol;/// Ks, specular light color
   double alpha;/// d, or 1.0 - Tr, d is opacity, Tr is translucency, alpha value
   double shine;/// Ns, shininess
   unsigned int illumination_model;/// illum, illumination model
   std::string diffuse_texmap_fp;/// map_Kd, diffuse texture map
};

class MaterialFile : protected TextFile {

   std::map<std::string , Material*> materialmap;

   void ClearMaterials();
   bool ProcessFile();

   
public :
   
   bool Load(std::string filepath);
   bool Save(std::string filepath);
/**
bool MaterialFile::Load(std::string filepath) {
   bool loaded = TextFile::Load(filepath);
   if (loaded) {
      loaded = ProcessFile();
   }
   return loaded;
}
bool MaterialFile::Save(std::string filepath) {
   
}
*/
};

class ObjectFile : protected TextFile {
   
public :
   
   bool Load(std::string filepath);
   bool Save(std::string filepath);
/*
bool ObjectFile::Load(std::string filepath) {
   
}
bool ObjectFile::Save(std::string filepath) {
   
}
*/
};






#endif // ObjModel_HPP

