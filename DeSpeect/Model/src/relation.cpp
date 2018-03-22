#include "relation.h"
Relation::Relation(Item item, const std::__cxx11::string &name)
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
