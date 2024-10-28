#include "ObjectItem.h"
#include "ArrayItem.h"
#include "StringItem.h"
#include "BoolItem.h"
#include "FloatItem.h"
#include "IntItem.h"

namespace json
{
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wdelete-incomplete"
    ObjectItem::~ObjectItem()
    {
        while (this->value->size())
        {
            std::map<std::string, CommonItem>::iterator iterator = this->value->begin();
            CommonItem item = iterator->second;

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
    #pragma GCC diagnostic pop
    
    std::string ObjectItem::toString() const
    {
        std::string str = "{\n";
        int i = 0;
    
        for (const auto& [key, item]: *this->value)
        {
            ++i;
            std::string keyStr = "\"" + key + "\": ";
    
            if (typeid(StringItem).hash_code() == item.getType()->hash_code())
                str += keyStr + "\"" + static_cast<StringItem*>(item.getItem())->toString() + "\"";
            else if (typeid(ArrayItem).hash_code() == item.getType()->hash_code())
                str += keyStr + static_cast<ArrayItem*>(item.getItem())->toString();
            else if (typeid(BoolItem).hash_code() == item.getType()->hash_code())
                str += keyStr + static_cast<BoolItem*>(item.getItem())->toString();
            else if (typeid(FloatItem).hash_code() == item.getType()->hash_code())
                str += keyStr + static_cast<FloatItem*>(item.getItem())->toString();
            else if (typeid(IntItem).hash_code() == item.getType()->hash_code())
                str += keyStr + static_cast<IntItem*>(item.getItem())->toString();
            else if (typeid(ObjectItem).hash_code() == item.getType()->hash_code())
                str += keyStr + static_cast<ObjectItem*>(item.getItem())->toString();
            else
                continue;
    
            if (i != this->value->size())
                str += ",";
            str += "\n";
        }
    
        str += "}";
    
        return str;
    }
    
    CommonItem ObjectItem::get(std::string key)
    {
        return this->value->at(key);
    }
    
    CommonItem ObjectItem::operator[](std::string key)
    {
        return this->get(key);
    }
    
    std::ostream& operator<<(std::ostream& out, const ObjectItem& objectItem)
    {
        out << objectItem.toString();
        return out;
    }
    
    std::ostream& operator<<(std::ostream& out, const ObjectItem* objectItem)
    {
        out << objectItem->toString();
        return out;
    }
    
    int ObjectItem::getLength()
    {
        return this->value->size();
    }
    
    bool ObjectItem::contains(std::string key)
    {
        return this->value->count(key);
    }
    
    std::map<std::string, CommonItem>::const_iterator ObjectItem::begin()
    {
        return this->value->cbegin();
    }
    
    std::map<std::string, CommonItem>::const_iterator ObjectItem::end()
    {
        return this->value->cend();
    }
    
    void ObjectItem::erase(std::string key)
    {
        this->value->erase(key);
    }

    void ObjectItem::erase(std::map<std::string, CommonItem>::const_iterator iterator)
    {
        this->value->erase(iterator);
    }

    void ObjectItem::erase(
            std::map<std::string, CommonItem>::const_iterator start,
            std::map<std::string, CommonItem>::const_iterator end
        )
    {
        this->value->erase(start, end);
    }
}