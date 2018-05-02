#ifndef UTTERANCE_H
#define UTTERANCE_H
class Relation;
#include "speect.h"
#include "string"
#include "list"
//this class wrap SUtterance
class Utterance
{
private:
    //speect utterance,see speect documentation for more information
    SUtterance* utt;
public:
    //set the utterance of this object with a utterance of speect
    Utterance(SUtterance*);
    //return the inner pointer used to run speect methods that require a SUtterance
    SUtterance *getUtterance()const;
    //delete the inner utterance
    ~Utterance();
    //return the relation by name ownership of object to caller
    Relation* getRelationByName(const std::string &name)const;
    //return all the relations name as a list ownership of list to caller
    const std::list<std::string> getRelationNamesList()const;
};
#endif // UTTERANCE_H
