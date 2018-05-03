#include "id.h"

/*
 * File: id.h
 * Type: header
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: models the ID of a node. 
 * 				ID is the path to the phisical node from the head of his relation where relation is the relation of the phisical node. 
 * 				The ID is unique within a relation but not among different relations
 */
 
/*
 * Description: returns the relation
 * @return const QString& 
 */
const QString& ID::getRelation() const
{
    return relation;
}

/*
 * Description: redefinition of the == operator, checks equality between two IDs (never used)
 * @param const ID& - ID to be compared
 * @return bool 
 */
bool ID::operator ==(const ID &other) const
{
    return id==other.id&&relation==other.relation;
}

/*
 * Description: ID constructor 
 * @param const QString& - identifier
 * @param const QString& - relation
 */
ID::ID(const QString& id,const QString& rel)
    :id(id)
    ,relation(rel)
{

}

/*
 * Description: redefinition of the = operator, sets assignment
 * @param const ID& - ID to be assigned
 * @return ID & 
 */
ID &ID::operator =(const ID &other)
{
    if(this!=&other)
    {
        this->id=QString(other.id);
        this->relation=QString(other.relation);
    }
    return *this;
}

/*
 * Description: returns the identification code
 * @return const QString& 
 */
const QString& ID::getID()const
{
    return id;
}


