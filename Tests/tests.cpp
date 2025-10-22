//
// Created by yitzk on 10/22/2025.
//

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <memory>
#include <io.h>
#include <iostream>

#include "../ArticalProcessing/ArticalHtmlDesigner.h"
#include "../ArticleScraper/HtmlExtractor.h"
#include "../LLM/client.h"
#include "../UserInterface/Shell.h"

const std::string REQUEST1 =
    "The following article is in hebrew. Critically analyze this article for logical errors, biases, and validity"\
    "of arguments, in neutral, unbiased language. Organize for readability. Respond in the same language as the article."\
    "Organize for readability and RETURN THE OUTPUT AS PURE HTML ONLY (no markdown)"\
    "No need to add a title just add the critical analysis.";

std::string activate_artical_downlaoder(int argc, char* argv[])
{
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

int activate_artical_extractor_to_file(const std::string& path)
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

std::unique_ptr<ArticalProcessing::Artical> activate_artical_extractor_to_Artical(const std::string& path)
{
    std::unique_ptr<ArticalProcessing::Artical> artical = nullptr;
    try
    {
        artical = ArticalScraper::HtmlExtractor::htmlDataExtractorToArtical(path);
        std::cout << "successfully extracted " + path + " to Artical Object\n";
    }
    catch (const std::ios_base::failure& e)
    {
        std::cerr << e.what() << "\n";
    }
    return std::move(artical);
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


int test_HtmlExtracor_and_designer_without_LLM(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Wrong number of arguments, can accept 2 only.";
        return EXIT_FAILURE;
    }

    std::string path1;
    path1 = activate_artical_downlaoder(argc, argv);

    std::unique_ptr<ArticalProcessing::Artical> artical = activate_artical_extractor_to_Artical(path1);
    if (!artical)
    {
        return EXIT_FAILURE;
    }

    ArticalProcessing::ArticalHtmlDesigner designer(*artical);

    try
    {
        std::string htmlPath = designer.generateDefaultHtmlFile();
        return EXIT_SUCCESS;
    }
    catch (const std::ios_base::failure& e)
    {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
}

int test_Basic_LLM_client(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Wrong number of arguments, can accept 2 only.";
        return EXIT_FAILURE;
    }
    const char* key_cstr = std::getenv("OPENAI_API_KEY");
    if (key_cstr == nullptr)
    {
        std::cerr << "API key not found in environment variables." << std::endl;
        return EXIT_FAILURE;
    }
    std::string key(key_cstr);
    LLM::client clnt(key);

    try
    {
        std::string request;
        for (int i = 1; i < argc; i++)
        {
            request.append(argv[i]);
            request.append(" ");
        }
        std::cout << clnt.getResponse(request);
        return EXIT_SUCCESS;
    }
    catch (std::runtime_error& e)
    {
        std::cout << "failed to generate LLM response" << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

int test_LLM_response_To_Article(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Wrong number of arguments, can accept 2 only.";
        return EXIT_FAILURE;
    }

    std::string path1;
    path1 = activate_artical_downlaoder(argc, argv);

    std::unique_ptr<ArticalProcessing::Artical> artical = activate_artical_extractor_to_Artical(path1);
    if (!artical)
    {
        return EXIT_FAILURE;
    }

    std::string articalTxt = artical->getArticleText();

    const char* key_cstr = std::getenv("OPENAI_API_KEY");
    if (key_cstr == nullptr)
    {
        std::cerr << "API key not found in environment variables." << std::endl;
        return EXIT_FAILURE;
    }
    std::string key(key_cstr);
    LLM::client clnt(key);

    try
    {
        std::string request;
        for (int i = 2; i < argc; i++)
        {
            request.append(argv[i]);
            request.append(" ");
        }
        request.append(articalTxt);

        // Convert UTF-8 string to wstring for wcout
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring wideResponse = converter.from_bytes(clnt.getResponse(request));

        std::wcout << wideResponse << std::endl;
        return EXIT_SUCCESS;
    }
    catch (std::runtime_error& e)
    {
        std::cerr << "Failed to generate LLM response: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

int test_Html_designer_with_LLM(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Wrong number of arguments, can accept 2 only.";
        return EXIT_FAILURE;
    }

    std::string path1;
    path1 = activate_artical_downlaoder(argc, argv);

    std::unique_ptr<ArticalProcessing::Artical> artical = activate_artical_extractor_to_Artical(path1);
    if (!artical)
    {
        return EXIT_FAILURE;
    }

    const char* key_cstr = std::getenv("OPENAI_API_KEY");
    if (key_cstr == nullptr)
    {
        std::cerr << "API key not found in environment variables." << std::endl;
        return EXIT_FAILURE;
    }
    std::string key(key_cstr);
    LLM::client clnt(key);


    //add requests to artical
    LLM::Request request;
    try
    {
        request = LLM::Request(REQUEST1,
                             artical->getArticleText(),
                             "Critical Analysis", clnt);
        artical->addRequest(request);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "failed to run test of html desighn with LLM request added.\n" << e.what() << std::endl;
        return EXIT_FAILURE;
    }


    ArticalProcessing::ArticalHtmlDesigner designer(*artical);

    try
    {
        std::string htmlPath = designer.generateDefaultHtmlFile();
        std::cout << "Succecful Html with LLM created!!!" << std::endl;
        return EXIT_SUCCESS;
    }
    catch (const std::ios_base::failure& e)
    {
        std::cerr << e.what() << "\n";
        return EXIT_FAILURE;
    }
}