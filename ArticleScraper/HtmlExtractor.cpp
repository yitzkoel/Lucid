//
// Created by yitzk on 8/6/2025.
//

#include "HtmlExtractor.h"

std::string convet_URL_to_valid_path(const std::string& path)
{
    std::regex protocol("^https?://");
    std::regex invalid_chars(R"([/:*?"<>|\\])");  // All problematic characters

    std::string augmentedString = std::regex_replace(path, protocol,"");
    augmentedString = std::regex_replace(augmentedString, invalid_chars, "_");

    // Clean up multiple underscores
    std::regex multiple_underscores("_+");
    augmentedString = std::regex_replace(augmentedString, multiple_underscores, "_");


    return augmentedString + ".html";
}

/**
 *
 * @param path The URL path to be downloaded artical from.
 * This method checks that the path prefix is valid for the curl setting.
 * @return bool of result.
 */
bool isValidURL_Regex(const std::string& path)
{
    std::regex protocol("^https?://");
    return std::regex_search(path, protocol);
}



namespace ArticalScraper {
    const std::string HtmlExtractor::websiteDownloader(const std::string& path)
    {
        CURL* curl = curl_easy_init();
        if(!curl)
        {
            std::cerr << "failed to initialize curl" << "\n";
            return "";
        }

        if(!isValidURL_Regex(path))
        {
            std::cerr << "URL must include http or https prefix" << "\n";
            return "";
        }


        std::string filePath = convet_URL_to_valid_path(path);
        FILE* file = fopen(filePath.c_str(), "wb");

        if(!file)
        {
            std::cerr << "Failed to open file for writing: " << filePath << std::endl;
            curl_easy_cleanup(curl);
            return "";
        }

        //Transparent User-Agent to aprove scrape
        curl_easy_setopt(curl, CURLOPT_USERAGENT,
            "ArticleScraper/1.0 (Educational Purpose; Contact: yitzkoel@gmail.com)");
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "ArticleScraper Educational Tool");

        //Setting up the handle
        curl_easy_setopt(curl,CURLOPT_URL, path.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        CURLcode result = curl_easy_perform(curl);

        if(result != CURLE_OK)
        {
            std::cerr << "CURL error: " << curl_easy_strerror(result) << std::endl;
            std::cerr << "Failed to download from: " << path << std::endl;
            return "";
        }

        curl_easy_cleanup(curl);
        fclose(file);
        
        return filePath;
    }

    const void htmlDataExtractor(const std::string& path)
    {

    }
} // ArticalScraper