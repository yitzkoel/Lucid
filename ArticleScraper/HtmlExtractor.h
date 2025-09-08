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

#include "../ArticalProcessing/Artical.h"

namespace ArticalScraper
{
    class HtmlExtractor
    {
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
         * It keeps the fallowing data (in this order):
         *
         * In JSON  <script type=\"application/ld+json\"> ... <\script> form:
         * 1.Link to page.
         * 2.Name of author.
         * 3.Headline.
         * 4.Publish date.
         * 5.Publisher information.
         *
         * In paragraph form the artical text <p>....<\p>
         * @param path  the path to the downlaoded html file.
         * @return A path to the reformated file please note that it is the same path as the input path.
         */
        const std::string htmlDataExtractorToFile(const std::string& path);
        ArticalProcessing::Artical& htmlDataExtractorToArtical(const std::string& path);

    };
} // ArticalScraper

#endif //HTMLEXTRACTOR_H
