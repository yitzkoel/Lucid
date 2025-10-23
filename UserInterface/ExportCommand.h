//
// Created by yitzk on 10/5/2025.
//

#ifndef EXPORTCOMMAND_H
#define EXPORTCOMMAND_H
#include "Command.h"
#include "../ArticalProcessing/ArticalHtmlDesigner.h"

namespace UserInterface {
    /**
     * This class genrates a html file of the cur article and saves is at the givin directory.
     */
    class ExportCommand : public Command{
public:
    explicit ExportCommand(std::shared_ptr<Shell>& shell)
        : Command(shell), designer_(std::make_unique<ArticalProcessing::ArticalHtmlDesigner>())
    {
    }

    void execute(std::string arg) override;
    private:
        std::unique_ptr<ArticalProcessing::ArticalHtmlDesigner> designer_;
};

} // UserInterface

#endif //EXPORTCOMMAND_H
