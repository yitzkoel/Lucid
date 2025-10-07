//
// Created by yitzk on 10/5/2025.
//

#ifndef ANALYSISCOMMAND_H
#define ANALYSISCOMMAND_H
#include "Command.h"
#include "Shell.h"

namespace UserInterface
{
    class AddAnalysisCommand : public Command
    {
    public:
        explicit AddAnalysisCommand(std::shared_ptr<Shell>& shell) : Command(shell)
        {
        }

        void execute(std::string arg) override;
    };

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
