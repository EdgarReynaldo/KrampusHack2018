



#ifndef ObjModel_HPP
#define ObjModel_HPP


#include <string>
#include <vector>



class TextFile {
private :
   std::string fpath;
   std::string fstr;
   std::vector<std::string> flines;
   
   void Clear();
   
public :
   TextFile();
   
   bool Load(std::string filepath);
   
   const std::vector<std::string>& Lines() {return flines;}
};

class MaterialFile : protected TextFile {

};

class ObjectFile : protected TextFile {
   
   
///   bool LoadObjectFile
};






#endif // ObjModel_HPP

