//
// Created by yitzk on 9/14/2025.
//

#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include "../include/json.hpp"
#include <curl/curl.h>

using json = nlohmann::json;

namespace LLM {


class client {
public:
    explicit client(std::string& APIkey);
    ~client();

    


    std::string getResponse(std::string &model, const std::vector<std::string>& requests);
    std::string getResponse(std::string& request);

private:
    void createJsonRequest(std::string& model, const std::vector<std::string>& messages);
    void setCurl();

    std::string model_;
    std::string APIkey_;
    json request_;
    json response_;
    std::string bufferResponse_;
    CURL* curl_ = nullptr;
    curl_slist* headers_ = nullptr;
};

} // LLM

#endif //CLIENT_H
