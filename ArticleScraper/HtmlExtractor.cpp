//
// Created by yitzk on 8/6/2025.
//

#include "HtmlExtractor.h"

# define MAX_PATH_LENGTH 95
/**
 *  This method replaces all problomatic chars in a URL path so it will be able to be used as a file path in windows.
 * @param path the URL.
 * @return a URL that can be used as a path in windows OS (and any other).
 */
std::string convet_URL_to_valid_path(const std::string& path)
{
    std::regex protocol("^https?://");
    std::regex invalid_chars(R"([%/:*?"<>|\\])");  // All problematic characters

    std::string augmentedString = std::regex_replace(path, protocol,"");
    augmentedString = std::regex_replace(augmentedString, invalid_chars, "_");

    // Clean up multiple underscores
    std::regex multiple_underscores("_+");
    augmentedString = std::regex_replace(augmentedString, multiple_underscores, "_");

    if(augmentedString.length() > MAX_PATH_LENGTH)
    {
        augmentedString = augmentedString.substr(0,MAX_PATH_LENGTH);
    }
    
    return augmentedString + ".html";
}

/**
 *
 * @param path The URL path to be downloaded artical from.
 * This method checks that the path prefix is valid for the curl setting.
 * @return bool of result.
 */
bool isValidURL_Regex(const std::string& path)
{
    std::regex protocol("^https?://");
    return std::regex_search(path, protocol);
}


/**
 * This method adds the fallowing metadata from the oroginal URL html page:
 * Link to page.
 * Name of author.
 * Headline.
 * Publish date.
 * Publisher information.
 * @param html  the oroginal URL html page.
 * @param artical the file to add to the meta data.
 */
void addMetaData(const std::string *html,std::ofstream *artical )
{
    // Adding the header to JSON meta data
    *artical << "<script type=\"application/ld+json\">\n{";
    std::smatch m;

    // Add link to page
    *artical << "<a href= " + (*html).substr(0, (*html).find('\n')) +">link to full website artical</a>\n";

    std::regex author(R"("author": \{[\s\S]*?\})");
    if(std::regex_search(*html, m, author))
    {
        *artical << m[0] << "\n";
    }

    // Add headline
    std::regex headline(R"("headline": "[\s\S]*?")");
    if(std::regex_search(*html, m, headline))
    {
        *artical << m[0] << "\n";
    }

    //Add Publishing date
    std::regex date(R"("datePublished": "[\s\S]*?")");
    if(std::regex_search(*html, m, date))
    {
        *artical << m[0] << "\n";
    }

    // Add publisher data
    std::regex publisher(R"("publisher": \{[\s\S]*?\})");   //the news media that published
    if(std::regex_search(*html, m, publisher))
    {
        *artical << m[0] << "\n";
    }

    // Close meta data JSON header
    *artical << "}</script>";
}

void addMetaData(const std::string *html,ArticalProcessing::Artical &artical )
{
    std::smatch m;

    // Add link to page
    artical.set_URLlink( (*html).substr(0, (*html).find('\n')));

    //std::regex author(R"("author": \{[\s\S]*?\})");
    //std::regex author(R"("author":\s*\{[\s\S]*?"name":\s*?"([\s\S]*?)"[\\s\\S]*?\})");
    std::regex author("\"author\":\\s*\\{[\\s\\S]*?\"name\":\\s*?\"([^\"]*)\"[\\s\\S]*?\\}");

    if(std::regex_search(*html, m, author))
    {
        artical.set_name_of_auther(m[1]);
    }

    // Add headline
    //std::regex headline("\"headline\":\\s*?\"([\\s\\S]*?)\",");
    std::regex headline("<title[\\s\\S]*?>([\\s\\S]*?)</title>");
    if(std::regex_search(*html, m, headline))
    {
        artical.set_headline( m[1]);
    }

    //Add Publishing date
    std::regex date("\"datePublished\":\\s*?\"([\\s\\S]*?)\"");
    if(std::regex_search(*html, m, date))
    {
        artical.set_publish_date(m[1]);
    }

    // Add publisher data
    std::regex publisher(R"("publisher": \{[\s\S]*?\})");   //the news media that published
    if(std::regex_search(*html, m, publisher))
    {
        artical.set_publisher_data(m[0]);
    }
}



namespace ArticalScraper {
    std::string HtmlExtractor::websiteDownloader(const std::string& path)
    {
        CURL* curl = curl_easy_init();
        if(!curl)
        {
            throw std::runtime_error("failed to initialize curl");
        }

        if(!isValidURL_Regex(path))
        {
            throw std::invalid_argument("URL must include http or https prefix");
        }


        std::string filePath = convet_URL_to_valid_path(path);
        FILE* file = fopen(filePath.c_str(), "wb");

        if(!file)
        {
            throw std::ios_base::failure("Failed to open file for writing: " + filePath);
        }

        //write link to file to use later
        std::string link =path + "\n";
        fputs(link.c_str(), file);

        //Transparent User-Agent to aprove scrape
        curl_easy_setopt(curl, CURLOPT_USERAGENT,
            "ArticleLooker (Educational Purpose; Contact: yitzkoel@gmail.com)");

        //Setting up the handle
        curl_easy_setopt(curl,CURLOPT_URL, path.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        CURLcode result = curl_easy_perform(curl);

        if(result != CURLE_OK)
        {
            throw std::runtime_error("CURL error: Failed to download from "+path);
        }

        curl_easy_cleanup(curl);
        fclose(file);
        
        return filePath;
    }

    std::string HtmlExtractor::htmlDataExtractorToFile(const std::string& path)
    {
        std::string temp = path + ".temp";
        std::ifstream html_page(path);
        std::ofstream artical(temp);

        if(!html_page || !artical)
        {
            throw std::ios_base::failure("Failed to open file for writing: ");
        }

        // Read entire HTML into a string
        std::ostringstream buffer;
        buffer << html_page.rdbuf();
        std::string html = buffer.str();

        //Add metadata in JSON to artical
        addMetaData(&html, &artical);

        // Regex for main artical text blocks
        std::smatch m;
        std::regex pattern(R"(((<p>|<p class="article_speakable">)(.*?)</p>)|(<span data-text="true">(.*?)</span>))");


        while (std::regex_search(html, m, pattern)) {
            std::string inner_text;
            if (m[3].matched)        // <p> branch matched
                inner_text = m[3].str();
            else if (m[5].matched)   // <span> branch matched
                inner_text = m[5].str();
            artical << "<p>" << inner_text << "</p>" << "\n";
            html = m.suffix().str();
        }

        // //ment for testing
        //  while (std::regex_search(html, m, pattern)) {
        //      artical << m[0] << "\n";
        //      html = m.suffix().str();
        //  }
        
        //safe close and renaming of reformated artical
        html_page.close();
        artical.close();
        if(std::remove(path.c_str()) != 0) {
            throw std::ios_base::failure("Error deleting original file");
        }
        if(std::rename(temp.c_str(), path.c_str()) != 0) {
            throw std::ios_base::failure("Error renaming temp file");
        }
        return path;
    }

    ArticalProcessing::Artical& HtmlExtractor::htmlDataExtractorToArtical(const std::string& path)
    {
        auto *artical = new ArticalProcessing::Artical();
        std::ifstream html_page(path);

        if(!html_page)
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
        std::regex pattern(R"(((<p>|<p class="article_speakable">)(.*?)</p>)|(<span data-text="true">(.*?)</span>))");


        while (std::regex_search(html, m, pattern)) {
            std::string inner_text;
            if (m[3].matched)        // <p> branch matched
                inner_text = m[3].str();
            else if (m[5].matched)   // <span> branch matched
                inner_text = m[5].str();
            artical->addTextToArtical("<p>" + inner_text + "</p>");
            html = m.suffix().str();
        }

        //safe close and renaming of reformated artical
        html_page.close();
        return *artical;
    }
} // ArticalScraper