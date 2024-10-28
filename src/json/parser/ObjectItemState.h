#pragma once

#include "JsonParserState.h"
#include "StringState.h"
#include "AppendState.h"
#include "ArrayState.h"
#include "NumberState.h"
#include "BoolState.h"
#include "../meta/ObjectItemInfo.h"
#include "../meta/StringInfo.h"
#include "../meta/ArrayInfo.h"
#include "../meta/NumberInfo.h"
#include "../meta/BoolInfo.h"

namespace json
{
    class ObjectItemState: public JsonParserState
    {
    protected:
        bool isFilledKey = false;
        bool isFilledValue = false;
        bool hasDelimiter = false;
    
        void parseKey(char c);
        void parseDelimiter(char c);
        JsonParserState* parseValue(char c);
        JsonParserState* parseEnd(char c);
    
    public:
        ObjectItemState(std::stack<MetaInfo*>* stack);
        virtual JsonParserState* next(char c) override;
    };
}