//
// Created by yitzk on 9/8/2025.
//

#include "ArticleHtmlDesigner.h"

#include <utility>

# define MAX_PATH_LENGTH 95
# define HTML_TEMPLATE_PATH "articalTemplateHtml"


namespace ArticleProcessing {

    // creating the const objects for Direction and Language.
    const Language Language::EN = Language("en");
    const Language Language::HEB = Language("he");

    const Dir Dir::LTR = Dir("ltr");
    const Dir Dir::RTL = Dir("rtl");

    ArticalHtmlDesigner::ArticalHtmlDesigner(std::shared_ptr<Article> artical):
    artical_(std::move(artical)),
    title_(false),
    publisherData_(false),
    publishTime_(false),
    URLlink_(false),
    articleText_(false),
    author_(false),
    LLMRequests_(false),
    dir_(Dir::RTL),
    lng_(Language::HEB)

        {
            articalPath_ = Util::StringUtil::convet_URL_to_valid_path(this->artical_->getURLlink());
        }

    ArticalHtmlDesigner::ArticalHtmlDesigner():
    dir_(Dir::RTL),
    lng_(Language::HEB)
    {
    }



    void ArticalHtmlDesigner::addTitle() {title_ = true;}

    void ArticalHtmlDesigner::addPublishTime(){publishTime_ = true;}

    void ArticalHtmlDesigner::addPublisherData(){publisherData_ = true;}

    void ArticalHtmlDesigner::addArticalText(){articleText_ = true;}

    void ArticalHtmlDesigner::addArticalURLlink(){URLlink_ = true;}

    void ArticalHtmlDesigner::addAuthor(){author_ = true;}

    void ArticalHtmlDesigner::addLLMRequests(){LLMRequests_ = true;}


    void ArticalHtmlDesigner::setPath(std::string path){articalPath_ = std::move(path);}

    void ArticalHtmlDesigner::setLanguage(Dir dir, Language lng)
    {
        dir_ = std::move(dir);
        lng_ = std::move(lng);
    }





    std::string ArticalHtmlDesigner::generateHtmlFile()
    {
        // Open files to read and write.
        std::ofstream htmlArtical(articalPath_);
        std::ifstream htmlTemplateFile(HTML_TEMPLATE_PATH);
        if(!htmlArtical || !htmlTemplateFile)
        {
            throw std::ios_base::failure("Failed to open file for writing: ");
        }

        // create buffer to create the file
        std::vector<std::string> htmlArticalBuffer;

        //Read the template into a buffer and into a string.
        std::stringstream buffer;
        buffer <<  htmlTemplateFile.rdbuf();

        std::string line;
        std::string llmRequests = createRequests();
        while (std::getline(buffer, line))
        {
            if(addTemplate(line,LANGUAGE_TEMPLATE, true,
                lng_.name(), htmlArticalBuffer))
            {
                htmlArticalBuffer.pop_back();
                addTemplate(line,DIRECTION_TEMPLATE, true,
                dir_.name(), htmlArticalBuffer);
                continue;
            }

            if(addTemplate(line, TITLE_TEMPLATE,title_,
                artical_->getHeadline(), htmlArticalBuffer)) continue;

            if(addTemplate(line, PUBLISH_TIME_TEMPLATE,publishTime_,
                artical_->getPublishDate(), htmlArticalBuffer)) continue;

            if(addTemplate(line, AUTHOR_TEMPLATE,author_,
                artical_->getAuthor(), htmlArticalBuffer)) continue;

            if(addTemplate(line, URL_LINK_TEMPLATE,URLlink_,
                artical_->getURLlink(), htmlArticalBuffer)) continue;

            if(addTemplate(line, ARTICLE_TEXT_TEMPLATE,articleText_,
                artical_->getArticleText(), htmlArticalBuffer)) continue;

            if(addTemplate(line, LLM_ANSWER_TEMPLATE,LLMRequests_,
                llmRequests, htmlArticalBuffer)) continue;

            htmlArticalBuffer.push_back(line + "\n");
        }
            dumpVecBuffer(htmlArtical, htmlArticalBuffer);
        // Return path to artical
        return articalPath_;
    }

    std::string ArticalHtmlDesigner::generateDefaultHtmlFile()
    {

        // Open files to read and write.
        std::ofstream htmlArtical(articalPath_);
        std::ifstream htmlTemplateFile(HTML_TEMPLATE_PATH);
        if(!htmlArtical || !htmlTemplateFile)
        {
            throw std::ios_base::failure("Failed to open file for writing, bad path\n");
        }

       // create buffer to create the file
        std::vector<std::string> htmlArticalBuffer;

        // Read the template into a buffer.
        std::stringstream HtmlTemplateBuffer;
        HtmlTemplateBuffer <<  htmlTemplateFile.rdbuf();

        // Fill in the buffer with the template buffer for each line of template.
        std::string line;
        std::string llmRequests = createRequests();
        while (std::getline(HtmlTemplateBuffer, line))
        {
            if(addTemplate(line,LANGUAGE_TEMPLATE, true,
                lng_.name(), htmlArticalBuffer))
            {
                htmlArticalBuffer.pop_back();
                addTemplate(line,DIRECTION_TEMPLATE, true,
                dir_.name(), htmlArticalBuffer);
                continue;
            }


            if(addTemplate(line, TITLE_TEMPLATE,true,
                artical_->getHeadline(), htmlArticalBuffer)) continue;

            if(addTemplate(line, PUBLISH_TIME_TEMPLATE,true,
                artical_->getPublishDate(), htmlArticalBuffer)) continue;

            if(addTemplate(line, AUTHOR_TEMPLATE,true,
                artical_->getAuthor(), htmlArticalBuffer)) continue;

            if(addTemplate(line, URL_LINK_TEMPLATE,true,
                artical_->getURLlink(), htmlArticalBuffer)) continue;

            if(addTemplate(line, ARTICLE_TEXT_TEMPLATE,true,
                artical_->getArticleText(), htmlArticalBuffer)) continue;

            if(addTemplate(line, LLM_ANSWER_TEMPLATE,LLMRequests_,
                llmRequests, htmlArticalBuffer)) continue;

            htmlArticalBuffer.push_back(line + "\n");
        }

        dumpVecBuffer(htmlArtical, htmlArticalBuffer);
        // Return path to artical.
        return  articalPath_;
    }



    void ArticalHtmlDesigner::reset(std::shared_ptr<Article> artical)
    {
        artical_ = std::move(artical);
        title_ = false;
        publisherData_ = false;
        URLlink_ = false;
        articleText_ = false;
        author_ = false;
        LLMRequests_ = false;
        dir_ = Dir::RTL;
        lng_ = Language::HEB;
        articalPath_ = Util::StringUtil::convet_URL_to_valid_path(this->artical_->getURLlink());
    }

    void ArticalHtmlDesigner::dumpVecBuffer(std::ofstream& htmlArtical, const std::vector<std::string>& htmlArticalBuffer)
    {
        for(const std::string& lineBuff : htmlArticalBuffer)
        {
            htmlArtical << lineBuff;
        }
    }

    std::string ArticalHtmlDesigner::createRequests()
    {
        std::string fullRequest;
        auto requests = artical_->getRequests();
        for(const LLM::Request& request: requests)
        {
            fullRequest +=
                            "<section class=\"ai-response\">\n"
                            "  <h2>" + request.get_title() + "</h2>\n"
                            "  <p>" + request.get_answer() + "</p>\n"
                            "</section>\n";
        }
        return fullRequest;
    }

    bool ArticalHtmlDesigner::addTemplate(string& line, string& templateStr, bool shouldAdd,
        const string& TemplateReplacement, std::vector<std::string>& vecBuffer)
    {
        if(line.find(templateStr) != std::string::npos)
        {
            if(shouldAdd) Util::StringUtil::replaceAll(line, templateStr , TemplateReplacement);
            else line = "";
            vecBuffer.push_back(line + "\n") ;
            return true;
        }
        return false;
        
    }


} // ArticleProcessing

