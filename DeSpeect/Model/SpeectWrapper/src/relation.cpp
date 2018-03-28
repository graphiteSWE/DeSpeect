#include "relation.h"
Relation::Relation(const Item& item, const std::string &name)
    :relationHead(item)
    ,name(name)
{
}

Relation::~Relation()
{
}
//return relations name
const std::string &Relation::getName() const
{
    return name;
}
//return head iterator
Item Relation::getRelationHead() const
{
    return relationHead;
}
