#include "item.h"
#include "iostream"
//build the item from the speect item and the id that rappresent the path from the head of the relation
Item::Item(SItem * i, const std::string &id)
    :item(i)
    ,ID(id)
{
    s_erc error=S_SUCCESS;
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
//return the next item
Item Item::next()
{
    s_erc error=S_SUCCESS;

    return Item(SItemNext(item,&error),ID+".n");
}
//return the daughter item
Item Item::daughter()
{

    s_erc error=S_SUCCESS;
    return Item(SItemDaughter(item,&error),ID+".d");
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
bool Item::IsEqual(const std::string &relation,const std::string& id)const
{
    s_erc error=S_SUCCESS;
    //if relation is equal only check Id otherwise must retrieve the SItem
    bool checkRelation=(relation==SRelationName(SItemRelation(item,&error),&error)),checkId=(id==ID);
    if(checkRelation)
        //if relation is equal then return if id is equal
        return checkId;

    else
        //otherwise relation is different retrieve the item at given path and test Speect equals
        return SItemEqual(item,
                SItemPathToItem(
                    SRelationHead(
                        SUtteranceGetRelation(
                            SItemUtterance(item,&error)
                            ,relation.c_str(),&error)
                        ,&error)
                    ,id.c_str(),&error)
                ,&error);
}
