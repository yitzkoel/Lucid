
#include <memory>
#include "ArticleScraper/HtmlExtractor.h"
#include "UserInterface/Shell.h"
//#include "Tests/tests.cpp"     ********TODO**********


int main(int argc, char* argv[])
{
    //return test_HtmlExtractor_class(argc, argv);
    //return test_HtmlExtracor_and_designer(argc,argv);

    //return test_Basic_LLM_client(argc, argv);

    //return test_Html_designer_with_LLM(argc, argv);


    // // Set console to UTF-8 output
    // _setmode(_fileno(stdout), _O_U8TEXT);
    //
    // return test_LLM_response_To_Article(argc, argv);






    // GLOBAL INITIALIZATION (Call ONCE at program start)
    CURLcode init_res = curl_global_init(CURL_GLOBAL_DEFAULT);
    if (init_res != CURLE_OK) {
        // Handle error: libcurl couldn't initialize properly
        return 1;
    }

    auto shell = UserInterface::Shell::create();
    return shell->run();
}
