cmake_minimum_required(VERSION 3.28)


# Toolchain for vcpkg
set(CMAKE_TOOLCHAIN_FILE "C:/Users/yitzk/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project(Lucid)

# Make sure C++ standard is set
set(CMAKE_CXX_STANDARD 20)

# Find and link libcurl
find_package(CURL REQUIRED)

# Add the executable with all needed source files
add_executable(Lucid
        main.cpp
        ArticleScraper/HtmlExtractor.cpp
        ArticleScraper/HtmlExtractor.h
        ArticalProcessing/ArticalHtmlDesigner.cpp
        ArticalProcessing/ArticalHtmlDesigner.h
        ArticalProcessing/Artical.cpp
        ArticalProcessing/Artical.h
        LLM/client.cpp
        LLM/client.h
        LLM/client.h
)

# Link libcurl
target_link_libraries(Lucid PRIVATE CURL::libcurl)

