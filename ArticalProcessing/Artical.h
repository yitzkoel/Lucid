//
// Created by yitzk on 9/8/2025.
//

#ifndef ARTICAL_H
#define ARTICAL_H
#include <string>
#include <vector>
#include "../LLM/Request.h"

/**
 * This namespace has the classes responsible to create objects that
 * hold articles and all important data on those article that provide user friendly API.
 *
 * And A class ArticleHtmlDesighner that gets a article object and is able to create a html file to represent that article.
 *
 */
namespace ArticalProcessing {
    /**
     * This class represents a Article.
     * It holds fields of the atrbutes of an artical and getters and setters.
     */
    class Artical {

    public:
        //
        /**
         * Parameterized constructor
         *
         * @param URLlink The link to the artical website source.
         * @param nameOfAuther The name of the artical's author.
         * @param headline The name of the artical's headline.
         * @param publishDate Date and time of publish.
         * @param publisherData Data about the publishers.
         * @param articleText The artical itself.
         */
        Artical(
            std::string& URLlink,
            std::string& nameOfAuther,
            std::string& headline,
            std::string& publishDate,
            std::string& publisherData,
            std::string& articleText ) :
            URLlink(URLlink),
            nameOfAuther(nameOfAuther),
            headline(headline),
            publishDate(publishDate),
            publisherData(publisherData),
            articleText(articleText) {}

        // default constructor
        Artical() = default;
        

        //setters
        void set_URLlink(const std::string& URL_link) {URLlink = URL_link;}
        void set_name_of_auther(const std::string& name_of_auther) {nameOfAuther = name_of_auther;}
        void set_headline(const std::string& headline) {this->headline = headline;}
        void set_publish_date(const std::string& publish_date) {publishDate = publish_date;}
        void set_publisher_data(const std::string& publisher_data) {publisherData = publisher_data;}
        void set_article_text(const std::string& article_text) {articleText = article_text;}
        void addRequest(LLM::Request& request){LLMRequests.push_back(std::move(request));}

        // getters
        [[nodiscard]] const std::string& getURLlink() const { return URLlink; }
        [[nodiscard]] const std::string& getAuthor() const { return nameOfAuther; }
        [[nodiscard]] const std::string& getHeadline() const { return headline; }
        [[nodiscard]] const std::string& getPublishDate() const { return publishDate; }
        [[nodiscard]] const std::string& getPublisherData() const { return publisherData; }
        [[nodiscard]] const std::string& getArticleText() const { return articleText; }
        [[nodiscard]] std::vector<LLM::Request>& getRequests()  {return LLMRequests;}

        /**
         * This method lets you add more text to the artical dynamicly.
         * @param text The text to be added to the artical.
         */
        void addTextToArtical(const std::string& text);

    private:
        std::string URLlink;
        std::string nameOfAuther;
        std::string headline;
        std::string publishDate;
        std::string publisherData;
        std::string articleText;
        std::vector<LLM::Request> LLMRequests;
    };

} // ArticalProccessing

#endif //ARTICAL_H
