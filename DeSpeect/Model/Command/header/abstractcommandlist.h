#ifndef ABSTRACTCOMMANDLIST_H
#define ABSTRACTCOMMANDLIST_H
#include "abstractcommand.h"
#include <list>
#include "string"
//List of abstract command
class AbstractCommandList
{
private:
    std::list<AbstractCommand*> commands;
    std::list<std::string> ErrorLog;

public:
    //AbstractCommandList(Speect* engine);
    //virtual ~AbstractCommandList()=0;

    virtual void executeAll();
    virtual void executeStep();

    virtual std::list<std::string> getErrorState() const;
    virtual void clearErrorState();

    virtual void addCommand(AbstractCommand*);
    virtual void addCommand(AbstractCommandList&);

/*
    + getRelation(std::string)
    + getRelationNames()
    + getConfiguration()
    + getUttProcessorsNames()
*/

};
#endif // ABSTRACTCOMMANDLIST_H
