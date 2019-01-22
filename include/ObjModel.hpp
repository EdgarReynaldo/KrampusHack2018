



#ifndef ObjModel_HPP
#define ObjModel_HPP


#include <string>
#include <vector>


#include "FileWork.hpp"
#include "Vec3.hpp"
#include "Mesh.hpp"

#include <string>
#include <map>




class Material {
   
protected :
   std::string matname;/// Material name
   
public :
   
///   Material(std::string name);
   Material(std::string name) : 
         matname(name),
         acol(1,1,1),
         dcol(1,1,1),
         scol(1,1,1),
         alpha(1.0),
         shine(0.0),
         illumination_model((unsigned int)-1),
         diffuse_texmap_fp(""),
         tid()
   {}
   
   Vec3 acol;/// Ka, ambient light color
   Vec3 dcol;/// Kd, diffuse light color
   Vec3 scol;/// Ks, specular light color
   double alpha;/// d, or 1.0 - Tr, d is opacity, Tr is translucency, alpha value
   double shine;/// Ns, shininess
   unsigned int illumination_model;/// illum, illumination model
   std::string diffuse_texmap_fp;/// map_Kd, diffuse texture map
   TexID tid;
};

class MaterialFile : protected TextFile {

   std::map<std::string , Material*> materialmap;

   TexLib texture_library;
   
   
   void ClearMaterials();
   void ClearTextures();
   void Clear();


   bool ProcessFile();

   
public :
   
//   MaterialFile();
   MaterialFile() :
         TextFile(),
         materialmap(),
         texture_library()
   {}
   
   bool Load(std::string filepath);
   bool Save(std::string filepath);

   Material* GetMaterial(std::string mat) {return materialmap[mat];}
   const std::map<std::string , Material*>& MatMap() {return materialmap;}
};

class ObjectFile : protected TextFile {
   
   std::map<std::string , MaterialFile*> matfiles;
   
   std::map<std::string , Mesh*> objects;
   
   
   
   void ClearMaterialFiles();
   void ClearObjects();

   void Clear();


   bool ProcessObjectFile();

public :
   
   ObjectFile() :
         TextFile(),
         matfiles(),
         objects()
   {}
   
   
   bool Load(std::string filepath);
   bool Save(std::string filepath);
};






#endif // ObjModel_HPP

