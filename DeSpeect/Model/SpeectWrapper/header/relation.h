#ifndef RELATION_H
#define RELATION_H
#include "string"
#include "item.h"

/*
 * File: relation.h
 * Type: header
 * Date: 2018-04-20
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: models a SRelation by keeping the head of the graph and the its name
 */
 
class Relation
{
private:

    //Field: head of the relation
    Item relationHead;

    //Field: name of the relation
    std::string name;
public:

    /*
    * Description: Relation constructor
    * @param const Item &item - head of the relation
    * @param const std::string& name - name of the relation
    */
    Relation(const Item &item, const std::string& name);
 
    /*
     * Description: returns the name of the relation
     * @return const std::string& 
     */
    const std::string& getName()const ;
    
    /*
     * Description: returns the head of the relation
     * @return Item 
     */
    Item getRelationHead()const;
};
#endif // RELATION_H
