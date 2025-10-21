//
// Created by yitzk on 10/5/2025.
//

#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H
#include "Command.h"

namespace UserInterface {
    /**
     * This command is responsible to terminate the shell run.
     */
    class ExitCommand : public Command{
public:
    explicit ExitCommand(std::shared_ptr<Shell>& shell)
        : Command(shell)
    {
    }

    void execute(std::string arg) override;
};

} // UserInterface

#endif //EXITCOMMAND_H
