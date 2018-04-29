#ifndef ABSTRACTCOMMANDLIST_H
#define ABSTRACTCOMMANDLIST_H
#include "abstractcommand.h"
#include <list>
#include "string"
#include "configuration.h"
//List of abstract command that allow execution of command, (to be checked if useless)
//and request memory command to the engine of speect that he is working with
class AbstractCommandList
{
private:
    //list of command to be executed
    std::list<AbstractCommand*> commands;
    //stack of the log that each command return
    std::list<std::string> ErrorLog;
    //wrapper that contains the data that every command uses
    Speect* Speectengine;

public:
    //builder of a AbstractCommandList
    class CommandBuilder
    {
    private:
        //engine that is gonna be used by the command list
        Speect* engine;
        //list of command of the command list
        AbstractCommandList* Commands;
    public:
        //constructor of the builder
        CommandBuilder(Speect* engine);
        //destructor of the builder
        ~CommandBuilder();
        //return the builded commandList
        AbstractCommandList* getCommandList();
        //add command of processors given the lists of name don't check if they actual exists
        CommandBuilder &WithProcessors(const std::list<std::string>&);
        //add the command needed to save audio given the output file, by default save as wav
        CommandBuilder& SaveAudio(const std::string&, const std::string & format="riff");
        //add the command to save utterance as the type in the given format (not implemented)
        CommandBuilder &SaveUtteranceAs(const std::string&,const std::string&);
        //add the commands to loads the plugins into the speect engine
        CommandBuilder& LoadPlugins(const std::list<const std::string>&);
        //add the commands to set the configuration of the speect engine
        CommandBuilder& LoadConfig(const Configuration::configName&,const std::string&);

    };
    //execute all commands in the lists, empty the list, and fill the log with their return
    void executeAll();
    //execute first command the the list fill the log and pop the command from the list
    void executeStep();
    //return the error state of the speect engine
    std::list<std::string> getErrorState() const;
    void clearErrorState();
    //allow to add a command to the list
    void addCommand(AbstractCommand*);
    //allow to queue a commandlist to this command list
    void addCommand(AbstractCommandList&);
    //return the numbers of command in the list
    int getNumberCommands();
    //return the named Relation if exist otherwise NULL
    const Relation* getRelation(const std::string &)const;
    //return the list of relation name
    const std::list<std::string> getRelationNames()const ;
    //return the configuration class
    const Configuration* getConfiguration()const;
    //return the utterance processors name in the current utterance type
    const std::list<std::string> getUttProcessorsNames()const;


private:
    //don't allow construction of command list outside of builder
    AbstractCommandList();
    AbstractCommandList(Speect* engine);

};
#endif // ABSTRACTCOMMANDLIST_H
