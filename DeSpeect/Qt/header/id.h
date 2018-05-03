#ifndef ID_H
#define ID_H
#include <QString>

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
 
class ID
{
private:
	
	//Field: identification code
    QString id;
    
    //Field: identified relation
    QString relation;
public:
    
    /*
     * Description: redefinition of the == operator, checks equality between two IDs (never used)
     * @param const ID& - ID to be compared
     * @return bool 
     */
    bool operator ==(const ID& )const;
    
    /*
     * Description: ID constructor 
     * @param const QString& - identifier
     * @param const QString& - relation
     */
    ID(const QString&,const QString&);
    
    /*
     * Description: redefinition of the = operator, sets assignment
     * @param const ID& - ID to be assigned
     * @return ID & 
     */
    ID &operator =(const ID&);

    /*
     * Description: returns the identification code
     * @return const QString& 
     */
    const QString& getID()const;
    
    /*
     * Description: returns the relation
     * @return const QString& 
     */
    const QString& getRelation() const;
};

#endif // ID_H
