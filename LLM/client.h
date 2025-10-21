//
// Created by yitzk on 9/14/2025.
//

#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "../include/json.hpp"
#include <curl/curl.h>

using json = nlohmann::json;

/**
 * @brief This namespace is responsible to provide simple LLM API interface.
 *
 * @note **IMPORTANT** this LLM namespace uses Open AI models and assumes getting Open AI API key.
 * @note **IMPORTANT** must include the include namespace of the Lucid project that has in it the json.hpp file
 * that includes all json.nlohmann library.
 */
namespace LLM
{
    /**
     * This class is the client of a LLM Online model of Open AI.
     * It cna genrate a response to a text request.
     */
    class client
    {
    public:
        explicit client(std::string& APIkey);
        ~client();

        /**
         *  This methods genrates the LLM response to the request.
         *  it can recies mult requests but returns only one response(to all at once).
         *
         * @param model the Open AI model to use.
         * @param requests the requests from the LLM model.
         * @return the response of the LLM.
         */

        std::string getResponse(std::string& model, const std::vector<std::string>& requests);
        /**
         * This method is the simple Client interface, it gets a request and generates a response.
         *
         * @param request the request from the LLM model.
         * @return The model response.
         */
        std::string getResponse(std::string& request);

    private:
        /**
         *  Creates the Jason request to be sent to the Open AI model.
         *
         * @param model the Open AI model
         * @param messages The vector of all messages to be added to the json request.
         */
        void createJsonRequest(std::string& model, const std::vector<std::string>& messages);

        /**
         * Sets the curl to be able to send the json request to Open AI servers.
         */
        void setCurl();

        std::string model_; // the Open AI model type.
        std::string APIkey_; // The API key to be able to access Open AI.
        json request_; // The request to be sent to Open AI via curl.
        json response_;  // the response gotten from the Open AI LLM.
        std::string bufferResponse_; // the string to save to parse into the LLM response.
        CURL* curl_ = nullptr; // the networking curl handle.
        curl_slist* headers_ = nullptr; //curl linked list structure that holds heades added to every curl request
                                        // required by Open AI API requirement.
    };
} // LLM

#endif //CLIENT_H
