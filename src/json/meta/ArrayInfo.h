#pragma once
#include "MetaInfo.h"
#include "ArrayItemInfo.h"
#include <vector>

namespace json
{
    class ArrayInfo: public MetaInfo
    {
    protected:
        std::vector<ArrayItemInfo*> items;
    public:
        virtual PARSING_ELEMENT getType() override;
        void append(ArrayItemInfo* item);
        virtual std::string toString() override;
        int size();
        ArrayItemInfo* operator[](int index);
    };
}