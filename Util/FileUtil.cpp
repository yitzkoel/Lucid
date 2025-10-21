//
// Created by yitzk on 10/5/2025.
//

#include "FileUtil.h"
#include <iostream>

namespace Util::FileUtil {
    namespace fs = std::filesystem;
    
    void copyFile(const std::string& srcPath, const std::string& destPath)
     {
         try {
             fs::path src(srcPath);
             fs::path dest(destPath);

             // if dest is a directory, append the filename from src
             if (fs::is_directory(dest)) {
                 dest /= src.filename();
             }

             fs::copy_file(src, dest, fs::copy_options::overwrite_existing);
         }
         catch (const fs::filesystem_error& e) {
             std::string errMsg = std::string(e.what()) + " | Bad destination path or file system error";
             throw std::runtime_error(errMsg);
         }
     }


     void deleteFile(const std::string& pathStr)
    {
        fs::path p(pathStr);
        fs::remove(p);
    }
} // Util