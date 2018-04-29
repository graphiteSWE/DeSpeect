#ifndef COMMANDLIST_H
#define COMMANDLIST_H
#include "abstractcommand.h"
#include <list>
#include "string"
#include "configuration.h"
#include <bits/stl_map.h>

//List of commands that allow execution of command, (to be checked if useless)
//and request memory command to the engine of speect that he is working with
class CommandList
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
        CommandList* Commands;
    public:
        //constructor of the builder
        CommandBuilder(Speect* engine);
        //destructor of the builder
        ~CommandBuilder();
        //return the builded commandList
        CommandList* getCommandList();
        //add command of processors given the lists of name don't check if they actual exists
        CommandBuilder &WithProcessors(const std::list<std::string>&);
        //add the command needed to save audio given the output file, by default save as wav
        CommandBuilder& SaveAudio(const std::string&, const std::string & format="riff");
        //add the commands to set the configuration of the speect engine
        CommandBuilder& LoadConfig(const Configuration::configName&,const std::string&);

    };
    //virtual ~CommandList()=0;
    //execute all commands in the lists, empty the list, and fill the log with their return
    void executeAll();
    //execute first command the the list fill the log and pop the command from the list
    void executeStep();
    //return the error log of the command executed and clear all the returned one from the log
    std::list<std::string> getErrorState();

    //Clear ErrorLog list
    void clearErrorState();
    //allow to add a command to the list
    void addCommand(AbstractCommand*);
    //allow to queue a commandlist to this command list
    void addCommand(CommandList&);
    //return the numbers of command in the list
    int getNumberCommands();

    //this method allow to get data from the engine on which the command are gonna run

    //return the named Relation if exist otherwise NULL
    const Relation* getRelation(const std::string &)const;
    //return the list of relation name
    const std::list<std::string> getRelationNames()const ;
    //return all the utterance processors name
    const std::list<std::string> getUttProcessorsNames()const;
    //return all the utterance processor name in the selected utterance type
    const std::list<std::string> getUttProcessorsNames(const std::string&)const;
    //return all the utterance type name defined in the loaded voice
    const std::list<std::string> getUttTypeNames()const;
    //return the data of the node given relation and path from head (ID of a graphic Node)
    const std::map<std::string,std::string> getNode(const std::string& rel,const std::string& path);

private:

    //don't allow construction outside the builder
    CommandList();
    CommandList(Speect* engine);

};
#endif // COMMANDLIST_H
