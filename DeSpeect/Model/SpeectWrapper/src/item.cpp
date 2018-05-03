#include "item.h"
#include "speect.h"

/*
 * File: item.cpp
 * Type: src
 * Date: 2018-04-20
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: an item iterates over the SItem and allows to get and set data, it has no responsibility about the memory management
 */
 
/*
* Description: Item constructor
* @param SItem* - Speect item
* @param const std::string& id - ID representing the path from the head of the relationship to the node
*/
Item::Item(SItem * i, const std::string &id)
    :item(i)
    ,ID(id)
{
    s_erc error=S_SUCCESS;
}

/*
* Description: item copy constructor
* @param const Item& - item to be copied
*/
Item::Item(const Item &other)
    :ID(other.ID)
{
    item=other.item;
}

//Description: item destructor
Item::~Item()
{

}

/*
* Description: check if the pointer is NULL
* @return bool
*/
bool Item::isNull() const
{
    return item==NULL;
}

/*
* Description: check if next is valid
* @return bool
*/
bool Item::hasNext()const
{
    s_erc error=S_SUCCESS;
    return SItemNext(item,&error)!=NULL;
}

/*
* Description: check if previous is valid
* @return bool
*/
bool Item::hasPrev()const
{

    s_erc error=S_SUCCESS;
    return SItemPrev(item,&error)!=NULL;
}

/*
* Description: check if daughter is valid
* @return bool
*/
bool Item::hasDaughter()const
{

    s_erc error=S_SUCCESS;
    return SItemDaughter(item,&error)!=NULL;
}

/*
* Description: check if father is valid
* @return bool
*/
bool Item::hasFather() const
{

    s_erc error=S_SUCCESS;
    return SItemParent(item,&error)!=NULL;
}

/*
* Description: check if the item belongs to the given relation
* @param const std::string & - relation
* @return bool
*/
bool Item::checkRelation(const std::string&relation) const
{
    s_erc error=S_SUCCESS;
return (relation==SRelationName(SItemRelation(item,&error),&error));
}

/*
* Description: returns a pointer to the next item (without checking if it's valid)
* @return Item
*/
Item Item::next() const
{
    s_erc error=S_SUCCESS;

    return Item(SItemNext(item,&error),ID+".n");
}

/*
* Description: returns a pointer to the daughter (without checking if it's valid)
* @return Item
*/
Item Item::daughter() const
{

    s_erc error=S_SUCCESS;
    return Item(SItemDaughter(item,&error),ID+".daughter");
}

/*
* Description: returns a pointer to the previous item (without checking if it's valid)
* @return Item
*/
Item Item::prev() const
{
    s_erc error=S_SUCCESS;
    return Item(SItemPrev(item,&error),ID+".p");
}

/*
* Description: returns a pointer to the father (without checking if it's valid)
* @return Item
*/
Item Item::father() const
{
    s_erc error=S_SUCCESS;
    return Item(SItemParent(item,&error),ID+".parent");

}

/*
* Description: returns the ID that is the path of the item from the head item of the relation
* @return std::string
*/
const std::string& Item::getId() const
{
    return ID;
}

/*
* Description: returns the name of the item
* @return std::string
*/
const std::string Item::getName() const
{
    s_erc error=S_SUCCESS;
    if(SItemFeatureIsPresent(item,"name",&error))
        return SItemGetName(item,&error);
    else
        return "";
}

/*
* Description: check if the SItem is equal to the SItem found in the given relation at the given Path
* 			   using Speect equals function. Returns:
* 					- 0 if !equal 
* 					- 1 if equal and same relation 
* 					- 2 if equal and different relations
* @param const std::string& - first item path
* @param const std::string& - second item path
* @return int
*/
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
