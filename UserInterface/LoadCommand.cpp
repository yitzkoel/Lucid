//
// Created by yitzk on 10/5/2025.
//

#include "LoadCommand.h"
#include "../ArticleScraper/HtmlExtractor.h"

namespace UserInterface {
    void LoadCommand::execute(std::string arg)
    {
        std::string path1 = ArticalScraper::HtmlExtractor::websiteDownloader(arg);
        std::unique_ptr<ArticalProcessing::Artical> artical = ArticalScraper::HtmlExtractor::htmlDataExtractorToArtical(path1);

        shell_->setArtical(artical);

    }
} // UserInterface