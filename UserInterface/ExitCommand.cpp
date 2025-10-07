//
// Created by yitzk on 10/5/2025.
//

#include "ExitCommand.h"

namespace UserInterface {
    void ExitCommand::execute(std::string arg)
    {
        getShell()->setExit(true);
    }
} // UserInterface