#include <iostream>
#include <string>
#include <curl/curl.h>
#include "ArticleScraper/HtmlExtractor.h"

int test_HtmlExtractor_class(int argc, char* argv[])
{
    std::string path1;
    if (argc != 2) return EXIT_FAILURE;
    try
    {
        path1 = ArticalScraper::HtmlExtractor::websiteDownloader(argv[1]);
        std::cout << "Successfully downloaded to: " << path1 << std::endl;
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Bad input: " << e.what() << '\n';
        std::cerr << "Download failed!" << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::ios_base::failure& e)
    {
        std::cerr << "I/O error: " << e.what() << '\n';
        std::cerr << "Download failed!" << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Runtime error: " << e.what() << '\n';
        std::cerr << "Download failed!" << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Other exception: " << e.what() << '\n';
        std::cerr << "Download failed!" << std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        std::string path2 = ArticalScraper::HtmlExtractor::htmlDataExtractorToFile(path1);
        std::cout << "Successfully reformated the html to artical" << std::endl;
        return EXIT_SUCCESS;
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Bad input: " << e.what() << '\n';
        std::cerr << "Download failed!" << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::ios_base::failure& e)
    {
        std::cerr << "I/O error: " << e.what() << '\n';
        std::cerr << "Download failed!" << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Runtime error: " << e.what() << '\n';
        std::cerr << "Download failed!" << std::endl;
        return EXIT_FAILURE;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Other exception: " << e.what() << '\n';
        std::cerr << "Download failed!" << std::endl;
        return EXIT_FAILURE;
    }
}



int main(int argc, char* argv[])
{
  return test_HtmlExtractor_class(argc, argv);
}
