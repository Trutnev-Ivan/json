#include "CommonItem.h"

namespace json
{
    CommonItem::CommonItem()
    {
        this->item = nullptr;
        this->type = nullptr;
    }
    
    CommonItem::CommonItem(CommonItem& item)
    {
        this->item = item.getItem();
        this->type = new std::type_index(*item.getType());
        this->size = item.getSize();
    }
    
    CommonItem::CommonItem(const CommonItem& item)
    {
        this->item = item.getItem();
        this->type = new std::type_index(*item.getType());
        this->size = item.getSize();
    }
    
    CommonItem::CommonItem(CommonItem* item)
    {
        this->item = item->getItem();
        this->type = new std::type_index(*item->getType());
        this->size = item->getSize();
    }
    
    CommonItem::~CommonItem()
    {
        delete this->type;
    }
    
    void* CommonItem::getItem() const
    {
        return this->item;
    }
    
    std::type_index* CommonItem::getType() const
    {
        return this->type;
    }
    
    int CommonItem::getSize() const
    {
        return this->size;
    }
}