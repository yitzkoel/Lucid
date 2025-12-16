//
// Created by yitzk on 9/8/2025.
//

#include "Article.h"

namespace ArticleProcessing {


    void Article::addTextToArtical(const std::string& text)
    {
        this->set_article_text(this->getArticleText() + text);
    }

} // ArticalProccessing