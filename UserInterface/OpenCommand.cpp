//
// Created by yitzk on 10/5/2025.
//

#include "OpenCommand.h"
#include "../ArticalProcessing/ArticalHtmlDesigner.h"
#include "../Util/FileUtil.h"
#include <cstdlib>

#include <iostream>
#include <thread>

namespace UserInterface {
    void OpenCommand::execute(std::string arg)
    {
        if (! shell_->hasArticleLoaded())
        {
            std::cout << "No article to analize (hint input: load \"URL\" )";
            return;
        }
        ArticalProcessing::ArticalHtmlDesigner designer(shell_->getArtical());
        if(shell_->hasAnalysisEnabled()) designer.addLLMRequests();
        std::string htmlPath = designer.generateDefaultHtmlFile();
        std::string cmd = "start \"\" \"" + htmlPath + "\"";
        std::system(cmd.c_str());
        // wait a bit before deleting
        std::this_thread::sleep_for(std::chrono::seconds(2));
        Util::deleteFile(htmlPath);
    }
} // UserInterface