//
// Created by yitzk on 10/5/2025.
//

#ifndef OPENCOMMAND_H
#define OPENCOMMAND_H
#include "Command.h"

namespace UserInterface {

class OpenCommand :public Command {
public:
    explicit OpenCommand(std::shared_ptr<Shell>& shell): Command(shell){}

    void execute(std::string arg) override;
};

} // UserInterface

#endif //OPENCOMMAND_H
