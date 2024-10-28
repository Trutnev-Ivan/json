#pragma once
#include <typeindex>
#include "JsonItem.h"
#include "../exceptions/JsonItemTypeException.h"

namespace json
{
    class CommonItem
    {
    protected:
        std::type_index* type = nullptr;
        void* item = nullptr;
        int size;
    public:
        CommonItem();
        CommonItem(CommonItem& item);
        CommonItem(const CommonItem& item);
        CommonItem(CommonItem* item);
        ~CommonItem();
        void* getItem() const;
        std::type_index* getType() const;
        int getSize() const;

        template<class T>
        void init(T* item)
        {
            if (!JsonItem<void*>::isInstanceOfJsonItem<T>())
                throw JsonItemTypeException();

            this->item = static_cast<void*>(item);
            this->type = new std::type_index(typeid(T));
            this->size = sizeof(T);
        }
    };
}