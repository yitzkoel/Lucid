//
// Created by yitzk on 10/5/2025.
//

#include "ExportCommand.h"
#include "../ArticalProcessing/ArticalHtmlDesigner.h"
#include "../Util/FileUtil.h"

#include <iostream>

namespace UserInterface {

    void ExportCommand::execute(std::string arg)
    {
        if (! shell_->hasArticleLoaded())
        {
            std::cout << "No article to analize (hint input: load \"URL\" )\n";
            return;
        }

        //Util::StringUtil::replaceAll(arg,"\\","/");


        //Reset the article
        designer_->reset(shell_->getArtical());

        //add Analysis if needed
        if(shell_->hasAnalysisEnabled()) designer_->addLLMRequests();

        //Add To current file name the path provided
        std::string nameOfFile = designer_->getPath();
        designer_->setPath(arg + "\\" + nameOfFile);

        //Generate the html file in the wanted path
        designer_->generateDefaultHtmlFile();

        //reset the path of the file to the curent directory
        designer_->setPath(nameOfFile);
    }
} // UserInterface