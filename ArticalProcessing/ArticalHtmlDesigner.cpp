//
// Created by yitzk on 9/8/2025.
//

#include "ArticalHtmlDesigner.h"

#include <utility>

# define MAX_PATH_LENGTH 95
# define HTML_TEMPLATE_PATH "articalTemplateHtml.txt"


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
    LLMRequests_(false),
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

    void ArticalHtmlDesigner::addLLMRequests(){LLMRequests_ = true;}


    void ArticalHtmlDesigner::setPath(std::string& path){articalPath_ = path;}

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
            if(addTemplate(line,"{{language}}", true,
                lng_.name(), htmlArticalBuffer))
            {
                htmlArticalBuffer.pop_back();
                addTemplate(line,"{{direction}}", true,
                dir_.name(), htmlArticalBuffer);
                continue;
            }

            if(addTemplate(line, "{{title}}",title_,
                artical_.getHeadline(), htmlArticalBuffer)) continue;

            if(addTemplate(line, "{{publishTime}}",publishTime_,
                artical_.getPublishDate(), htmlArticalBuffer)) continue;

            if(addTemplate(line, "{{author}}",author_,
                artical_.getAuthor(), htmlArticalBuffer)) continue;

            if(addTemplate(line, "{{URLlink}}",URLlink_,
                artical_.getURLlink(), htmlArticalBuffer)) continue;

            if(addTemplate(line, "{{articalText}}",articleText_,
                artical_.getArticleText(), htmlArticalBuffer)) continue;

            if(addTemplate(line, "{{LLM answers}}",LLMRequests_,
                llmRequests, htmlArticalBuffer)) continue;

            htmlArticalBuffer.push_back(line + "\n");
        }
            dumpVecBuffer(htmlArtical, htmlArticalBuffer);
        // Return path to artical
        return articalPath_;
    }

    void ArticalHtmlDesigner::dumpVecBuffer(std::ofstream& htmlArtical, std::vector<std::string> htmlArticalBuffer) const
    {
        for(std::string& lineBuff : htmlArticalBuffer)
        {
            htmlArtical << lineBuff;
        }
    }

    std::string ArticalHtmlDesigner::generateDefaultHtmlFile()
    {

        // Open files to read and write.
        std::ofstream htmlArtical(articalPath_);
        std::ifstream htmlTemplateFile("C:/Users/yitzk/Desktop/c programs/Lucid/articalTemplateHtml");
        if(!htmlArtical || !htmlTemplateFile)
        {
            throw std::ios_base::failure("Failed to open file for writing: ");
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
            if(addTemplate(line,"{{language}}", true,
                lng_.name(), htmlArticalBuffer))
            {
                htmlArticalBuffer.pop_back();
                addTemplate(line,"{{direction}}", true,
                dir_.name(), htmlArticalBuffer);
                continue;
            }


            if(addTemplate(line, "{{title}}",true,
                artical_.getHeadline(), htmlArticalBuffer)) continue;

            if(addTemplate(line, "{{publishTime}}",true,
                artical_.getPublishDate(), htmlArticalBuffer)) continue;

            if(addTemplate(line, "{{author name}}",true,
                artical_.getAuthor(), htmlArticalBuffer)) continue;

            if(addTemplate(line, "{{URLlink}}",true,
                artical_.getURLlink(), htmlArticalBuffer)) continue;

            if(addTemplate(line, "{{articalText}}",true,
                artical_.getArticleText(), htmlArticalBuffer)) continue;

            if(addTemplate(line, "{{LLM answers}}",LLMRequests_,
                llmRequests, htmlArticalBuffer)) continue;

            htmlArticalBuffer.push_back(line + "\n");
        }

        dumpVecBuffer(htmlArtical, htmlArticalBuffer);
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

    std::string ArticalHtmlDesigner::createRequests()
    {
        std::string fullRequest;
        auto requests = artical_.getRequests();
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

    bool ArticalHtmlDesigner::addTemplate(string& line, const char* templateStr, bool shouldAdd,
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


} // ArticalProcessing

