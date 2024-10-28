#include "ObjectItemState.h"

namespace json
{
    ObjectItemState::ObjectItemState(std::stack<MetaInfo*>* stack):
        JsonParserState(stack)
        {
            ObjectItemInfo* objectItemInfo = static_cast<ObjectItemInfo*>(this->parsingElement->top());

            if (objectItemInfo->getValue() != nullptr)
            {
                isFilledKey = true;
                isFilledValue = true;
                hasDelimiter = true;
            }
        }

    JsonParserState* ObjectItemState::next(char c)
    {
        if (!isFilledKey)
        {
            parseKey(c);
            return this;
        }
        else if (!hasDelimiter)
        {
            parseDelimiter(c);
            return this;
        }
        else if (!isFilledValue)
        {
            return parseValue(c);
        }
        else
        {
            return parseEnd(c);
        }
    }

    void ObjectItemState::parseKey(char c)
    {
        ObjectItemInfo* objectItemInfo = static_cast<ObjectItemInfo*>(this->parsingElement->top());

        if (objectItemInfo->getKeyQuotesType() == c)
        {
            if (objectItemInfo->isEscaped())
                objectItemInfo->appendToKey(c);
            else
            {
                objectItemInfo->endKeyParse();
                isFilledKey = true;
            }
        }
        else
        {
            objectItemInfo->appendToKey(c);
        }
    }

    void ObjectItemState::parseDelimiter(char c)
    {
        if (std::isspace(c))
            return;

        if (c == ':')
        {
            hasDelimiter = true;
            return;
        }

        throw JsonObjectItemDelimiterException();
    }

    JsonParserState* ObjectItemState::parseValue(char c)
    {
        if (std::isspace(c))
            return this;

        if (c == '\'' || c == '"')
        {
            this->parsingElement->push(new StringInfo(c));
            return new StringState(this->parsingElement);
        }
        else if (c == '{')
        {
            this->parsingElement->push(new ObjectInfo);
            return new ObjectState(this->parsingElement);
        }
        else if (c == '[')
        {
            this->parsingElement->push(new ArrayInfo);
            return new ArrayState(this->parsingElement);
        }
        else if (std::isdigit(c) || c == '-')
        {
            this->parsingElement->push(new NumberInfo);
            NumberState* numberState = new NumberState(this->parsingElement);
            return numberState->next(c);
        }
        else if (c == 't' || c == 'f')
        {
            this->parsingElement->push(new BoolInfo);
            BoolState* boolState = new BoolState(this->parsingElement);
            return boolState->next(c);
        }

        throw JsonParseException(c);
    }

    JsonParserState* ObjectItemState::parseEnd(char c)
    {
        if (std::isspace(c))
            return this;

        if (c == ',')
        {
            AppendState* appendState = new AppendState(this->parsingElement);
            JsonParserState* next = appendState->next(c);

            delete appendState;
            return next;
        }
        else if (c == '}')
        {
            AppendState* appendState = new AppendState(this->parsingElement);
            JsonParserState* next = appendState->next(c);

            delete appendState;
            return next->next(c);
        }

        throw JsonParseException(c);
    }
}