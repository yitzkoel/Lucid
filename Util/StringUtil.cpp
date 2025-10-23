//
// Created by yitzk on 10/4/2025.
//

#include "StringUtil.h"

#include <regex>


namespace Util::StringUtil
{
#define MAX_PATH_LENGTH 95
    inline static const std::regex protocol{"^https?://"} ;
    inline static const std::regex invalid_chars {R"([%/:*?"<>|\\])"};

    void replaceAll(std::string& str, const std::string& from, const std::string& to)
    {
        size_t startPos = 0;
        while((startPos = str.find(from, startPos)) != std::string::npos) {
            str.replace(startPos, from.length(), to);
            startPos += to.length();
        }
    }

    std::string convet_URL_to_valid_path(const std::string& path)
    {
        std::string augmentedString = std::regex_replace(path, protocol, "");
        augmentedString = std::regex_replace(augmentedString, invalid_chars, "_");

        // Clean up multiple underscores
        std::regex multiple_underscores("_+");
        augmentedString = std::regex_replace(augmentedString, multiple_underscores, "_");

        if (augmentedString.length() > MAX_PATH_LENGTH)
        {
            augmentedString = augmentedString.substr(0,MAX_PATH_LENGTH);
        }

        return augmentedString + ".html";
    }
}
