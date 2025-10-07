//
// Created by yitzk on 10/5/2025.
//

#ifndef SHELL_H
#define SHELL_H
#include "Command.h"

#include "../ArticalProcessing/Artical.h"

namespace UserInterface
{
    class Command; // forword decleration
    class CommandFactory; // forword decleration

    class Shell : public std::enable_shared_from_this<Shell>
    {
    public:
        static std::shared_ptr<Shell> create();

        void init();

        [[nodiscard]] bool hasArticleLoaded() const { return hasArticalLoaded_; }
        [[nodiscard]] bool hasAnalysisEnabled() const { return analysisEnabled_; }
        [[nodiscard]] bool hasAnalysisGenerated() const {return  analysisGenerated_;}

        void setAnalysis(bool set){analysisEnabled_ = set;}

        void setGeneratedAnalysis(bool set){analysisGenerated_ = set;}


        void setArtical(std::unique_ptr<ArticalProcessing::Artical>& artical);

        void setExit(bool exit) { shouldExit_ = exit; }

        ArticalProcessing::Artical& getArtical() { return *artical_; }

        bool executeCommand(std::string& command, std::string& arg);

        static void getCommandFromUser(std::vector<std::string>& tokens);

        int run();

    private:
        Shell() : hasArticalLoaded_(false), analysisEnabled_(false), shouldExit_(false), analysisGenerated_(false)
        {
        }

        bool hasArticalLoaded_;
        bool analysisEnabled_;
        bool shouldExit_;

        std::map<std::string, std::unique_ptr<Command>> commands;
        std::shared_ptr<ArticalProcessing::Artical> artical_;
        bool analysisGenerated_;
    };
} // UserInterface

#endif //SHELL_H
