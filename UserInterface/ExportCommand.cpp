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

        ArticalProcessing::ArticalHtmlDesigner designer(shell_->getArtical());
        if(shell_->hasAnalysisEnabled()) designer.addLLMRequests();
        std::string htmlPath = designer.generateDefaultHtmlFile();
        Util::FileUtil::copyFile(htmlPath, arg);
        Util::FileUtil::deleteFile(htmlPath);
    }
} // UserInterface