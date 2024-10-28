#pragma once
#include "JsonParserState.h"
#include "AppendState.h"
#include "../meta/BoolInfo.h"
#include "../exceptions/JsonParseException.h"

namespace json
{
    class BoolState: public JsonParserState
    {
    public:
        BoolState(std::stack<MetaInfo*>* state);
        virtual JsonParserState* next(char c) override;
    };
}