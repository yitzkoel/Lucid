//
// Created by yitzk on 9/8/2025.
//

#ifndef ARTICAL_H
#define ARTICAL_H
#include <string>

namespace ArticalProcessing {

    class Artical {
    private:
        std::string URLlink;
        std::string nameOfAuther;
        std::string headline;
        std::string publishDate;
        std::string publisherData;
        std::string articlaText;

    public:
        // Parameterized constructor
        Artical(
            std::string& URLlink,
            std::string& nameOfAuther,
            std::string& headline,
            std::string& publishDate,
            std::string& publisherData,
            std::string& articlaText ) :
            URLlink(URLlink),
            nameOfAuther(nameOfAuther),
            headline(headline),
            publishDate(publishDate),
            publisherData(publisherData),
            articlaText(articlaText) {}

        // default constructor
        Artical() = default;

        //setters
        void set_URLlink(const std::string& URL_link) {URLlink = URL_link;}
        void set_name_of_auther(const std::string& name_of_auther) {nameOfAuther = name_of_auther;}
        void set_headline(const std::string& headline) {this->headline = headline;}
        void set_publish_date(const std::string& publish_date) {publishDate = publish_date;}
        void set_publisher_data(const std::string& publisher_data) {publisherData = publisher_data;}
        void set_articla_text(const std::string& articla_text) {articlaText = articla_text;}

        // getters
        const std::string& getURLlink() const { return URLlink; }
        const std::string& getAuthor() const { return nameOfAuther; }
        const std::string& getHeadline() const { return headline; }
        const std::string& getPublishDate() const { return publishDate; }
        const std::string& getPublisherData() const { return publisherData; }
        const std::string& getArticleText() const { return articlaText; }

        void addToArticalText(std::string text);


    };

} // ArticalProccessing

#endif //ARTICAL_H
