//
// Created by yitzk on 10/5/2025.
//

#ifndef FILEUTIL_H
#define FILEUTIL_H
#include <string>
#include <filesystem>

namespace Util {

    void copyFile(const std::string& srcPath, const std::string& destPath);
    void deleteFile(const std::string& pathStr);


} // Util

#endif //FILEUTIL_H
