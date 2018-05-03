#ifndef UTTERANCE_H
#define UTTERANCE_H
class Relation;
#include "speect.h"
#include "string"
#include "list"

/*
 * File: utterance.h
 * Type: header
 * Date: 2018-04-20
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: SUtterance wrapper
 */
 
class Utterance
{
private:
    //Field: Speect utterance (see Speect documentation for more information)
    SUtterance* utt;
public:

    /*
     * Description: Utterance constructor
     * @param SUtterance* - Speect utterance 
     */
    explicit Utterance(SUtterance*);
    
    /*
     * Description: returns the inner pointer used to run Speect methods that require a SUtterance
     * @return SUtterance *
     */
    SUtterance *getUtterance()const;
    
    //Description: Utterance destructor 
    ~Utterance();
    
    /*
     * Description: returns the relation by name
     * @param const std::string &name - name of the relation
     * @return Relation* 
     */
    Relation* getRelationByName(const std::string &name) const;
    
    /*
     * Description: returns all the relations names as a list
     * @return const std::list<std::string>
     */
    const std::list<std::string> getRelationNamesList() const;
};
#endif // UTTERANCE_H
