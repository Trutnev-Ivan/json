#pragma once
#include "MetaInfo.h"
#include <cctype>
#include <string>

namespace json
{
    class BoolInfo: public MetaInfo
    {
    private:
        bool isValidChar(char c);
    protected:
        std::string value;
    public:
        const static int FALSE_LENGTH = 5;
        const static int TRUE_LENGTH = 4;
        virtual PARSING_ELEMENT getType() override;
        void appendChar(char c);
        std::string getValue();
        virtual std::string toString() override;
    };
}