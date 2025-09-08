# Lucid
Project goals:
1. create noise free article layout (nothing but the article and assistive data).
2. add LLM to webpage with quires (maby summery maby critic);
3. give articles layout based on different political bias(not sure how to implement maby an opposing suggested view
at the end of the article with a link )
4. Optional: adding features to 2: having at he same page apposing views with LLM generated analysis. 
5. Very far ambition : a truth Monitor, a easily accessed database that hold the records of officials and media people
opions and recorded dishonesty, (can have video, audio, court records, police record and every data publicly available
to back it up).

The goals are listed in order of importance and progression.
                
possible class layeout:
/MediaSummarizerProject/
│
├── main.cppgit
├── Manager/
│   └── Manager.hpp / .cpp
│
├── ArticleScraper/    (Util)
│   ├── HtmlExtractor.hpp / .cpp
│
│
├── ArticleDesigner(add the html design to the website + upload featurs to URL that is push command)
│
│
├──ArticalUplaoder(to some URL just a push operation);
│
│
├── Article (a optional class that will be created if further analysys of artical is neede)
│
│
├── LLMRequester/ (strategy design )
│   ├── Requester.hpp / .cpp
│   ├── Question.hpp / .cpp
│   ├── QuestionFactory.hpp / .cpp
│


discription:
create a ArticalExtractor folder in it we will have 
Extractor class: gives the raw HTML text without unnecessary garbage in a standard fashion

ArticalDesigner - adds html design features to article based on other classes.

**still need to think about the design.**
Artical class : creates a article object with: 1. author, title, summery, date, website,
subject, actual article text, and anything other that is needed.
**still need to think about the design.**
 
**still need to think about the design.**
create a LLMRequester folder and in it:
create question Object subclass of text.
maby a bunch of different question types and a factory to create them
create a Requester class that has a method that gets a list of text objects,
a question object and runs the LLM accordingly and saves the answer in a text Object.
**still need to think about the design.**

creat a Manager that can mange all the features classes
basiclly the manager will be a handle that can create mult articals can downlaod html proccess them, desighn them() etc.
add a shell class that will take care of shell user interface. 

