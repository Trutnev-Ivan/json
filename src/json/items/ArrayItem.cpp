#include "ArrayItem.h"
#include "ObjectItem.h"
#include "StringItem.h"
#include "BoolItem.h"
#include "FloatItem.h"
#include "IntItem.h"
#include <cstring>

namespace json
{
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdelete-incomplete"
    ArrayItem::~ArrayItem()
    {
        if (this->value != nullptr)
        {
            while (this->value->size())
            {
                std::list<CommonItem>::iterator iterator = this->value->begin();
                CommonItem item = *iterator;

                if (item.getItem() != nullptr)
                {
                    if (typeid(ArrayItem).hash_code() == item.getType()->hash_code())
                        delete static_cast<ArrayItem*>(item.getItem());
                    else if (typeid(ObjectItem).hash_code() == item.getType()->hash_code())
                        delete static_cast<ObjectItem*>(item.getItem());
                    else
                        delete item.getItem();
                }

                this->value->erase(iterator);
            }

            delete this->value;
        }
    }
    #pragma GCC diagnostic pop
    
    std::type_index* ArrayItem::getType(int index)
    {
        return this->get(index).getType();
    }
    
    int ArrayItem::getLength()
    {
        return this->value->size();
    }
    
    std::string ArrayItem::toString() const
    {
        std::string str = "[";
    
        for (int i = 0; i < this->value->size(); ++i)
        {   
            CommonItem item = this->get(i);
    
            if (typeid(StringItem).hash_code() == item.getType()->hash_code())
                str += "\"" + static_cast<StringItem*>(item.getItem())->toString() + "\"";
            else if (typeid(ArrayItem).hash_code() == item.getType()->hash_code())
                str += static_cast<ArrayItem*>(item.getItem())->toString();
            else if (typeid(BoolItem).hash_code() == item.getType()->hash_code())
                str += static_cast<BoolItem*>(item.getItem())->toString();
            else if (typeid(FloatItem).hash_code() == item.getType()->hash_code())
                str += static_cast<FloatItem*>(item.getItem())->toString();
            else if (typeid(IntItem).hash_code() == item.getType()->hash_code())
                str += static_cast<IntItem*>(item.getItem())->toString();
            else if (typeid(ObjectItem).hash_code() == item.getType()->hash_code())
                str += static_cast<ObjectItem*>(item.getItem())->toString();
    
            if (i != this->value->size() - 1)
                str += ", ";
        }
        
        str += "]";
    
        return str;
    }
    
    std::ostream& operator<<(std::ostream& out, const ArrayItem& arrayItem)
    {
        out << arrayItem.toString();
        return out;
    }
    
    std::ostream& operator<<(std::ostream& out, const ArrayItem* arrayItem)
    {
        out << arrayItem->toString();
        return out;
    }
    
    CommonItem ArrayItem::get(int index) const
    {
        if (index >= this->value->size())
            throw std::out_of_range("Index out of range");

        std::list<CommonItem>::iterator iterator = this->value->begin();
        std::advance(iterator, index);
        return *iterator;
    }
    
    CommonItem ArrayItem::pop()
    {
        CommonItem item = this->get(this->getLength() - 1);
        this->getValue()->pop_back();
        return item;
    }
    
    std::list<CommonItem>::const_iterator ArrayItem::begin()
    {
        return this->value->cbegin();
    }
    
    std::list<CommonItem>::const_iterator ArrayItem::end()
    {
        return this->value->cend();
    }
    
    void ArrayItem::erase(int index)
    {
        std::list<CommonItem>::const_iterator iterator = this->begin();
        std::advance(iterator, index);
        this->value->erase(iterator);
    }
    
    void ArrayItem::erase(std::list<CommonItem>::const_iterator iterator)
    {
        this->value->erase(iterator);
    }
    
    void ArrayItem::erase(int start, int end)
    {
        std::list<CommonItem>::const_iterator startIterator = this->begin();
        std::list<CommonItem>::const_iterator endIterator = this->begin();
        std::advance(startIterator, start);
        std::advance(endIterator, end);
        this->value->erase(startIterator, endIterator);
    }
    
    void ArrayItem::erase(
            std::list<CommonItem>::const_iterator startIterator,
            std::list<CommonItem>::const_iterator endIterator
            )
            {
                this->value->erase(startIterator, endIterator);
            }
    
    CommonItem ArrayItem::operator[](int index)
    {
        return this->get(index);
    }
}