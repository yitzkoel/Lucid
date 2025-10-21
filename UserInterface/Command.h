//
// Created by yitzk on 10/5/2025.
//

#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <vector>

#include "Shell.h"
#include <memory>

namespace UserInterface
{
    class Shell;

    /**
     * This class is abstract.
     * The subclasses of this class will be responsible for running the logic of user commands.
     * It holds one public method, 'execute'.
     */
    class Command
    {
    public:
        explicit Command(std::shared_ptr<Shell>& shell): shell_(shell)
        {
        }

        /**
         * This method runs the logic of the given command type.
         * @param arg the arg input to run the command.
         */
        virtual void execute(std::string arg) = 0;
        std::shared_ptr<Shell> getShell() { return shell_; }
        virtual ~Command() = default;

    protected:
        std::shared_ptr<Shell> shell_;
    };
} // UserInterface

#endif //COMMAND_H
