#pragma once

#include "JsonParserState.h"
#include "ObjectState.h"
#include "ArrayState.h"
#include "../meta/ObjectInfo.h"
#include "../meta/ArrayInfo.h"

namespace json
{
    class StartState: public JsonParserState
    {
    public:
        StartState(std::stack<MetaInfo*>* stack);
        virtual JsonParserState* next(char c) override;
    };
}