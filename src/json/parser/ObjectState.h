#pragma once

#include "JsonParserState.h"
#include "EndState.h"
#include "ObjectItemState.h"
#include "AppendState.h"
#include "../meta/ObjectItemInfo.h"

namespace json
{
    class ObjectState: public JsonParserState
    {
    protected:
        bool isMustNextElem = false;
    public:
        ObjectState(std::stack<MetaInfo*>* stack);
        virtual JsonParserState* next(char c) override;
        void mustNextElem();
    };
}