#ifndef COMMANDLIST_H
#define COMMANDLIST_H
#include "abstractcommand.h"
#include <list>
#include "string"
#include "configuration.h"
#include <bits/stl_map.h>
//List of abstract command
class CommandList
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
        CommandList* Commands;
    public:
        CommandBuilder(Speect* engine);
        ~CommandBuilder();
        CommandList* getCommandList();
        CommandBuilder &WithProcessors(const std::list<std::string>&);
        CommandBuilder& SaveAudio(const std::string&, const std::string & format="riff");
        CommandBuilder &SaveUtteranceAs(const std::string&,const std::string&);
        CommandBuilder& LoadPlugins(const std::list<const std::string>&);
        CommandBuilder& LoadConfig(const Configuration::configName&,const std::string&);

    };
    //virtual ~CommandList()=0;
    void executeAll();
    void executeStep();

    std::list<std::string> getErrorState();
    void clearErrorState();

    void addCommand(AbstractCommand*);
    void addCommand(CommandList&);

    int getNumberCommands();

    const Relation* getRelation(const std::string &)const;
    const std::list<std::string> getRelationNames()const ;
    const Configuration* getConfiguration()const;
    const std::list<std::string> getUttProcessorsNames()const;
    const std::list<std::string> getUttProcessorsNames(const std::string&)const;
    const std::list<std::string> getUttTypeNames()const;
    const std::map<std::string,std::string> getNode(const std::string& rel,const std::string& path);

private:
    CommandList();
    CommandList(Speect* engine);

};
#endif // COMMANDLIST_H
