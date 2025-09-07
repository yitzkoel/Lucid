#include <iostream>
#include <string>
#include <curl/curl.h>
#include "ArticleScraper/HtmlExtractor.h"



int main(int argc, char* argv[]) {
    ArticalScraper::HtmlExtractor handle;
    std::string path1;
    if(argc < 2) return EXIT_FAILURE;
    if(argc == 2){
        path1 = handle.websiteDownloader(argv[1]);
        if(!path1.empty()) {
            std::cout << "Successfully downloaded to: " << path1 << std::endl;
        } else {
            std::cerr << "Download failed!" << std::endl;
            return EXIT_FAILURE;
        }
    }


    std::string path2 = handle.htmlDataExtractor(path1);
    if(!path2.empty()) {
        std::cout << "Successfully extracted to: " << path2 << std::endl;
        return EXIT_SUCCESS;
    } else {
        std::cerr << "Download failed!" << std::endl;
        return EXIT_FAILURE;
    }
}
