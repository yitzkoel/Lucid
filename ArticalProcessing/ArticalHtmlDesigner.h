//
// Created by yitzk on 9/8/2025.
//


#ifndef ARTICALHTMLDESIGNER_H
#define ARTICALHTMLDESIGNER_H
#include <string>
#include <utility>

#include "Artical.h"
#include "../ArticleScraper/HtmlExtractor.h"
#include "../Util/StringUtil.h"

namespace ArticalProcessing {
    /**
     * This class represents the constants of direction in html tags.
     */
    class Dir
    {
    private:
        std::string name_;

        explicit Dir(std::string name): name_(std::move(name)){}
    public:
        static const Dir LTR;
        static const Dir RTL;

        [[nodiscard]] std::string name() const {return this->name_;}
    };

    /**
     * his class represents the constants of language in html tags.
     */
    class Language
    {
    private:
        std::string name_;

        explicit Language(std::string name): name_(std::move(name)){}
    public:
        static const Language EN;
        static const Language HEB;

        [[nodiscard]] std::string name() const {return this->name_;}
    };




    /**
     * This class is responsible to desighn a html page based on a artical object and is able to generate a html file
     * according to specefecation or a default html file that include all the data in the artical object.
     */
    class ArticalHtmlDesigner {
    public:
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
        void setPath(std::string &path);
        /**
         *  This method lets the user control the languge of the page and the direction of the text layout.
         * @param dir the direction of the text on page (right to left or vice versa).
         * @param lng the default language in the page.
         */
        void setLanguage(Dir dir, Language lng);

        /**
         *  This is a contructor to the desighner.
         *  it will be initalized to a default state of hebrew language and right to left and all flags turned off.
         * @param artical The artical obj to create the html from.
         */
        explicit ArticalHtmlDesigner(Artical &artical);



        /**
         * This method creates a html file according to user prefrences.
         * @return The path to the html file created.
         */
        [[nodiscard]] std::string generateHtmlFile() ;

     
        void dumpVecBuffer(std::ofstream& htmlArtical, std::vector<std::string> htmlArticalBuffer) const;

        /**
         * Create a default layout with will be all the fields desplayed on the page.
        * @return The path to the html file created..
         */
        [[nodiscard]] std::string generateDefaultHtmlFile() ;

private:
    Artical artical_;
    std::string articalPath_;     //The path in Lucid directory to create the Html page.
    Dir dir_;
    Language lng_;

    bool title_, publishTime_, publisherData_, articleText_, URLlink_,author_, LLMRequests_;

        /**
         *  Generates a generic and unique path according to the URL link provided by the artical object.
         * @param string the URL link
         * @return A path that can be used by windows.
         */
        static std::string generatePath(const std::string& path);

         [[nodiscard]] std::string createRequests() ;

     static bool addTemplate(string& line, const char* templateStr, bool shouldAdd,
      const string& TemplateReplacement, std::vector<std::string>& vecBuffer);

};

} // ArticalProcessing

#endif //ARTICALHTMLDESIGNER_H
