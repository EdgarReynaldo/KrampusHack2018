
/*
 *
 *     _______       ___       ____      __       _______
 *    /\  ____\    /|   \     /  __\    /\ \     /\  ____\
 *    \ \ \___/_   ||  _ \   |  /__/____\ \ \    \ \ \___/_
 *     \ \  ____\  || |_\ \  |\ \ /\_  _\\ \ \    \ \  ____\
 *      \ \ \___/_ ||  ___ \ \ \ \\//\ \/ \ \ \____\ \ \___/_
 *       \ \______\||_|__/\_\ \ \ \_\/ |   \ \_____\\ \______\
 *        \/______/|/_/  \/_/  \_\_____/    \/_____/ \/______/
 *
 *
 *    EAGLE
 *    Edgar's Agile Gui Library and Extensions
 *
 *    Copyright 2009-2016+ by Edgar Reynaldo
 *
 *    See EagleLicense.txt for allowed uses of this library.
 *
 */



#include "Exception.hpp"
//#include "Eagle/Platform.hpp"
#include "StringWork.hpp"

#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <cstring>

using std::vector;
using std::string;
using std::list;




unsigned int STRINGPRINTF_BUFFER_SIZE = 1024;

   
string StringPrintF(const char* format_str , ...) {
   char buffer[STRINGPRINTF_BUFFER_SIZE];
   va_list args;
   va_start(args , format_str);
///int vsnprintf (char * s, size_t n, const char * format, va_list arg );
   vsnprintf(buffer , STRINGPRINTF_BUFFER_SIZE , format_str , args);
   va_end(args);
   return std::string(buffer);
}




int CountNewLines(std::string s) {
   int nlines = 1;
   for (unsigned int i = 0 ; i < s.length() ; i++) {
      char c = s[i];
      if (c == '\r' || c == '\n') {
         ++nlines;
         unsigned int i2 = i + 1;
         char c2 = (i2 < s.length())?s[i2]:'\0';
         if (c == '\r' && c2 == '\n') {
            ++i;
         }
      }
   }
   return nlines;
}



vector<string> SplitByNewLines(std::string s) {
   vector<string> lines;

   if (s.length() == 0) {
      lines.push_back("");
      return lines;
   }

   string line;
   for (unsigned int i = 0 ; i < s.length() ; ) {
      char c = s[i];
      if (c == '\r' || c == '\n') {

         lines.push_back(line);
         line = "";

         unsigned int i2 = i + 1;
         char c2 = (i2 < s.length())?s[i2]:'\0';
         if (c == '\r' && c2 == '\n') {
            ++i;
         }
      }
      else {
         line.push_back(c);
      }
      ++i;
      if (i == s.length() && line.length()) {
         lines.push_back(line);
      }
   }

   return lines;
}








