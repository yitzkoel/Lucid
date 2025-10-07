//
// Created by yitzk on 9/29/2025.
//

#include "Request.h"

namespace LLM {
    Request::Request(const string& requestPrompt,const string &requestBody,const string &requestTitle, client &LLMmodel):
    requestPrompt_(requestPrompt),requestBody_(requestBody),  requestTitle_(requestTitle)
    {
        string fullRequest = requestPrompt + "\n" + requestBody;
        try
        {
            answer_=LLMmodel.getResponse(fullRequest);
        }
        catch (const std::runtime_error& e)
        {
            throw std::runtime_error(std::string("Failed to answer request from the LLM\n") + e.what());
        }

    }
} // LLM