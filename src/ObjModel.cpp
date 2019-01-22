



#include "ObjModel.hpp" 
#include "FileWork.hpp"
#include "StringWork.hpp"
#include <cstring>



void MaterialFile::ClearMaterials() {
   for (std::map<std::string , Material*>::iterator it = materialmap.begin() ; it != materialmap.end() ; ++it) {
      if (it->second) {
         delete it->second;
      }
   }
   materialmap.clear();
}



void MaterialFile::ClearTextures() {
   texture_library.Clear();
}



void MaterialFile::Clear() {
   ClearMaterials();
   ClearTextures();
}



bool MaterialFile::ProcessFile() {
   Clear();

   Material* cmat = 0;/// Current material
   
   bool error = false;
   
   const std::vector<std::string>& lines = Lines();
   for (unsigned int i = 0 ; i < lines.size() ; ++i) {
      const std::string& line = lines[i];
      if (!line.size())   {continue;}/// Empty lines
      if (line[0] == '#') {continue;}/// Comments
      
      if (strncmp(line.c_str() , "newmtl " , 7) == 0) {
         const char* name = line.c_str() + 7;
         std::map<std::string , Material*>::iterator it = materialmap.find(name);
         if (it != materialmap.end()) {
            cmat = it->second;
///            delete it->second;
         }
         else {
            Material* newmat = new Material(name);
            cmat = newmat;
            materialmap[name] = newmat;
         }
      }
      else if (strncmp(line.c_str() , "map_Kd " , 7) == 0) {
         cmat->diffuse_texmap_fp = line.c_str() + 7;
         cmat->tid = texture_library.TID(cmat->diffuse_texmap_fp);
      }
      else if (strncmp(line.c_str() , "Ka " , 3) == 0) {
         if (!ScanVec3(line.c_str() + 3 , cmat->acol)) {
            error = true;
         }
      }
      else if (strncmp(line.c_str() , "Kd " , 3) == 0) {
         if (!ScanVec3(line.c_str() + 3 , cmat->dcol)) {
            error = true;
         }
      }
      else if (strncmp(line.c_str() , "Ks " , 3) == 0) {
         if (!ScanVec3(line.c_str() + 7 , cmat->scol)) {
            error = true;
         }
      }
      else if (strncmp(line.c_str() , "d " , 2) == 0) {
         double opacity = -1.0;
         if (1 == sscanf(line.c_str() + 2 , "%lf" , &opacity)) {
            cmat->alpha = opacity;
         }
         else {
            error = true;
         }
      }
      else if (strncmp(line.c_str() , "Tr " , 3) == 0) {
         double trans = 0.0;
         if (1 == sscanf(line.c_str() + 3 , "%lf" , &trans)) {
            cmat->alpha = 1.0 - trans;
         }
         else {
            error = true;
         }
      }
      else if (strncmp(line.c_str() , "illum " , 6) == 0) {
         if (1 != sscanf(line.c_str() + 6 , "%d" , &cmat->illumination_model)) {
            error = true;
         }
      }
      else {
         printf("Unrecognized line in material file %s :\n%s\n" , Path().c_str() , line.c_str());
         error = true;
      }
   }
   if (error) {
      return false;
   }
   return true;
}



bool MaterialFile::Load(std::string filepath) {
   bool loaded = TextFile::Load(filepath);
   if (loaded) {
      loaded = ProcessFile();
   }
   return loaded;
}



bool MaterialFile::Save(std::string filepath) {
   return false;
}



void ObjectFile::ClearMaterialFiles() {
   std::map<std::string , MaterialFile*>::iterator it = matfiles.begin();
   while (it != matfiles.end()) {
      MaterialFile* mfile = it->second;
      if (mfile) {
         delete mfile;
      }
      ++it;
   }
   matfiles.clear();
}



void ObjectFile::ClearObjects() {
   std::map<std::string , Mesh*>::iterator it = objects.begin();
   while (it != objects.end()) {
      Mesh* mesh = it->second;
      if (mesh) {
         delete mesh;
      }
      ++it;
   }
   objects.clear();
}



void ObjectFile::Clear() {
   ClearMaterialFiles();
   ClearObjects();
}



bool ObjectFile::ProcessObjectFile() {
   
   MaterialFile* cmatlib = 0;/// Current material
   Mesh* cobjmesh = 0;
   
   bool error = false;
   int ecount = 0;
   
   const std::vector<std::string>& lines = Lines();
   for (unsigned int i = 0 ; i < lines.size() ; ++i) {
      const std::string& line = lines[i];
      if (!line.size())   {continue;}/// Empty lines
      if (line[0] == '#') {continue;}/// Comments
      
      if (strncmp(line.c_str() , "mtllib " , 7) == 0) {
         std::string fstr = line.c_str() + 7;
         std::map<std::string , MaterialFile*>::iterator it = matfiles.find(fstr);
         if (it == matfiles.end()) {
            MaterialFile* mf = new MaterialFile();
            if (!mf->Load(fstr)) {
               error = true;
               printf("Failed to load material file '%s'\n" , fstr.c_str());
               delete mf;
            }
            else {
               matfiles[fstr] = mf;
               cmatlib = mf;
            }
         }
      }
      else if (strncmp(line.c_str() , "o " , 2) == 0) {
         /// New object
         std::string objname = line.c_str() + 2;
         Mesh* objmesh = new Mesh();
         objects[objname] = objmesh;
         cobjmesh = objmesh;
      }
      else if (strncmp(line.c_str() , "v " , 2) == 0) {
         /// vertice = v x y z
         Vec3 xyz;
         if (!ScanVec3(line.c_str() + 2 , xyz)) {
            error = true;
         }
         else {
            cobjmesh->AddVertex(xyz);
         }
      }
      else if (strncmp(line.c_str() , "vn " , 3) == 0) {
         /// vertice normal = vn x y z
         
      }
      else if (strncmp(line.c_str() , "vt " , 3) == 0) {
         /// texture vertice = vt u v
         
      }
      
      if (error) {
         printf("Problem with line %d of file %s here :\n\t%s\n" , (int)i + 1 , Path().c_str() , line.c_str());
         ++ecount;
         error = false;
      }
   }
   return ecount == 0;
}



bool ObjectFile::Load(std::string filepath) {
   bool loaded = TextFile::Load(filepath);
   if (loaded) {
      loaded = ProcessObjectFile();
   }
   return loaded;
}



bool ObjectFile::Save(std::string filepath) {
   return false;
}






