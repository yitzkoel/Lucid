//
// Created by yitzk on 9/8/2025.
//

#include "Artical.h"

namespace ArticalProcessing {
    void Artical::addToArticalText(std::string text)
    {
        this->set_articla_text(this->getArticleText() + text);
    }
} // ArticalProccessing