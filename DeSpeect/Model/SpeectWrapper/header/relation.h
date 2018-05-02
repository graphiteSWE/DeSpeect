#ifndef RELATION_H
#define RELATION_H
#include "string"
#include "item.h"
//model a SRelation only keeping the head of the graph and the name
class Relation
{
private:
    //head of the relation
    Item relationHead;

    //name of the relation
    std::string name;

public:
    //create the SRelation wrapper
    Relation(const Item &item, const std::string& name);

    //return the relation name
    const std::string& getName() const;

    //return the relationhead
    Item getRelationHead() const;

};
#endif // RELATION_H
