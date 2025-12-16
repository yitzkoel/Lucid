//
// Created by yitzk on 10/5/2025.
//

#ifndef SHELL_H
#define SHELL_H
#include "Command.h"

#include "../ArticalProcessing/Artical.h"

/**
 * @brief This namspace provides all the classes needed to run a shell interface to run the lucid project that genrates
 * a simplified user and read friendly html page of web articles.
 *
 *  This namespace creates an interface to the Lucid project.
 *  The lucid project is a tool to html of online articles that are only the article text and critical information.
 *  The goal is to create a better reading experiance devoid of add and annoying layouts that is clutterd with garbage.
 *
 * This name space is devided into 3 parts.
 * The core: The shell class - responsible of managing all the interaction with the user (getting command input)
 *           and executing the Lucid functionalities wich will be described bellow.
 * The commands: implemented as an abstract Command class with the fallowing extensions:
 *                  1.load "URL" - the starting command of the given URL path.
 *                  2.addAnalysis/removeAnalysis - genrates ai analysis (using open ai) and adds to article.
 *                  3.exportTo "Directory" - exports the html file of the article in the givin "DIrectory" path.
 *                  4.open - opens the current loaded article with the default local browser
 *
 * @note **CRITICAL ASSUMPTION:** This entire library is designed for and
 * tested only on **Windows 64-bit** platforms.
 *
 * @note **CRITICAL ASSUMPTION:** This entire library need the user to to have a open AI API key,
 * and to set it as an environment variable by fallowing these steps.
 * 1.open Poweshell.
 * 2. input: $env:OPENAI_API_KEY="YOUR_SECRET_KEY_HERE"
 *
 */
namespace UserInterface
{
    class Command; // forword decleration
    class CommandFactory; // forword decleration

    /**
     * This class provides the shell interface to the Lucid aplication.
     * The Lucid aplication allows the user to create clean and reader friendly html page of online article.
     * To use:
     * input: load URL (press enter)
     *        open     (press enter)
     * To understand the Lucid appliction intirely and all possible functionalities
     * please read Lucid project readme (can be found in github).
     */
    class Shell : public std::enable_shared_from_this<Shell>
    {
    public:
        /**
         *  This method creates a Shell Obj on heap and returns the smart ptr to it.
         *  It is implemented in order to be able to use enable_shared_from_this class
         *  that allows a object to pass a smart pointer to itself.
         * @return a smart pointer to the this Shell obj.
         */
        static std::shared_ptr<Shell> create();


        /**
         * Returns true if there is a artical that was prev loaded into the shell.
         * @return
         */
        [[nodiscard]] bool hasArticleLoaded() const { return hasArticalLoaded_; }
        /**
         * Returns true if the user want an analysis desplayed with the artical.
         * @return
         */
        [[nodiscard]] bool hasAnalysisEnabled() const { return analysisEnabled_; }
        /**
         * Return true if the Shell generated to cur loaded artical a analysis.
         * @return
         */
        [[nodiscard]] bool hasAnalysisGenerated() const { return analysisGenerated_; }

        /**
         * Enables or disables adding analysis.
         * @param set the bool value to enable or disable adding analysis to artical.
         */
        void setAnalysis(bool set) { analysisEnabled_ = set; }

        /**
         *  A flag to indicate if the cur article has an analysis generated for it already.
         * @param set the bool value indicate if cur artical has a analysis genrated for it.
         */
        void setGeneratedAnalysis(bool set) { analysisGenerated_ = set; }

        /**
         *  This method sets up all setting to a new article to be handled by the shell.
         * @param artical the smart ptr to a article to be added to shell.
         */
        void setArtical(std::unique_ptr<ArticleProcessing::Article>& artical);

        /**
         * Sets the flag the shell uses to determine terminating the Lucid application.
         * @param exit the bool to indicate terminating the Lucid program.
         */
        void setExit(bool exit) { shouldExit_ = exit; }

        /**
         *  Returns a shared_ptr to article.
         * @return The cur article in the shell.
         */
        std::shared_ptr<ArticleProcessing::Article> getArtical() { return artical_; }

        /**
         * This func trys to execute the command givin to it with the arguments givin to it.
         *
         * @param command The string the user gave as input to activate a command that is in the shell's database
         * we assume it is a single word
         * @param arg optional string of the argument that the command can recieve.
         * @return  true-if the command was found in database and executed, false-No such command in database.
         */
        bool executeCommand(std::string& command, std::string& arg);

        /**
         *  This methods gets input from user, parses it to words and savs it in the 'token' vector.
         *  This method assumes geting 2 word string.
         * @param tokens the input vector to be filled with the user input.
         */
        static void getCommandFromUser(std::vector<std::string>& tokens);

        /**
         *  Runs the shell.
         * @return Exit succes when program terminates.
         */
        int run();

    private:
        /**
         * Private constructor.
         * To create obj use the create func.
         */
        Shell() : hasArticalLoaded_(false), analysisEnabled_(false), shouldExit_(false), analysisGenerated_(false)
        {
        }

        /**
         * Initates the commands srtucture with a pointer to this obj.
         */
        void init();

        /**
         * flags to keep track of changes, I added this to reduce redundency running backend proccess.
         */
        bool hasArticalLoaded_;
        bool analysisEnabled_;
        bool analysisGenerated_;
        bool shouldExit_;

        /**
         * Our command data structure
         */
        std::map<std::string, std::unique_ptr<Command>> commands;

        /**
         * The current artical to proccess.
         */
        std::shared_ptr<ArticleProcessing::Article> artical_;

    };
} // UserInterface

#endif //SHELL_H
