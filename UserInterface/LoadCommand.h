//
// Created by yitzk on 10/5/2025.
//

#ifndef LOADCOMMAND_H
#define LOADCOMMAND_H
#include "Command.h"
#include "Shell.h"

namespace UserInterface {

class LoadCommand : public Command{
public:
    explicit LoadCommand(std::shared_ptr<Shell>& shell) : Command(shell){}
    void execute(std::string arg) override;
};

} // UserInterface

#endif //LOADCOMMAND_H
