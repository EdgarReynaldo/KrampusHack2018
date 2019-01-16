



#include "ObjModel.hpp" 
#include "FileWork.hpp"
#include "StringWork.hpp"



void TextFile::Clear() {
   fstr.clear();
   flines.clear();
}



bool TextFile::Load(std::string filepath) {
   Clear();
   fpath = filepath;
   if (!LoadTextFile(filepath , fstr)) {
      return false;
   }
   flines = SplitByNewLines(fstr);
   fstr.clear();
   return true;
}




