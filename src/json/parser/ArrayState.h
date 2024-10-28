#pragma once
#include "JsonParserState.h"
#include "EndState.h"
#include "StringState.h"
#include "ObjectState.h"
#include "NumberState.h"
#include "BoolState.h"
#include "../meta/ArrayItemInfo.h"
#include "../meta/StringInfo.h"
#include "../meta/ObjectInfo.h"
#include "../meta/NumberInfo.h"
#include "../meta/BoolInfo.h"

namespace json
{
    class ArrayState: public JsonParserState
    {
    protected:
        bool isMustNextElement = false;
    public:
        ArrayState(std::stack<MetaInfo*>* stack);
        virtual JsonParserState* next(char c) override;
        void mustNextElement();
    };
}