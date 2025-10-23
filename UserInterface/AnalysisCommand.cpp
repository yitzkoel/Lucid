//
// Created by yitzk on 10/5/2025.
//

#include "AnalysisCommand.h"

#include <iostream>

namespace UserInterface
{
    const std::string REQUEST =
    "The following article is in hebrew. Critically analyze this article for logical errors, biases, and validity"\
    "of arguments, in neutral, unbiased language. Organize for readability. Respond in the same language as the article."\
    "Organize for readability and RETURN THE OUTPUT AS PURE HTML ONLY (no markdown)"\
    "No need to add a title just add the critical analysis.";

    const std::string REQUEST_TITLE = "Critical Analysis";


    void AddAnalysisCommand::execute(std::string arg)
    {
        if (! shell_->hasArticleLoaded())
        {
            std::cout << "No article to analize (hint input: load \"URL\" )";
            return;
        }
        if (getShell()->hasAnalysisEnabled()) return;

        if(getShell()->hasAnalysisGenerated())
        {
            shell_->setAnalysis(true);
            return;
        }

        auto artical = shell_->getArtical();

        LLM::Request request = LLM::Request(REQUEST,
                            artical->getArticleText(),
                            REQUEST_TITLE, *client_);

        artical->addRequest(request);
        shell_->setAnalysis(true);
        shell_->setGeneratedAnalysis(true);
    }

    void AddAnalysisCommand::setClient()
    {
        const char* key_cstr = std::getenv("OPENAI_API_KEY");
        if (key_cstr == nullptr)
        {
            throw std::runtime_error(
        #ifdef _WIN32
                "Missing environment variable OPENAI_API_KEY.\n"
                "Please set it with:\n"
                "  setx OPENAI_API_KEY \"your_api_key_here\"\n"
        #else
            "Missing environment variable OPENAI_API_KEY.\n"
            "Please set it with:\n"
            "  export OPENAI_API_KEY=\"your_api_key_here\"\n"
        #endif
            );
        }
        std::string key(key_cstr);
        client_ = std::make_unique<LLM::client>(key);
    }

    void RemoveAnalysisCommand::execute(std::string arg)
    {
        if (!shell_->hasArticleLoaded()) std::cout << "No artical to analize (hint input: load \"URL\" )";

        if(!shell_->hasAnalysisEnabled()) return;

        shell_->setAnalysis(false);
    }
} // UserInterface
