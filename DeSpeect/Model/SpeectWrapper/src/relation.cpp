#include "relation.h"

/*
 * File: relation.cpp
 * Type: src
 * Date: 2018-04-20
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: models a SRelation by keeping the head of the graph and the its name
 */
 
/*
* Description: Relation constructor
* @param const Item &item - head of the relation
* @param const std::string& name - name of the relation
*/
Relation::Relation(const Item& item, const std::string &name)
    :relationHead(item)
    ,name(name)
{
}

/*
 * Description: returns the name of the relation
 * @return const std::string& 
 */
const std::string &Relation::getName() const
{
    return name;
}

/*
 * Description: returns the head of the relation
 * @return Item 
 */
Item Relation::getRelationHead() const
{
    return relationHead;
}
