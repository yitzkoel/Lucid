//
// Created by yitzk on 8/6/2025.
//

#ifndef HTMLEXTRACTOR_H
#define HTMLEXTRACTOR_H
#include <string>
#include <regex>
#include <curl/curl.h>
#include <iostream>
#include <fstream>

namespace ArticalScraper {

class HtmlExtractor {
public:



    /**
     * This methed sends a request from a website to the html and saves it to a local file.
     * This scaper handels only http and https requests and will return failure otherwise.
     * @param path A path to the website that holds the artical.
     * @return A path to a local directory that holds the articals html, returns empty string if fail.
     */
    const std::string websiteDownloader(const std::string& path);

    /**
     * This methods recieves a raw html in a txt file of a artical and removes all unessecery text.
     * The nessecery text are the artical, name of athor, subject(can be highrarical).
     * @param path
     */
    const std::string htmlDataExtractor(const std::string& path);

};

} // ArticalScraper

#endif //HTMLEXTRACTOR_H
