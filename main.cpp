#include <iostream>
#include <string>
#include <curl/curl.h>

#include "ArticalProcessing/ArticalHtmlDesigner.h"
#include "ArticleScraper/HtmlExtractor.h"


std::string activate_artical_downlaoder(int argc, char* argv[]){
    std::string path1;
    try
    {
        path1 = ArticalScraper::HtmlExtractor::websiteDownloader(argv[1]);
        std::cout << "Successfully downloaded to: " << path1 << std::endl;
    }
    catch (const std::invalid_argument& e)
    {
        std::cerr << "Bad input: " << e.what() << '\n';
        std::cerr << "Download failed!" << std::endl;
        return "";
    }
    catch (const std::ios_base::failure& e)
    {
        std::cerr << "I/O error: " << e.what() << '\n';
        std::cerr << "Download failed!" << std::endl;
        return "";
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Runtime error: " << e.what() << '\n';
        std::cerr << "Download failed!" << std::endl;
        return "";
    }
    catch (const std::exception& e)
    {
        std::cerr << "Other exception: " << e.what() << '\n';
        std::cerr << "Download failed!" << std::endl;
        return "";
    }
    return path1;
}

int activate_artical_extractor_to_file(const std::string &path)
{
    try
    {
        std::string path2 = ArticalScraper::HtmlExtractor::htmlDataExtractorToFile(path);
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

ArticalProcessing::Artical* activate_artical_extractor_to_Artical(const std::string &path)
{
    ArticalProcessing::Artical *artical = nullptr;
    try
    {
         artical = &ArticalScraper::HtmlExtractor::htmlDataExtractorToArtical(path);
         std::cout << "successfully extracted" + path + " to Artical Object\n";
    }
    catch (const std::ios_base::failure& e)
    {
        std::cerr << e.what() << "\n";
    }
    return artical;
}

int test_HtmlExtractor_class(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Wrong number of arguments, can accept 2 only.";
        return EXIT_FAILURE;
    }

    std::string path1;
    path1 = activate_artical_downlaoder(argc, argv);

    return activate_artical_extractor_to_file(path1);

}


int test_HtmlExtracor_and_designer(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Wrong number of arguments, can accept 2 only.";
        return EXIT_FAILURE;
    }

    std::string path1;
    path1 = activate_artical_downlaoder(argc, argv);

    ArticalProcessing::Artical *artical = activate_artical_extractor_to_Artical(path1);
    if(!artical)
    {
        return EXIT_FAILURE;
    }

    ArticalProcessing::ArticalHtmlDesigner designer(*artical);

    try
    {
        std::string htmlPath = designer.generatedefaultHtmlFile();
        return EXIT_SUCCESS;
    }
    catch (const std::ios_base::failure& e)
    {
        std::cerr << e.what() << "\n";
        return  EXIT_FAILURE;
    }
}



int main(int argc, char* argv[])
{
  //return test_HtmlExtractor_class(argc, argv);
  return test_HtmlExtracor_and_designer(argc,argv);
}

