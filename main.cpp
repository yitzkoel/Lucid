#include <iostream>
#include <string>
#include <curl/curl.h>
#include "ArticleScraper/HtmlExtractor.h"



int main(int argc, char* argv[]) {
    if(argc < 2) return EXIT_FAILURE;

    ArticalScraper::HtmlExtractor handle;

    std::string path = handle.websiteDownloader(argv[1]);

    if(!path.empty()) {
        std::cout << "Successfully downloaded to: " << path << std::endl;
    } else {
        std::cerr << "Download failed!" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
