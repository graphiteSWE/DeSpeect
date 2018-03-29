#ifndef ID_H
#define ID_H

#include <QString>


//ID of a node
//id is the path to the phisical node from the head of his relation
//relation is the relation of the phisical node
//id is unique in a relation but not between different relations
class ID
{
private:
    const QString id;
    const QString relation;
public:
    //check equals between two nodes (never used)
    bool operator ==(const ID& )const;
    //constructor
    ID(const QString&,const QString&);
    //getters

    const QString& getID()const;
    const QString& getRelation() const;
};

#endif // ID_H
