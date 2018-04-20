#ifndef ABSTRACTCOMMANDLIST_H
#define ABSTRACTCOMMANDLIST_H
#include "abstractcommand.h"
#include <list>
#include "string"
#include "configuration.h"
//List of abstract command
class AbstractCommandList
{
private:
    std::list<AbstractCommand*> commands;
    std::list<std::string> ErrorLog;
    Speect* Speectengine;

public:
    class CommandBuilder
    {
    private:
        Speect* engine;
        AbstractCommandList* Commands;
    public:
        CommandBuilder(Speect* engine);
        ~CommandBuilder();
        AbstractCommandList* getCommandList();
        CommandBuilder &WithProcessors(const std::list<std::string>&);
        CommandBuilder& SaveAudio(const std::string&, const std::string & format="riff");
        CommandBuilder &SaveUtteranceAs(const std::string&,const std::string&);
        CommandBuilder& LoadPlugins(const std::list<const std::string>&);
        CommandBuilder& LoadConfig(const Configuration::configName&,const std::string&);

    };
    //virtual ~AbstractCommandList()=0;
    void executeAll();
    void executeStep();

    std::list<std::string> getErrorState() const;
    void clearErrorState();

    void addCommand(AbstractCommand*);
    void addCommand(AbstractCommandList&);

    int getNumberCommands();

    const Relation* getRelation(const std::string &)const;
    const std::list<std::string> getRelationNames()const ;
    const Configuration* getConfiguration()const;
    const std::list<std::string> getUttProcessorsNames()const;


private:
    AbstractCommandList();
    AbstractCommandList(Speect* engine);

};
#endif // ABSTRACTCOMMANDLIST_H
