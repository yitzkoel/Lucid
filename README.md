# Lucid

![License](https://img.shields.io/badge/license-MIT-blue)

A command-line tool that transforms cluttered online articles into clean, reader-friendly layouts.

## About The Project

Like many people, I was frustrated with the online reading experience. Most news sites and blogs are filled with distracting ads, auto-playing videos, and popups that make it difficult to focus on the content.

Lucid was born from a simple idea: download the article's text and re-format it in a clean, minimalist, and distraction-free view in your browser. It lets you focus on what matters: the text itself.

As a bonus feature, it also leverages the OpenAI API to generate an AI-powered analysis of the article.

**A Note on Technology:** You might wonder why this project was built in C++ instead of a more common web language like JavaScript. The reason is simple: it was a great opportunity for me to practice and deepen my C++ skills while solving a problem I genuinely care about.

## Features

-    **Distraction-Free Reading**: Extracts article text and displays it in a clean, simple HTML layout.
-    **AI-Powered Analysis**: Generates and appends an AI summary/analysis using the OpenAI API.
-    **Simple CLI**: An easy-to-use command-line interface to load, view, and manage articles.
-    **Export to HTML**: Save the clean article layout as an HTML file on your machine.

## Installation

### For Users (Using `Lucid.exe`)

1.  Download the `Lucid.exe` file from the [Releases page](https://github.com/yitzkoel/Lucid).
2.  Download the `articleTemplate.html` file.
3.  **Important:** Place both `Lucid.exe` and `articleTemplate.html` in the same directory.
4.  Run `Lucid.exe` to start the program.

### For Developers (Building from Source)

**Prerequisites:**
* This software is developed and tested for **Windows 64-bit**.
* **libcurl**: Installation instructions can be found on the [official cURL website](https://curl.se/).
* **nlohmann/json**: This is a header-only library. The required `json.h` file is already included in the `include/` directory of this project.

Once prerequisites are met, clone the repository and compile the source code using your preferred C++ compiler.

## Configuration

### OpenAI API Key

To use the AI analysis feature, you must have an OpenAI API key.

1.  Open PowerShell on your Windows machine.
2.  Set your API key as an environment variable by running the following command (replace the placeholder with your actual key):
    ```powershell
    $env:OPENAI_API_KEY="YOUR_SECRET_KEY_HERE"
    ```
3.  The program will now be able to access the key and make calls to the OpenAI API.

## Usage

Once `Lucid.exe` is running, you can use the following commands in the terminal:

-   `load [URL]` - Loads the article from the given URL.
    -   *Example: `load https://www.some-news-site.com/article`*
-   `open` - Opens the cleaned-up article in your default web browser.
-   `addAnalysis` - Generates an AI analysis and adds it to the bottom of the article.
-   `removeAnalysis` - Removes the AI analysis from the article.
-   `exportTo [PATH]` - Exports the generated HTML file to a specified directory.
    -   *Example: `exportTo C:\Users\YourName\Desktop`*
-   `exit` - Terminates the program.

## Important Limitations

Please be aware of the following limitations:

-   **No JavaScript Rendering**: The program can only parse content directly present in the initial HTML. It cannot process articles on pages that rely on JavaScript to load their content dynamically.
-   **Article Content Only**: The URL provided should point directly to an article page. The parsing logic is not designed to work on main pages or site indexes.
-   **Limited Testing**: This tool has primarily been tested on major Israeli news websites as of 2025. Its effectiveness may vary on other sites.

## Roadmap & Future Ideas

Here are some potential improvements and ideas for the future:

-   **Switch to a HTML Parser**: Replace the current regex-based text extraction with a robust HTML parsing library (like Gumbo) to improve speed and compatibility with more websites.
-   **Browser Extension**: Create a Chrome/Firefox extension that automatically provides a "Read in Lucid" button when visiting an article link.
-   **Automated Testing**: Implement a test suite with known websites and edge cases to ensure reliability and make future development easier.
-   **Live Chatbot**: Extend the project to include a live AI chatbot that can answer questions about the article content, verify facts, or find opposing viewpoints online.

## Contact

If you have any questions or suggestions, feel free to reach out.

-   **Email**: yitzkoel@gmail.com
-   **LinkedIn**: (Add your link here when ready)

## License

This project is licensed under the MIT License - see the `LICENSE` file for details.