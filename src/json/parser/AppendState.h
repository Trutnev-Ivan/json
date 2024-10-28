#pragma once

#include "JsonParserState.h"
#include "ObjectItemState.h"
#include "ObjectState.h"
#include "ArrayItemState.h"
#include "ArrayState.h"
#include "../meta/ObjectItemInfo.h"
#include "../meta/ObjectInfo.h"
#include "../meta/ArrayItemInfo.h"
#include "../meta/ArrayInfo.h"

namespace json
{
    class AppendState: public JsonParserState
    {
    protected:
        JsonParserState* appendToObject(MetaInfo* metaInfo, bool mustNextElem);
        JsonParserState* appendToObjectItem(MetaInfo* metaInfo);
        JsonParserState* appendToArrayItem(MetaInfo* metaInfo);
        JsonParserState* appendToArray(MetaInfo* metaInfo, bool mustNextElem);
        JsonParserState* append(MetaInfo* metaInfo);
    public:
        AppendState(std::stack<MetaInfo*>* stack);
        virtual JsonParserState* next(char c) override;
    };
}