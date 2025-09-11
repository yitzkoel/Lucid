//
// Created by yitzk on 9/8/2025.
//

#include "Artical.h"

namespace ArticalProcessing {
    void Artical::addTextToArtical(const std::string& text)
    {
        this->set_article_text(this->getArticleText() + text);
    }

} // ArticalProccessing