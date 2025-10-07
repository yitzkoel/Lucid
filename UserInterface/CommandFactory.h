//
// Created by yitzk on 10/5/2025.
//

#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H
#include <map>
#include <memory>
#include <string>

#include "Command.h"

namespace UserInterface
{
    class Command; //forword decleration
    class Shell; //forword decleration

    class CommandFactory
    {
    public:
        static std::map<std::string, std::unique_ptr<Command>> getCommands(std::shared_ptr<Shell> shell);
    };
} // UserInterface

#endif //COMMANDFACTORY_H
