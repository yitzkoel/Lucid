//
// Created by yitzk on 10/5/2025.
//

#ifndef FILEUTIL_H
#define FILEUTIL_H
#include <string>
#include <filesystem>

/**
 * This namspace Orginizes all file utility functions that are not provided by the standerd library.
 */
namespace Util::FileUtil  {
    /**
     * This method copies a file from srcPath to destPath.
     * This method will throws runtime_error.
     * @param srcPath is source path of file to be copied.
     * @param destPath is destenation path to copy the file to.
     */
    void copyFile(const std::string& srcPath, const std::string& destPath);


    /**
     * This method attemptd to delete the file in the path pathStr.
     * This method does not handle throws that might be thrown in the method implemention.
     * @param pathStr is path of file to be deleted.
     */
    void deleteFile(const std::string& pathStr);


} // Util

#endif //FILEUTIL_H
