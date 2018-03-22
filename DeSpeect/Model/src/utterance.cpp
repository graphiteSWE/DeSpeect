#include "utterance.h"

#include <item.h>
#include <relation.h>
Utterance::Utterance(SUtterance *u)
    :utt(u)
{

}

SUtterance *Utterance::getUtterance() const
{
    return utt;
}

Utterance::~Utterance()
{
    s_erc error=S_SUCCESS;
    S_DELETE(utt,NULL,&error);
}

Relation *Utterance::getRelationByName(const std::string &name) const
{
    s_erc error=S_SUCCESS;
    return new Relation(Item(SRelationHead(SUtteranceGetRelation(utt,name.c_str(),&error),&error)),name);
}

std::list<std::string> Utterance::getRelationNamesList() const
{
    s_erc error=S_SUCCESS;
    SList* temp=SUtteranceRelationsKeys(utt,&error);
    std::list<std::string> l;
    while(!SListIsEmpty(temp,&error))
    {

        SObject*obj=SListPop(temp,&error);
        l.push_front(std::string(SObjectGetString(obj,&error)));
        S_DELETE(obj,NULL,&error);
    }
    S_DELETE(temp,NULL,&error);
    return l;
}
