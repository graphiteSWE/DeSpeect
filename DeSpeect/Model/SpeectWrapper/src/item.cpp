#include "item.h"
#include "speect.h"
//build the item from the speect item and the id that rappresent the path from the head of the relation
Item::Item(SItem * i, const std::string &id)
    :item(i)
    ,ID(id)
{
    s_erc error=S_SUCCESS;
}

Item::Item(const Item &other)
    :ID(other.ID)
{
    item=other.item;
}

Item::~Item()
{

}
//return if items is null
bool Item::isNull() const
{
    return item==NULL;
}
//return if item has next
bool Item::hasNext()const
{
    s_erc error=S_SUCCESS;
    return SItemNext(item,&error)!=NULL;
}

//return if item has prev
bool Item::hasPrev()const
{

    s_erc error=S_SUCCESS;
    return SItemPrev(item,&error)!=NULL;
}

//return if item has daughter
bool Item::hasDaughter()const
{

    s_erc error=S_SUCCESS;
    return SItemDaughter(item,&error)!=NULL;
}
//return if item has father
bool Item::hasFather() const
{

    s_erc error=S_SUCCESS;
    return SItemParent(item,&error)!=NULL;
}

bool Item::checkRelation(const std::string&relation) const
{
    s_erc error=S_SUCCESS;
return (relation==SRelationName(SItemRelation(item,&error),&error));
}
//return the next item
Item Item::next() const
{
    s_erc error=S_SUCCESS;

    return Item(SItemNext(item,&error),ID+".n");
}
//return the daughter item
Item Item::daughter() const
{

    s_erc error=S_SUCCESS;
    return Item(SItemDaughter(item,&error),ID+".daughter");
}

Item Item::prev() const
{
    s_erc error=S_SUCCESS;
    return Item(SItemPrev(item,&error),ID+".p");
}

Item Item::father() const
{
    s_erc error=S_SUCCESS;
    return Item(SItemParent(item,&error),ID+".parent");

}
//return the id of this node
const std::string& Item::getId() const
{
    return ID;
}

//return the name of the item
const std::string Item::getName() const
{
    s_erc error=S_SUCCESS;
    if(SItemFeatureIsPresent(item,"name",&error))
        return SItemGetName(item,&error);
    else
        return "";
}
/*
//set the name at the given value
bool Item::setName(const std::string &value)
{
    s_erc error=S_SUCCESS;
    SItemSetName(item,value.c_str(),&error);
    return error==S_SUCCESS;
}
*/
//return if item isEqual to the item of the relation at given path
int Item::IsEqual(const std::string &relation,const std::string& id)const
{
    s_erc error=S_SUCCESS;
    //if relation is equal only check Id otherwise must retrieve the SItem
    bool rel=checkRelation(relation);
    const SItem* item2=
            SItemPathToItem(
                SRelationHead(
                    SUtteranceGetRelation(
                        SItemUtterance(item,&error),relation.c_str(),&error
                        ),&error
                    ),id.c_str(),&error);
    int result=0;
    if(rel)
        result=item==item2?1:0;
    else
        //otherwise relation is different retrieve the item at given path and test Speect equals
        result=SItemEqual(item,item2,&error)?2:0;
    S_DELETE(item2,NULL,&error);
    return result;
}
