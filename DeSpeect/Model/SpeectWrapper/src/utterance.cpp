#include "utterance.h"
#include <item.h>
#include <relation.h>

/*
 * File: utterance.cpp
 * Type: src
 * Date: 2018-04-20
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: SUtterance wrapper
 */
 
/*
 * Description: Utterance constructor
 * @param SUtterance* - Speect utterance 
 */
Utterance::Utterance(SUtterance *u)
    :utt(u)
{

}

/*
 * Description: returns the inner pointer used to run Speect methods that require a SUtterance
 * @return SUtterance *
 */
SUtterance *Utterance::getUtterance() const
{
    return utt;
}

//Description: Utterance destructor 
Utterance::~Utterance()
{
    s_erc error=S_SUCCESS;
    S_DELETE(utt,NULL,&error);
}

/*
 * Description: returns the relation by name
 * @param const std::string &name - name of the relation
 * @return Relation* 
 */
Relation* Utterance::getRelationByName(const std::string &name) const
{
    s_erc error=S_SUCCESS;
    return new Relation(Item(SRelationHead(SUtteranceGetRelation(utt,name.c_str(),&error),&error)),name);
}

/*
 * Description: returns all the relations names as a list
 * @return const std::list<std::string>
 */
const std::list<std::string> Utterance::getRelationNamesList() const
{
    s_erc error=S_SUCCESS;
    SList* temp=NULL;
    if(utt)
        temp=SUtteranceRelationsKeys(utt,&error);

    std::list<std::string> l;
    if(temp!=NULL)
    {
        while(!SListIsEmpty(temp,&error))
        {

            SObject*obj=SListPop(temp,&error);
            l.push_front(std::string(SObjectGetString(obj,&error)));
            S_DELETE(obj,NULL,&error);
        }
        S_DELETE(temp,NULL,&error);
    }
    return l;
}
