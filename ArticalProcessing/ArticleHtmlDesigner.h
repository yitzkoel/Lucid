//
// Created by yitzk on 9/8/2025.
//


#ifndef ARTICALHTMLDESIGNER_H
#define ARTICALHTMLDESIGNER_H
#include <string>
#include <utility>

#include "Article.h"
#include "../ArticleScraper/HtmlExtractor.h"
#include "../Util/StringUtil.h"

namespace ArticleProcessing
{
    /**
     * This class represents the constants of direction in html tags.
     */
    class Dir
    {
    private:
        std::string name_;

        explicit Dir(std::string name): name_(std::move(name))
        {
        }

    public:
        static const Dir LTR;
        static const Dir RTL;

        [[nodiscard]] std::string name() const { return this->name_; }
    };

    /**
     * This class represents the constants of language in html tags.
     */
    class Language
    {
    private:
        std::string name_;

        explicit Language(std::string name): name_(std::move(name))
        {
        }

    public:
        static const Language EN;
        static const Language HEB;

        [[nodiscard]] std::string name() const { return this->name_; }
    };


    /**
     * This class is responsible to desighn a html page based on a artical object and is able to generate a html file
     * according to specefecation or a default html file that include all the data in the artical object.
     *
     * @note **IMPORTANT ASSUMPTION** This class assumes you have a articalTemplateHtml.html file in the .exe directory.
     * @note **IMPORTANT** this class gives default setting to hebrew layout (direction of html page and so on).
     *
     */
    class ArticalHtmlDesigner
    {
    public:
        /**
        *  This is a contructor to the desighner.
        *  it will be initalized to a default state of hebrew language and right to left and all flags turned off.
        * @param artical The artical obj to create the html from.
        */
        explicit ArticalHtmlDesigner(std::shared_ptr<Article> artical);

        ArticalHtmlDesigner();

        /**
         * This method resets the desighner with a bew article.
         *
         * @param artical The new article to load into the designer
         */
        void reset(std::shared_ptr<Article> artical);


        // The add functions bellow turn on a flag that will be used when generating a html file.
        void addTitle();
        void addPublishTime();
        void addPublisherData();
        void addArticalText();
        void addArticalURLlink();
        void addAuthor();
        void addLLMRequests();

        /**
         *  This method lets the user control what path the html generated will have.
         * @param path the path to the generated html page to be created
         */
        void setPath(std::string path);
        /**
         *  This method lets the user control the languge of the page and the direction of the text layout.
         * @param dir the direction of the text on page (right to left or vice versa).
         * @param lng the default language in the page.
         */
        void setLanguage(Dir dir, Language lng);


        /**
         * This method creates a html file according to user prefrences.
         * @return The path to the html file created.
         */
        std::string generateHtmlFile();


        /**
         * Create a default layout with will be all the fields desplayed on the page.
        * @return The path to the html file created..
         */
        std::string generateDefaultHtmlFile();

        /**
         *
         * @return
         */
        std::string getPath(){return articalPath_;}

    private:
        /**
         * Constants
         */
        inline static string LANGUAGE_TEMPLATE = "{{language}}";
        inline static string DIRECTION_TEMPLATE = "{{direction}}";
        inline static string TITLE_TEMPLATE = "{{title}}";
        inline static string PUBLISH_TIME_TEMPLATE = "{{publishTime}}";
        inline static string AUTHOR_TEMPLATE = "{{author name}}";
        inline static string URL_LINK_TEMPLATE = "{{URLlink}}";
        inline static string ARTICLE_TEXT_TEMPLATE = "{{articalText}}";
        inline static string LLM_ANSWER_TEMPLATE = "{{LLM answers}}";


        std::shared_ptr<Article> artical_; // The article to be geneated into a html file.
        std::string articalPath_; //a valid path with the file name to create in the html file.
        Dir dir_; // direction setting in html.
        Language lng_; // language setting in html.

        //Flags to indicate to the class obj if to add the listed part to the final html
        bool title_{}, publishTime_{}, publisherData_{}, articleText_{}, URLlink_{}, author_{}, LLMRequests_{};


        /**
         * This method Takes a Request Object and extracts the information in it to create a string that cna be injected
         * into a html file.
         *
         * @return the request in html tags
         */
        [[nodiscard]] std::string createRequests();

        /**
         *
         * This method gets the line from the template and decides based on the bellow vars if it should replace some 'templateStr'
         * inside of line with 'TemplateReplacement' and add the augmented line to 'vecBuffer'.
         *
         * @param line The line from the html template that the template should or shouldnt inject to it the 'TemplateReplacement' string.
         * @param templateStr The string in the template to search for
         * @param shouldAdd  Bool val to indicte if the line should be augmented before adding to vecBuffer.
         * @param TemplateReplacement The string to replace the template in 'line' string.
         * @param vecBuffer  The vector to add the line to after augmention.
         * @return bool val if the line was augmented and added to vecBuffer or not.
         */
        static bool addTemplate(string& line, string& templateStr, bool shouldAdd,
                                const string& TemplateReplacement, std::vector<std::string>& vecBuffer);

        /**
            * This method dumps the entire vector(which is supposed to hold all the data of that article) into the stream.
            *
            * @param htmlArtical the stream of the article.
            * @param htmlArticalBuffer the vector holding the article
            */
        static void dumpVecBuffer(std::ofstream& htmlArtical, const std::vector<std::string>& htmlArticalBuffer);
    };
} // ArticalProcessing

#endif //ARTICALHTMLDESIGNER_H
