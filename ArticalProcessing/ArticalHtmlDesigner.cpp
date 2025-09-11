//
// Created by yitzk on 9/8/2025.
//

#include "ArticalHtmlDesigner.h"

#include <utility>

# define MAX_PATH_LENGTH 95


std::string replaceAll(std::string& str, const std::string& from, const std::string& to) {
    size_t startPos = 0;
    while((startPos = str.find(from, startPos)) != std::string::npos) {
        str.replace(startPos, from.length(), to);
        startPos += to.length();
    }
    return str;
}

namespace ArticalProcessing {

    // creating the const objects for Direction and Language.
    const Language Language::EN = Language("en");
    const Language Language::HEB = Language("he");

    const Dir Dir::LTR = Dir("ltr");
    const Dir Dir::RTL = Dir("rtl");

    ArticalHtmlDesigner::ArticalHtmlDesigner(Artical& artical):
    artical_(artical),
    title_(false),
    publisherData_(false),
    publishTime_(false),
    URLlink_(false),
    articleText_(false),
    author_(false),
    dir_(Dir::RTL),
    lng_(Language::HEB)
        {
            articalPath_ = generatePath(this->artical_.getURLlink());
        }



    void ArticalHtmlDesigner::addTitle() {title_ = true;}

    void ArticalHtmlDesigner::addPublishTime(){publishTime_ = true;}

    void ArticalHtmlDesigner::addPublisherData(){publisherData_ = true;}

    void ArticalHtmlDesigner::addArticalText(){articleText_ = true;}

    void ArticalHtmlDesigner::addArticalURLlink(){URLlink_ = true;}

    void ArticalHtmlDesigner::addAuthor(){author_ = true;}




    void ArticalHtmlDesigner::setPath(std::string& path){articalPath_ = path;}

    void ArticalHtmlDesigner::setLanguage(Dir dir, Language lng)
    {
        dir_ = std::move(dir);
        lng_ = std::move(lng);
    }





    std::string ArticalHtmlDesigner::generateHtmlFile() const
    {
        // Open files to read and write.
        std::ofstream htmlArtical(articalPath_);
        std::ifstream htmlTemplateFile("articalTemplateHtml.txt");
        if(!htmlArtical || htmlTemplateFile)
        {
            throw std::ios_base::failure("Failed to open file for writing: ");
        }

        // Read the template into a buffer and into a string.
        std::stringstream buffer;
        buffer <<  htmlTemplateFile.rdbuf();
        std::string htmlTemplate = buffer.str();

        // Add language and direction.
        htmlTemplate = replaceAll(htmlTemplate, "{{language}}", lng_.name());
        htmlTemplate = replaceAll(htmlTemplate, "{{direction}}", dir_.name());

        // Add title
        if(title_)
        {
            htmlTemplate = replaceAll(htmlTemplate, "{{title}}", artical_.getHeadline());
        }

        // Add publish time
        if(publishTime_)
        {
            htmlTemplate = replaceAll(htmlTemplate, "{{publishTime}}", artical_.getPublishDate());
        }

        // Add author's name.
        if(author_)
        {
            htmlTemplate = replaceAll(htmlTemplate, "{{author}}", artical_.getAuthor());
        }

        // Add url link.
        if(URLlink_)
        {
            htmlTemplate = replaceAll(htmlTemplate, "{{URLlink}}", artical_.getURLlink());
        }

        // Add articals text.
        if(articleText_)
        {
            htmlTemplate = replaceAll(htmlTemplate, "{{articalText}}", artical_.getArticleText());
        }

        // Copy the generated file into the html artical file.
        htmlArtical << htmlTemplate;

        // Return path to artical.
        return  articalPath_;
    }

    std::string ArticalHtmlDesigner::generatedefaultHtmlFile() const
    {

        // Open files to read and write.
        std::ofstream htmlArtical(articalPath_);
        std::ifstream htmlTemplateFile("C:/Users/yitzk/Desktop/c programs/Lucid/articalTemplateHtml");
        if(!htmlArtical || !htmlTemplateFile)
        {
            throw std::ios_base::failure("Failed to open file for writing: ");
        }

       // std::cout << htmlTemplateFile.rdbuf();

        // Read the template into a buffer and into a string.
        std::stringstream buffer;
        buffer <<  htmlTemplateFile.rdbuf();
        std::string htmlTemplate = buffer.str();

        // Fill in all the template.
        htmlTemplate = replaceAll(htmlTemplate, "{{language}}", lng_.name());
        htmlTemplate = replaceAll(htmlTemplate, "{{direction}}", dir_.name());
        htmlTemplate = replaceAll(htmlTemplate, "{{title}}", artical_.getHeadline());
        htmlTemplate = replaceAll(htmlTemplate, "{{publishTime}}", artical_.getPublishDate());
        htmlTemplate = replaceAll(htmlTemplate, "{{author name}}", artical_.getAuthor());
        htmlTemplate = replaceAll(htmlTemplate, "{{URLlink}}", artical_.getURLlink());
        htmlTemplate = replaceAll(htmlTemplate, "{{articalText}}", artical_.getArticleText());

        // Copy the generated file into the html artical file.
        htmlArtical << htmlTemplate;

        // Return path to artical.
        return  articalPath_;
    }




    std::string ArticalHtmlDesigner::generatePath(const std::string& path)
    {
        std::regex protocol("^https?://");
        std::regex invalid_chars(R"([%/:*?"<>|\\])");  // All problematic characters

        std::string augmentedString = std::regex_replace(path, protocol,"");
        augmentedString = std::regex_replace(augmentedString, invalid_chars, "_");

        // Clean up multiple underscores
        std::regex multiple_underscores("_+");
        augmentedString = std::regex_replace(augmentedString, multiple_underscores, "_");

        if(augmentedString.length() > MAX_PATH_LENGTH)
        {
            augmentedString = augmentedString.substr(0,MAX_PATH_LENGTH);
        }

        return augmentedString + ".html";
    }

} // Artical