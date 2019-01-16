



#include "ObjModel.hpp" 
#include "FileWork.hpp"
#include "StringWork.hpp"
#include <cstring>



void MaterialFile::ClearMaterials() {
   for (std::map<std::string , Material*>::iterator it = materialmap.begin() ; it != materialmap.end() ; ++it) {
      delete it->second;
   }
   materialmap.clear();
}
   
bool MaterialFile::ProcessFile() {
   ClearMaterials();

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
      else if (strncmp(line.c_str() , "Ka " , 3) == 0) {
            
      }
      else if (strncmp(line.c_str() , "Kd " , 3) == 0) {
            
      }
      else if (strncmp(line.c_str() , "Ks " , 3) == 0) {
            
      }
      else if (strncmp(line.c_str() , "d " , 2) == 0) {
            
      }
      else if (strncmp(line.c_str() , "d " , 2) == 0) {
            
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



