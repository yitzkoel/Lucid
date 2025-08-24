# MediaSuperviser
Project goals:
1. Create summery of israeli news in hebrew.
    features:
    a. Length of read time(that will give more or less detail.)
    b. Fields of interest modifications.
    c. political agenda modifications
    d. favorite reporters.
2. give articles layout based on different political bias.
3. Truth Monitor, a easily accessed database that hold the records of officails and media people being dishonest,
    and having video, audio, court records, police record and every data publicly available to back it up.
    maby even summered option on certain topics and conterdictions witha time scale(that is if somone changed his
    opionion but it is consistent with the time scale it is ok).

The goals are listed in order of importance.
                

class layeout:
/MediaSummarizerProject/
│
├── main.cpp
├── Manager/
│   └── Manager.hpp / .cpp
│
├── ArticleScraper/
│   ├── Extractor.hpp / .cpp
│   ├── Text.hpp
│   └── Article.hpp / .cpp
│
├── LLMRequester/
│   ├── Requester.hpp / .cpp
│   ├── Question.hpp / .cpp
│   ├── QuestionFactory.hpp / .cpp
│
├── Summarizer/
│   └── Summarizer.hpp / .cpp

discription:
create a ArticalExtracor folder in it we will have 
Extractor class: gives the raw HTML text without unnececery garbage
Text abstract class
Artical class inherets from Text class: creates a article object with: 1. author, title, summery, date, website, subject, actual article text, and anything other that is needed.


create a LLMRequester folder and in it:
create question Object subclass of text.
maby a bunch of different question types and a factory to create them
create a Requester class that has a method that gets a list of text objects, a question object and runs the LLM accordingly and saves the answer in a text Object.

create a Summerizer folder
1class summerizer: holds fields that customize the summery, and create a summery from text objects and question objects that were created using the customizing summery fields

creat a Manager that talks to the user and creates the summerizer and all

create a main that creates a summerizer
