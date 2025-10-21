//
// Created by yitzk on 10/4/2025.
//

#ifndef STRINGUTIL_H
#define STRINGUTIL_H
#include <string>


/**
 * This namspace Orginizes all String utility functions that are not provided by the standerd library.
 */
namespace Util::StringUtil
{
    /**
  * @brief Replaces all occurrences of a specified substring within a string.
  *
  * This method finds all occurrences of the substring 'from' within 'str'
  * and replaces them with the string 'to'.
  *  @param str The string to modify. It is passed by reference and updated in place.
  * @param from The substring pattern to be replaced.
  * @param to The replacement string.
  */
    void replaceAll(std::string& str, const std::string& from, const std::string& to) ;
}

#endif //STRINGUTIL_H




