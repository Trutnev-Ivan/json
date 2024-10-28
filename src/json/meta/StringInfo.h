#pragma once

#include "MetaInfo.h"
#include <string>

namespace json
{
    class StringInfo: public MetaInfo
    {
    protected:
        char quoteType;
        char prevChar;
        std::string value;
    public:
        StringInfo(char quoteType);
        char getQuoteType();
        bool isEscaped();
        std::string getValue();
        void appendChar(char c);
        virtual PARSING_ELEMENT getType() override;
        virtual std::string toString() override;
    };
}