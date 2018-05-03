#ifndef ITEM_H
#define ITEM_H
#include "speect.h"
#include "string"

/*
 * File: item.h
 * Type: header
 * Date: 2018-04-20
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: an item iterates over the SItem and allows to get and set data, it has no responsibility about the memory management
 */
 
class Item
{
private:
    //Field: Speect SItem
    SItem* item;
    //Field: ID representing the path from the head of the relation up to the node
    std::string ID;
public:
    
    /*
    * Description: Item constructor
    * @param SItem* - Speect item
    * @param const std::string& id - ID representing the path from the head of the relationship to the node
    */
    Item(SItem*,const std::string& id=" ");
    
    /*
    * Description: item copy constructor
    * @param const Item& - item to be copied
    */
    Item(const Item&);
    
    //Description: item destructor
    ~Item();
    
    /*
    * Description: check if the pointer is NULL
    * @return bool
    */
    bool isNull()const;
    
    /*
    * Description: check if next is valid
    * @return bool
    */
    bool hasNext()const;
    
    /*
    * Description: check if previous is valid
    * @return bool
    */
    bool hasPrev()const;
    
    /*
    * Description: check if daughter is valid
    * @return bool
    */
    bool hasDaughter()const;
    
    /*
    * Description: check if father is valid
    * @return bool
    */
    bool hasFather()const;
    
    /*
    * Description: check if the item belongs to the given relation
    * @param const std::string & - relation
    * @return bool
    */
    bool checkRelation(const std::string &)const;
    
    /*
    * Description: returns a pointer to the next item (without checking if it's valid)
    * @return Item
    */
    Item next()const;
    
    /*
    * Description: returns a pointer to the daughter (without checking if it's valid)
    * @return Item
    */
    Item daughter()const;
    
    /*
    * Description: returns a pointer to the previous item (without checking if it's valid)
    * @return Item
    */
    Item prev()const;
    
    /*
    * Description: returns a pointer to the father (without checking if it's valid)
    * @return Item
    */
    Item father()const;

    /*
    * Description: returns the ID that is the path of the item from the head item of the relation
    * @return std::string
    */
    const std::string &getId()const;
    
    /*
    * Description: returns the name of the item
    * @return std::string
    */
    const std::string getName()const;
    
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
    int IsEqual(const std::string&, const std::string &) const;

};
#endif // ITEM_H
