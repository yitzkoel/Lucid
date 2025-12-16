//
// Created by yitzk on 10/5/2025.
//

#include "Shell.h"
#include "CommandFactory.h"

#include <iostream>

namespace UserInterface {
    std::shared_ptr<Shell> Shell::create()
    {
        auto shell = std::shared_ptr<Shell>(new Shell());
        shell->init(); // do post-construction setup that uses shared_from_this
        return shell;
    }

    void Shell::init()
    {
        commands = CommandFactory::getCommands(shared_from_this());
    }

    void Shell::setArtical(std::unique_ptr<ArticleProcessing::Article>& artical)
    {
        artical_ = std::move(artical);
        hasArticalLoaded_ = true;
        analysisEnabled_ = false;    // No cretaed analysis yet
        analysisGenerated_ = false;  // No cretaed analysis yet
    }

    bool Shell::executeCommand(std::string& commandStr, std::string& arg)
    {
        auto command = commands.find(commandStr);
        if(command == commands.end()) return false;
        try
        {
            command->second->execute( arg);
            //std::cout << "\n";
        }
        catch (const std::ios_base::failure& e)
        {
            std::cerr << e.what() << "\n";
        }
        catch (const std::runtime_error& e)
        {
            std::cerr << e.what() << "\n";
        }
        catch (const std::ios_base::failure& e)
        {
            std::cerr << e.what() << "\n";
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << "\n";
        }
        return true;
    }

    void Shell::getCommandFromUser(std::vector<std::string>& tokens)
    {
        std::string line;
        if (!std::getline(std::cin, line)) {
            return;
        }

        std::istringstream iss(line);  // wrap it in a stream

        std::string first;
        if (!(iss >> first)) return;  // no command typed
        tokens.push_back(first);

        
        std::string rest;
        std::getline(iss, rest);
        if (!rest.empty())
        {
            const std::string WHITESPACE = " \t\n\r\f\v";
            rest.erase(0, rest.find_first_not_of(WHITESPACE));
            rest.erase(rest.find_last_not_of(WHITESPACE) + 1);
        }
            
        if (!rest.empty())
            tokens.push_back(rest);
    }

    int Shell::run()
    {
        std::vector<std::string> tokens;
        while(!shouldExit_)
        {
            tokens.clear();
            std::cout << "> ";
            getCommandFromUser(tokens);

            if(tokens.empty()) continue;

            std::string arg;
            std::string command = tokens.at(0);

            if(tokens.size() == 2)
            {
                    arg = tokens[1];
            }

            if(!executeCommand(command, arg))
            {
                std::cout << "No such command.\n";
                continue;
            }
        }
        return EXIT_SUCCESS;
    }
} // UserInterface