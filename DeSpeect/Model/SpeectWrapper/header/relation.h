#ifndef RELATION_H
#define RELATION_H
#include "string"
#include "item.h"
//model a SRelation only keeping the head of the graph and the name
class Relation
{
private:
    Item relationHead;
    std::string name;
public:
    Relation(const Item &item, const std::string& name);
    ~Relation();
    //return the relation name
    const std::string& getName()const ;
    //return the relationhead
    Item getRelationHead()const;
};
#endif // RELATION_H
