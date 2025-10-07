//
// Created by yitzk on 10/5/2025.
//

#include "CommandFactory.h"

#include "AnalysisCommand.h"
#include "ExitCommand.h"
#include "ExportCommand.h"
#include "LoadCommand.h"
#include "OpenCommand.h"
#include "Command.h"

namespace UserInterface {

    std::map<std::string, std::unique_ptr<Command>> CommandFactory::getCommands(std::shared_ptr<Shell> shell)
    {
        std::map<std::string, std::unique_ptr<Command>> commandMap;

        commandMap["load"] = std::make_unique<LoadCommand>(shell) ;
        commandMap["addAnalysis"] = std::make_unique<AddAnalysisCommand>(shell) ;
        commandMap["removeAnalysis"] = std::make_unique<RemoveAnalysisCommand>(shell) ;
        commandMap["exportTo"] = std::make_unique<ExportCommand>(shell) ;
        commandMap["exit"] = std::make_unique<ExitCommand>(shell) ;
        commandMap["open"] = std::make_unique<OpenCommand>(shell) ;

        return commandMap;
    }
} // UserInterface