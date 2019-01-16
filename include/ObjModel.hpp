



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
   Material(std::string name) : matname(name) {}
   
   Vec3 ambientlc;/// Ka
   Vec3 diffuselc;/// Kd
   Vec3 specularlc;/// Ks
   double alpha;/// d, or 1.0 - Tr
   double shine;/// Ns
   unsigned int illumination_model;/// illum
   std::string diffuse_texmap_fp;/// map_Kd
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

