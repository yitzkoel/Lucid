//
// Created by yitzk on 10/5/2025.
//

#ifndef ANALYSISCOMMAND_H
#define ANALYSISCOMMAND_H
#include "Command.h"
#include "Shell.h"

namespace UserInterface
{
    /**
     * This class is the command that generates and adds the analysis to the cur artical loaded in the shell.
     */
    class AddAnalysisCommand : public Command
    {
    public:
        explicit AddAnalysisCommand(std::shared_ptr<Shell>& shell) : Command(shell)
        {
            setClient();
        }

        void execute(std::string arg) override;

    private:
        void setClient();
        std::unique_ptr<LLM::client> client_ ;//The LLM model interface
    };

    /**
     * This class is the command that generates and adds the analysis to the cur artical loaded in the shell.
     */
    class RemoveAnalysisCommand : public Command
    {
    public:
        explicit RemoveAnalysisCommand(std::shared_ptr<Shell>& shell) : Command(shell)
        {
        }

        void execute(std::string arg) override;
    };
} // UserInterface

#endif //ANALYSISCOMMAND_H
