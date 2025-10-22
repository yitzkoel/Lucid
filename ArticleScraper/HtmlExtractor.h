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

/**
 * This namespase allows to scrape URL's of articles.
 *
 * @note  **IMPORTANT ASSUMPTION** This assumes that the input URL is an actual article.
 * @note  **IMPORTANT ASSUMPTION** This library can handle only article that the article text is in the html page.
 *                                 It can't handel article pages that the html contain a js script that genrate
 *                                 the article text.
 * @note **IMPORTANT ASSUMPTION** this library was tested only on the current(2025) israely news sites.
 *
 */
namespace ArticalScraper
{
    /**
     * This class extracts the html page from teh web and can extract the required data from it.
     * That is:
     *       1.article text.
     *       2.Name of author.
     *       3.Headline.
     *       4.Publish date.
     *       5.Publisher information.
     *       6.Link to page.
     *
     */
    class HtmlExtractor
    {
    public:
        /**
         * Constructor
         */
        HtmlExtractor();
        /**
         * Destructor;
         */
        ~HtmlExtractor();


        /**
         * This methed sends a request from a website to the html and saves it to a local file.
         * This scaper handels only http and https requests and will return failure otherwise.
         *
         * @param path A path to the website that holds the artical.
         * @return A path to a local directory that holds the articals html, returns empty string if fail.
         */
        [[nodiscard]] std::string websiteDownloader(const std::string& path) const;

        /**
         * This methods recieves a raw html in a txt file of a artical and removes all unessecery text
         * And saves it in the given path.
         *
         * It keeps the fallowing data (in this order):
         *
         * We save in the file the metaData on the article In JSON format.
         * it will be saved inside the fallowing header:
         *                              <script type=\"application/ld+json\"> THE META DATA <\script>
         * The META DATA will include the falowing in this order:
         * 1.Link to page.
         * 2.Name of author.
         * 3.Headline.
         * 4.Publish date.
         * 5.Publisher information.
         *
         *  After MetaData we will add the actual article text in the the header <p>ARTICLE TEXT<\p>
         *
         * @param path  the path to the downlaoded html file.
         * @return A path to the reformated file.
         *         please note that it is the same path as the input path.
         */
        static std::string htmlDataExtractorToFile(const std::string& path);

        /**
         * This methods recieves a raw html in a txt file of a article and creates a article obj that holds all
         * important information on the article.
         * It keeps the fallowing data :
         *
         *  URLlink
         *  nameOfAuther
         *  headline
         *  publishDate
         *  publisherData
         *  articleText
         *
         * @param path  the path to the downlaoded html file.
         * @return A path to the reformated file please note that it is the same path as the input path.
         */
        static std::unique_ptr<ArticalProcessing::Artical> htmlDataExtractorToArtical(const std::string& path);

    private:
        CURL* curl_ = nullptr;
        void setCurl();


        /**
         *
         * @param path The URL path to be downloaded artical from.
         * This method checks that the path prefix is valid for the curl setting.
         * @return bool of result.
         */
        static bool isValidURL_Regex(const std::string& path);


        /**
         * This method adds the fallowing metadata from the URL html page:
         * Link to page.
         * Name of author.
         * Headline.
         * Publish date.
         * Publisher information.
         * @param html  the oroginal URL html page.
         * @param artical the file to add to the meta data.
         */
        static void addMetaData(const std::string* html, std::ofstream* artical);
        /**
         * This method adds the fallowing metadata from the URL html page:
         * Link to page.
         * Name of author.
         * Headline.
         * Publish date.
         * Publisher information.
         * @param html the oroginal URL html page.
         * @param artical the Article obj to add to it the meta data.
         */
        static void addMetaData(const std::string* html, ArticalProcessing::Artical& artical);


        /**
         * all of the code bellow is to create static regex
         * that will be created once in the program's static initialization phase,
         * and will be saved during the running of any program that will include this class.
         */

        /**
         * Regex constants used in the class
         */
        inline static const std::regex PROTOCOL_REGEX{"^https?://"};
        inline static const std::regex AUTHOR_REGEX{
            "\"author\":\\s*\\{[\\s\\S]*?\"name\":\\s*?\"([^\"]*)\"[\\s\\S]*?\\}"
        };
        inline static const std::regex HEADLINE_REGEX{"<title[\\s\\S]*?>([\\s\\S]*?)</title>"};
        inline static const std::regex DATE_REGEX{"\"datePublished\":\\s*?\"([\\s\\S]*?)\""};
        inline static const std::regex PUBLISHER_REGEX{R"("publisher": \{[\s\S]*?\})"}; //the news media that published


        inline static const std::regex MAIN_ARTICLE_TEXT_REGEX{
            R"(((<p>|<p\s).*?</p>)|(<span data-text="true">(.*?)</span>))"
        };
        inline static const string META_DATA_HTML_TAG_START = "<script type=\"application/ld+json\">\n{";
        inline static const string META_DATA_HTML_TAG_END = "}</script>";


        /**
         * The regex that will be used later to remove all these bellow tags
         * from the text extracted from the html downloaded.
         *
         * all the tags bellow are regex patterns.
         * They are ment to catch patterns that need to be removed from the article html text.
         */
        inline static const std::string termsAndConditions = "<p class=\"terms-and-conditions-p\".*?</p>";
        inline static const std::string comentNotesTag = "<p class=\"comment-.*?\">.*?</p>";
        inline static const std::string styleTag = "<p style=\"display:.*?</p>";
        inline static const std::string acwp_title = "<p class=\"acwp-title\">.*?</p>";
        static const int NUM_OF_TAGS_TO_REMOVE = 4;

        /**
         * create a array of all tags to remove.
         */
        inline static const std::array<std::string, NUM_OF_TAGS_TO_REMOVE> removeTagsArray =
        {
            styleTag, acwp_title,
            termsAndConditions, comentNotesTag
        };

        /**
         * lambda To create the combined regex of all tags that need to be remved.
         */
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

        // the final regex.
        inline static const std::regex tags{combinedRemoveTags};
    };
} // ArticalScraper

#endif //HTMLEXTRACTOR_H
