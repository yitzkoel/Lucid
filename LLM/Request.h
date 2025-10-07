//
// Created by yitzk on 9/29/2025.
//

#ifndef REQUEST_H
#define REQUEST_H
#include <string>

#include "client.h"
using std::string;

namespace LLM {

class Request {
public:
    Request() = default;
    Request(const string& requestPrompt,const string &requestBody,const string &requestTitle, client &LLMmodel );

    [[nodiscard]] string get_prompt() const
    {
        return requestPrompt_;
    }

    [[nodiscard]] string get_title() const
    {
        return requestTitle_;
    }

    [[nodiscard]] string get_answer() const
    {
        return answer_;
    }

    [[nodiscard]] string get_requestBody() const
    {
        return requestBody_;
    }

private:
    string requestPrompt_;
    string requestBody_;
    string requestTitle_;
    string answer_;

};

} // LLM

#endif //REQUEST_H
