//
// Created by yitzk on 10/5/2025.
//

#ifndef EXPORTCOMMAND_H
#define EXPORTCOMMAND_H
#include "Command.h"

namespace UserInterface {

class ExportCommand : public Command{
public:
    explicit ExportCommand(std::shared_ptr<Shell>& shell)
        : Command(shell)
    {
    }

    void execute(std::string arg) override;
};

} // UserInterface

#endif //EXPORTCOMMAND_H
