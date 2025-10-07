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
#include <memory>

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
        static std::string websiteDownloader(const std::string& path);

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
        static std::string htmlDataExtractorToFile(const std::string& path);


        static std::unique_ptr<ArticalProcessing::Artical> htmlDataExtractorToArtical(const std::string& path);

    private:
        //inline static const std::string pictureTag = "<picture\\s.*?</picture>";
        //inline static const std::string styleTag2 = "<style\\s.*?</style>";
        //inline static const std::string figcaptionTag = "<figcaption\\s.*?</figcaption>";
        inline static const std::string termsAndConditions = "<p class=\"terms-and-conditions-p\".*?</p>";
        inline static const std::string comentNotesTag = "<p class=\"comment-.*?\">.*?</p>";
        inline static const std::string styleTag1 = "<p style=\"display:.*?</p>";
        inline static const std::string acwp_title = "<p class=\"acwp-title\">.*?</p>";
        static const int NUM_OF_TAGS_TO_REMOVE = 4;

        inline static const std::array<std::string, NUM_OF_TAGS_TO_REMOVE> removeTagsArray =
        {
            styleTag1, acwp_title,
            termsAndConditions, comentNotesTag
        };

        inline static const std::string combinedRemoveTags = []
        {
            std::string temp;
            for (const std::string& tag : removeTagsArray)
            {
                temp += tag + "|";
            }
            temp.pop_back();
            return temp;
        }();

        inline static const std::regex tags{combinedRemoveTags};
    };
} // ArticalScraper

#endif //HTMLEXTRACTOR_H
