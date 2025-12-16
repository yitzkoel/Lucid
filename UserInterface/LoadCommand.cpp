//
// Created by yitzk on 10/5/2025.
//

#include "LoadCommand.h"
#include "../ArticleScraper/HtmlExtractor.h"

namespace UserInterface {
    void LoadCommand::execute(std::string arg)
    {
        std::string path = htmlExtractor->websiteDownloader(arg);
        std::unique_ptr<ArticleProcessing::Article> artical = htmlExtractor->htmlDataExtractorToArtical(path);

        shell_->setArtical(artical);

    }
} // UserInterface