



#ifndef FileWork_HPP
#define FileWork_HPP


#include <string>
#include <vector>



bool LoadTextFile(std::string filepath , std::string& fstr);

bool SaveTextFile(std::string filepath , const std::vector<std::string>& lines , bool append = false , bool overwrite = false);



#endif // FileWork_HPP

