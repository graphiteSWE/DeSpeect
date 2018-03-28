#ifndef ID_H
#define ID_H

#include <QString>



class ID
{
private:
    const QString id;
    const QString relation;
public:
    bool operator ==(const ID& )const;
    ID(const QString&,const QString&);
    const QString& getID()const;
    const QString& getRelation() const;
};

#endif // ID_H
