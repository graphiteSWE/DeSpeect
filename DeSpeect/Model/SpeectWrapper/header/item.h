#ifndef ITEM_H
#define ITEM_H
#include "speect.h"
#include "string"
//this item only iterate over the SItem and allow to get and set data
//have no responsibility of memory
class Item
{
private:
    //SItem of speect
    SItem* item;
    //ID that rappresent the path from the head of relationship to nod
    std::string ID;
public:
    //construct the item
    Item(SItem*,const std::string& id="");
    //check if pointer is NULL
    bool isNull()const;
    bool hasNext()const;
    bool hasPrev()const;
    bool hasDaughter()const;
    bool hasFather()const;
    //return the pointer to the item don't do check
    Item next();
    Item daughter();
    Item prev();
    Item father();
    //return the Id that is the path of item
    const std::string &getId()const;
    //return the name of the item
    const std::string getName()const;
    //set the name of the item
    bool setName(const std::string&);
    //check if this SItem is equal to the SItem found in the given relation at given Path
    //using Speect equals function
    bool IsEqual(const std::string&, const std::string &) const;


};
#endif // ITEM_H
