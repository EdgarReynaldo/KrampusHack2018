
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



#ifndef StringWork_H
#define StringWork_H


#include <vector>
#include <string>
#include <list>

/// TODO : Cleanup, organize

extern unsigned int STRINGPRINTF_BUFFER_SIZE;

#if defined __GNUC__
   #define PRINTF_FORMAT_STYLE __attribute__ ((format (printf, 1, 2)))
#else
   #define PRINTF_FORMAT_STYLE
#endif

std::string StringPrintF(const char* format_str , ...) PRINTF_FORMAT_STYLE;/// 1024 character limit!

int CountNewLines(std::string s);

std::vector<std::string> SplitByNewLines(std::string s);





#endif // StringWork_H


