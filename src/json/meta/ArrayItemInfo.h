#pragma once
#include "MetaInfo.h"
#include <string>

namespace json
{
    class ArrayItemInfo: public MetaInfo
    {
    protected:
        MetaInfo* value = nullptr;
    public:
        virtual PARSING_ELEMENT getType() override;
        void setValue(MetaInfo* value);
        MetaInfo* getValue();
        virtual std::string toString() override;
    };
}
