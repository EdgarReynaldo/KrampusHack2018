



#include "FileWork.hpp"


bool LoadTextFile(std::string filepath , std::string& fstr) {
   
   bool ret = false;
   
   FILE* f = fopen(filepath.c_str() , "rb");
 
   if (f) {
      unsigned int count = 0;
      while (fgetc(f) != EOF) {++count;}
      
      if (count) {
         fseek(f , 0 , SEEK_SET);
         fstr = std::string();
         fstr.reserve(count);
         if (count == fread(&fstr[0] , sizeof(char) , count , f)) {
            ret = true;
         }
      }
      fclose(f);
   }
   
   return ret;
}



bool SaveTextFile(std::string filepath , const std::vector<std::string>& lines , bool append , bool overwrite) {
   if (!overwrite)
   {
      FILE* f = fopen(filepath.c_str() , "r");
      if (f) {
         fclose(f);
         return false;
      }
   }
   const char* flags = "w";
   if (append) {flags = "w+";}
   
   bool ret = true;
   FILE* f = fopen(filepath.c_str() , flags);
   if (f) {
      for (unsigned int i = 0 ; i < lines.size() ; ++i) {
         if (lines[i].size() != fwrite(&lines[i][0] , sizeof(char) , lines[i].size() , f)) {
            ret = false;
            break;
         }
         fprintf(f , "\n");
      }
      fclose(f);
   }
   return ret;
}

