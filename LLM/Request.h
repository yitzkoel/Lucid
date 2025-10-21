//
// Created by yitzk on 9/29/2025.
//

#ifndef REQUEST_H
#define REQUEST_H
#include <string>

#include "client.h"
using std::string;

namespace LLM
{
    /**
     * This class is responsible to create obj that save the a genrated LLM request and all the given input that was
     * used to create said request.
     */
    class Request
    {
    public:
        Request() = default;
        /**
         *  This is the constructor, it creates a LLM response on the given input data and generates it with the LLMModel.
         *
         * @param requestPrompt The prompt to be sent to the AI API.
         * @param requestBody Aditional text that the prompt may or may not refer to( that is is can be empty).
         * @param requestTitle The title of the given request, it is added to explain to users the request.
         * @param LLMmodel The LLM API to send request to and get answer.
         */
        Request(const string& requestPrompt, const string& requestBody, const string& requestTitle, client& LLMmodel);

        /**
         * Fields Getters
         */
        [[nodiscard]] string get_prompt() const { return requestPrompt_; }

        [[nodiscard]] string get_title() const {return requestTitle_;}

        [[nodiscard]] string get_answer() const {return answer_;}

        [[nodiscard]] string get_requestBody() const {return requestBody_;}

    private:
        string requestPrompt_;
        string requestBody_;
        string requestTitle_;
        string answer_;
    };
} // LLM

#endif //REQUEST_H
