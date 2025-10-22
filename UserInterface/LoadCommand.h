//
// Created by yitzk on 10/5/2025.
//

#ifndef LOADCOMMAND_H
#define LOADCOMMAND_H
#include "Command.h"
#include "Shell.h"
#include "../ArticleScraper/HtmlExtractor.h"

namespace UserInterface
{
    /**
     * This class runs the nesseccery logic to load into the shell the artical at the givin URL.
     */
    class LoadCommand : public Command
    {
    public:
        explicit LoadCommand(std::shared_ptr<Shell>& shell) :
            Command(shell),
            htmlExtractor(std::make_unique<ArticalScraper::HtmlExtractor>())
        {
        }

        void execute(std::string arg) override;

    private:
        std::unique_ptr<ArticalScraper::HtmlExtractor> htmlExtractor;
    };
} // UserInterface

#endif //LOADCOMMAND_H
