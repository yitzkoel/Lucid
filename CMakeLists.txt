cmake_minimum_required(VERSION 3.28)
project(Lucid)
set(CMAKE_CXX_STANDARD 20)

# --- Static linking and compatibility flags ---
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")

add_definitions(
        -DCURL_STATICLIB
        -D__USE_MINGW_ANSI_STDIO=1
        -D__MINGW_USE_VC2005_COMPAT
)

# --- Include paths ---
set(CURL_INCLUDE_DIR "C:/libs/curl-8.16.0_4-win64-mingw/curl-8.16.0_4-win64-mingw/include")
include_directories(${CURL_INCLUDE_DIR})

# --- Shim for missing MinGW symbols ---
file(WRITE ${CMAKE_BINARY_DIR}/winfix.cpp
        "#include <sys/stat.h>\n"
        "extern \"C\" {\n"
        "  // emulate __sys_nerr + __sys_errlist imports\n"
        "  int __sys_nerr = 0;\n"
        "  int* __imp___sys_nerr = &__sys_nerr;\n"
        "  const char* __sys_errlist[] = {\"(none)\"};\n"
        "  const char** __imp___sys_errlist = __sys_errlist;\n"
        "\n"
        "  // emulate stat64i32 used by libpsl\n"
        "  int stat64i32(const char* path, struct _stati64* buf) {\n"
        "    return _stati64(path, buf);\n"
        "  }\n"
        "}\n"
)


# --- Executable ---
add_executable(Lucid
        main.cpp
        ArticleScraper/HtmlExtractor.cpp
        ArticalProcessing/ArticleHtmlDesigner.cpp
        ArticalProcessing/Article.cpp
        LLM/client.cpp
        LLM/Request.cpp
        Util/StringUtil.cpp
        UserInterface/Shell.cpp
        UserInterface/Command.cpp
        UserInterface/LoadCommand.cpp
        UserInterface/AnalysisCommand.cpp
        UserInterface/ExportCommand.cpp
        UserInterface/OpenCommand.cpp
        UserInterface/ExitCommand.cpp
        Util/FileUtil.cpp
        UserInterface/CommandFactory.cpp
        ${CMAKE_BINARY_DIR}/winfix.cpp
        #Tests/tests.cpp   ********TODO
)

# --- Link all required libs ---
target_link_libraries(Lucid
        PRIVATE
        # Core curl + crypto
        C:/libs/curl-8.16.0_4-win64-mingw/curl-8.16.0_4-win64-mingw/lib/libcurl.a
        C:/libs/curl-8.16.0_4-win64-mingw/curl-8.16.0_4-win64-mingw/lib/libssl.a
        C:/libs/curl-8.16.0_4-win64-mingw/curl-8.16.0_4-win64-mingw/lib/libcrypto.a

        # Protocol/compression libs
        C:/libs/curl-8.16.0_4-win64-mingw/curl-8.16.0_4-win64-mingw/lib/libnghttp2.a
        C:/libs/curl-8.16.0_4-win64-mingw/curl-8.16.0_4-win64-mingw/lib/libnghttp3.a
        C:/libs/curl-8.16.0_4-win64-mingw/curl-8.16.0_4-win64-mingw/lib/libngtcp2.a
        C:/libs/curl-8.16.0_4-win64-mingw/curl-8.16.0_4-win64-mingw/lib/libngtcp2_crypto_libressl.a
        C:/libs/curl-8.16.0_4-win64-mingw/curl-8.16.0_4-win64-mingw/lib/libssh2.a
        C:/libs/curl-8.16.0_4-win64-mingw/curl-8.16.0_4-win64-mingw/lib/libz.a
        C:/libs/curl-8.16.0_4-win64-mingw/curl-8.16.0_4-win64-mingw/lib/libpsl.a
        C:/libs/curl-8.16.0_4-win64-mingw/curl-8.16.0_4-win64-mingw/lib/libbrotlidec.a
        C:/libs/curl-8.16.0_4-win64-mingw/curl-8.16.0_4-win64-mingw/lib/libbrotlicommon.a
        C:/libs/curl-8.16.0_4-win64-mingw/curl-8.16.0_4-win64-mingw/lib/libzstd.a

        # Windows system libs
        ws2_32
        wldap32
        crypt32
        normaliz
        bcrypt
        secur32
        iphlpapi
        version
        advapi32
        user32
        gdi32
        kernel32
        shell32
)