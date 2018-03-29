#include "id.h"

const QString& ID::getRelation() const
{
    return relation;
}

bool ID::operator ==(const ID &other) const
{
    return id==other.id;
}

ID::ID(const QString& id,const QString& rel)
    :id(id)
    ,relation(rel)
{

}

const QString& ID::getID()const
{
    return id;
}


