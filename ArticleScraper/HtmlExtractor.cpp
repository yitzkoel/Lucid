//
// Created by yitzk on 8/6/2025.
//

#include "HtmlExtractor.h"

#include "../Util/FileUtil.h"
#include "../Util/StringUtil.h"


namespace ArticalScraper
{

    HtmlExtractor::HtmlExtractor()
    {
      setCurl();
    }

    HtmlExtractor::~HtmlExtractor()
    {
        curl_easy_cleanup(curl_);
    }

    void HtmlExtractor::setCurl()
    {
        curl_ = curl_easy_init();
        if (!curl_)
        {
            throw std::runtime_error("failed to initialize curl");
        }
        //Transparent User-Agent to aprove scrape
        curl_easy_setopt(curl_, CURLOPT_USERAGENT,
                         "Article view (Educational Purpose student in huji: Contact: yitzkoel@gmail.com)");

        //Setting up the handle
        curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, fwrite);
        curl_easy_setopt(curl_, CURLOPT_SSL_OPTIONS, CURLSSLOPT_NATIVE_CA);

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

    bool HtmlExtractor::isValidURL_Regex(const std::string& path)
    {
        return std::regex_search(path, PROTOCOL_REGEX);
    }

    void HtmlExtractor::addMetaData(const std::string* html, std::ofstream* artical)
    {
        // Adding the header to JSON meta data
        *artical << META_DATA_HTML_TAG_START;
        std::smatch m;

        // Add link to page
        *artical << "<a href= " + (*html).substr(0, (*html).find('\n')) + ">link to full website artical</a>\n";

        // Add author
        if (std::regex_search(*html, m, AUTHOR_REGEX))
        {
            *artical << m[0] << "\n";
        }

        // Add headline
        if (std::regex_search(*html, m, HEADLINE_REGEX))
        {
            *artical << m[0] << "\n";
        }

        //Add Publishing date
        if (std::regex_search(*html, m, DATE_REGEX))
        {
            *artical << m[0] << "\n";
        }

        // Add publisher data
        if (std::regex_search(*html, m, PUBLISHER_REGEX))
        {
            *artical << m[0] << "\n";
        }

        // Close meta data JSON header
        *artical << META_DATA_HTML_TAG_END;
    }

    void HtmlExtractor::addMetaData(const std::string* html, ArticalProcessing::Artical& artical)
    {
        std::smatch m;

        // Add link to page
        artical.set_URLlink((*html).substr(0, (*html).find('\n')));

        // Add author
        if (std::regex_search(*html, m, AUTHOR_REGEX))
        {
            artical.set_name_of_auther(m[1]);
        }

        // Add headline
        if (std::regex_search(*html, m, HEADLINE_REGEX))
        {
            artical.set_headline(m[1]);
        }

        // Add Publishing date
        if (std::regex_search(*html, m, DATE_REGEX))
        {
            artical.set_publish_date(m[1]);
        }

        // Add publisher data
        if (std::regex_search(*html, m, PUBLISHER_REGEX))
        {
            artical.set_publisher_data(m[0]);
        }
    }

    std::string HtmlExtractor::websiteDownloader(const std::string& path) const
    {
        if (!isValidURL_Regex(path))
        {
            throw std::invalid_argument("URL must include http or https prefix");
        }

        std::string filePath = Util::StringUtil::convet_URL_to_valid_path(path);
        FILE* file = fopen(filePath.c_str(), "wb");

        if (!file)
        {
            throw std::ios_base::failure("Failed to open file for writing: " + filePath);
        }

        //write link to file to use later
        std::string link = path + "\n";
        fputs(link.c_str(), file);

        //Setting up the handle
        curl_easy_setopt(curl_, CURLOPT_URL, path.c_str());
        curl_easy_setopt(curl_, CURLOPT_WRITEDATA, file);

        CURLcode result = curl_easy_perform(curl_);

        if (result != CURLE_OK)
        {
            fclose(file);
            std::string err = std::string("CURL error: ") + curl_easy_strerror(result);
            throw std::runtime_error(err + " " + path);
        }

        //close file
        fclose(file);

        return filePath;
    }

    std::string HtmlExtractor::htmlDataExtractorToFile(const std::string& path)
    {
        std::string temp = path + ".temp";
        std::ifstream html_page(path);
        std::ofstream artical(temp);

        if (!html_page || !artical)
        {
            throw std::ios_base::failure("Failed to open file for writing: ");
        }

        // Read entire HTML into a string
        std::ostringstream buffer;
        buffer << html_page.rdbuf();
        std::string html = buffer.str();

        //Add metadata in JSON to artical
        addMetaData(&html, &artical);

        // Regex search of main artical text blocks
        std::smatch m;
        while (std::regex_search(html, m, MAIN_ARTICLE_TEXT_REGEX))
        {
            std::string inner_text;
            if (m[3].matched) // <p> branch matched
                inner_text = m[3].str();
            else if (m[5].matched) // <span> branch matched
                inner_text = m[5].str();
            artical << "<p>" << inner_text << "</p>" << "\n";
            html = m.suffix().str();
        }

        //safe close and renaming of reformated artical
        html_page.close();
        artical.close();
        if (std::remove(path.c_str()) != 0)
        {
            throw std::ios_base::failure("Error deleting original file");
        }
        if (std::rename(temp.c_str(), path.c_str()) != 0)
        {
            throw std::ios_base::failure("Error renaming temp file");
        }
        return path;
    }

    std::unique_ptr<ArticalProcessing::Artical> HtmlExtractor::htmlDataExtractorToArtical(const std::string& path)
    {
        auto artical = std::make_unique<ArticalProcessing::Artical>();
        std::ifstream html_page(path);

        if (!html_page)
        {
            throw std::ios_base::failure("Failed to open file for writing: ");
        }

        // Read entire HTML into a string
        std::ostringstream buffer;
        buffer << html_page.rdbuf();
        std::string html = buffer.str();

        //Add metadata in JSON to artical
        addMetaData(&html, *artical);

        // Regex for main artical text blocks
        std::smatch m;

        while (std::regex_search(html, m, MAIN_ARTICLE_TEXT_REGEX))
        {
            std::string inner_text;
            if (m[1].matched) // <p> branch matched
                inner_text = m[1].str();
            else if (m[4].matched) // <span> branch matched
                inner_text = m[4].str();
            artical->addTextToArtical("<p>" + inner_text + "</p>");
            html = m.suffix().str();
        }

        // Remove all unwanted Tags look at h file to understand which tags were removed.
        artical->set_article_text(std::regex_replace(artical->getArticleText(), tags, ""));

        //safe close and renaming of reformated artical
        html_page.close();
        return std::move(artical);
    }
} // ArticalScraper
