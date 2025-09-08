//
// Created by yitzk on 9/8/2025.
//

#ifndef ARTICALHTMLDESIGNER_H
#define ARTICALHTMLDESIGNER_H
#include <string>

#include "Artical.h"

namespace ArticalProcessing {
    struct Dir
    {
        static constexpr const char* LTR = "ltr";
        static constexpr const char* RTL = "rtl";
    };

    struct Language
    {
        static constexpr const char* EN = "en";  // english
        static constexpr const char* HEB = "he"; // hebrew
    };

class ArticalHtmlDesigner {
    public:
        void addHtmlTag(Artical &artical);
        void addLanguage(Artical &artical, Dir &dir, Language &lng);
        void addTitle(Artical &artical);
        void addPublishTime(Artical &artical);
        void addPublisherData(Artical &artical);
        void addArticalText(Artical &artical);
};

} // ArticalProcessing

#endif //ARTICALHTMLDESIGNER_H
