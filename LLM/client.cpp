//
// Created by yitzk on 9/14/2025.
//

#include "client.h"

#define AI_MODEL "gpt-4o-mini"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    auto *string = static_cast<std::string* > (userdata);
    string->append(ptr, size * nmemb);
    return size * nmemb;
}



namespace LLM {
    client::client(std::string& APIkey): APIkey_(move(APIkey)),model_(AI_MODEL)
    {
      setCurl();
    }

    client::~client()
    {
        curl_slist_free_all(headers_);
        curl_easy_cleanup(curl_);
    }

    std::string client::getResponse(std::string& model, const std::vector<std::string>& requests)
    {
        // Create json post data request.
        createJsonRequest(model,requests);
        std::string postData = request_.dump();

        // set curl with the requests
        curl_easy_setopt(curl_, CURLOPT_POSTFIELDS, postData.c_str());

        // Activate curl
        bufferResponse_.clear();
        response_.clear();
        CURLcode res = curl_easy_perform(curl_);
        if(res != CURLE_OK)
        {
            throw std::runtime_error(std::string("curl_easy_perform() failed: ") + curl_easy_strerror(res));
        }

        // Parse the response
        try {
            response_ = json::parse(bufferResponse_);
        } catch (json::parse_error& e) {
            throw std::runtime_error(std::string("Failed to parse JSON response: ") + e.what());
        }
        if (!response_.contains("choices") || response_["choices"].empty() ||
        !response_["choices"][0].contains("message") ||
        !response_["choices"][0]["message"].contains("content"))
        {
            throw std::runtime_error("Invalid API response: missing content");
        }

        bufferResponse_ = response_["choices"][0]["message"]["content"].get<std::string>();

        // Return
        return bufferResponse_;
    }


    std::string client::getResponse(std::string& request)
    {
        return getResponse(model_, std::vector<std::string>({request}));
    }
    

    void client::createJsonRequest(std::string& model, const std::vector<std::string>& messages)
    {
        request_.clear();
        request_["model"] = model;
        for(auto msg: messages) request_["messages"].push_back({{"role", "user"}, {"content", msg}});
    }

    void client::setCurl()
    {
        curl_ = curl_easy_init();
        if(!curl_)
        {
            throw std::runtime_error("failed to initialize curl");
        }

        // Add headers to request
        std::vector<std::string> vecHeader= {"Authorization: Bearer " + APIkey_,
                                            "Content-Type: application/json"} ;
        for(const auto& header : vecHeader ) headers_ = curl_slist_append(headers_, header.c_str());

        // Set curl.
        curl_easy_setopt(curl_, CURLOPT_HTTPHEADER, headers_);
        curl_easy_setopt(curl_,CURLOPT_URL,"https://api.openai.com/v1/chat/completions");

        // Set callback response
        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &bufferResponse_);

        // Set a 10-second timeout for the connection phase
        curl_easy_setopt(curl_, CURLOPT_CONNECTTIMEOUT, 10L);

        // Set a 30-second total timeout for the entire request
        curl_easy_setopt(curl_, CURLOPT_TIMEOUT, 30L);

        /**
         * PERFORMANCE OPTIONS OPTIMIZATION
        */

        // Enable TCP Keepalive
        curl_easy_setopt(curl_, CURLOPT_TCP_KEEPALIVE, 1L);

        // Disable Nagle's algorithm for lower latency
        curl_easy_setopt(curl_, CURLOPT_TCP_NODELAY, 1L);

        // Try to use HTTP/2
        curl_easy_setopt(curl_, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);

        // Disable the progress meter, as it's not needed for API calls
        curl_easy_setopt(curl_, CURLOPT_NOPROGRESS, 1L);

        // Use the default CA bundle
        curl_easy_setopt(curl_, CURLOPT_SSL_OPTIONS, CURLSSLOPT_NATIVE_CA);

        // Allow libcurl to reuse connections
        curl_easy_setopt(curl_, CURLOPT_FORBID_REUSE, 0L);

        // Allow compression requests
        curl_easy_setopt(curl_, CURLOPT_ACCEPT_ENCODING, "");
    }

} // LLM