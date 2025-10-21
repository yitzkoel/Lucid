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

    /**
     * This class is responsible to create all the coomads that are curently supported by the shell,
     * and the classes in the Lucid project.
     */
    class CommandFactory
    {
    public:
        /**
         * This method generates the current supposrted commad(for more look at class documention).
         * @param shell the shell that will implemnt the comands.
         * @return the map of the created commands.
         */
        static std::map<std::string, std::unique_ptr<Command>> getCommands(std::shared_ptr<Shell> shell);
    };
} // UserInterface

#endif //COMMANDFACTORY_H
