#include "commandlist.h"
#include <createaudiocommand.h>
#include <loadplugincommand.h>
#include <setspeectconfigcommand.h>
#include <uttprocessorcommand.h>

//Invokes the execute method of all commands in the list and clean the list
void CommandList::executeAll(){
    while(!commands.empty()){
        CommandList::executeStep();
    }

}

//Invokes the execute method of the first command in the list and remove command
void CommandList::executeStep(){
    if(!commands.empty()){
        AbstractCommand* pHead=*(commands.begin());
        commands.pop_front();

        ErrorLog.push_back(pHead->execute(Speectengine));
        delete pHead;
    }
}

//Return ErrorLog list
std::list<std::string> CommandList::getErrorState(){
   std::list<std::string>Error(ErrorLog);
   ErrorLog.clear();
   return Error;
}


//Clear ErrorLog list
void CommandList::clearErrorState(){
   ErrorLog.clear();
}

//Add command to list commands
void CommandList::addCommand(AbstractCommand* command){
    commands.push_back(command);
}


//Add all commands inside listOfCommands
void CommandList::addCommand(CommandList &listOfCommands){
     while(!listOfCommands.commands.empty()){
         AbstractCommand* command=*(listOfCommands.commands.begin());
         addCommand(command);
         listOfCommands.commands.pop_front();
     }

}
//return the numbers of commmand in the list
int CommandList::getNumberCommands(){
    return commands.size();

}
//if utterance exists return the relation if exists otherwisse null
const Relation* CommandList::getRelation(const std::string& relation)const
{
    if(Speectengine->getUtterance()!=NULL)
    {
        return Speectengine->getUtterance()->getRelationByName(relation);
    }
    else
        return NULL;


}

//return all the relation names or an empty list
const std::list<std::string> CommandList::getRelationNames() const
{
    if(Speectengine->getUtterance()!=NULL){
        return Speectengine->getUtterance()->getRelationNamesList();
    }
    return std::list<std::string>();
}
//return all utterance processor names
const std::list<std::string> CommandList::getUttProcessorsNames() const
{
    return Speectengine->getUttProcessorNames();
}
//return the utterance processor names of the given utt type
const std::list<std::string> CommandList::getUttProcessorsNames(const std::string &uttType) const
{
    return Speectengine->getUttProcessorNames(uttType);
}

//return all the utterance type names
const std::list<std::string> CommandList::getUttTypeNames() const
{
    return Speectengine->getUttTypeName();
}

//return the nodes information
const std::map<std::string, std::string> CommandList::getNode(const std::string &rel, const std::string &path)
{
    return Speectengine->getNode(rel,path);
}


CommandList::CommandList(Speect *engine)
    :Speectengine(engine)
{

}

/**
  start of command builder method definition
**/

//create a builder for an engine
CommandList::CommandBuilder::CommandBuilder(Speect *engine)
   :engine(engine)
   ,Commands(new CommandList(engine))
{

}

//destroy the builder
CommandList::CommandBuilder::~CommandBuilder()
{
    delete Commands;
}

//create the commandlist
CommandList *CommandList::CommandBuilder::getCommandList()
{
    auto tempPtr=new CommandList(engine);
    tempPtr->addCommand(*Commands);
    return tempPtr;
}
//add processors command to the list
CommandList::CommandBuilder &CommandList::CommandBuilder::WithProcessors(const std::list<std::string> &ProcessorsList)
{
    for (auto ProcessorName=ProcessorsList.begin();ProcessorName!=ProcessorsList.end();++ProcessorName) {
        Commands->commands.push_back(new UttProcessorCommand(*ProcessorName));
    }
    return *this;
}
//add command to save audio to the list
CommandList::CommandBuilder &CommandList::CommandBuilder::SaveAudio(const std::string & outPutFile, const std::string& format)
{
    Commands->commands.push_back(new SetSpeectConfigCommand(Configuration::Audio,outPutFile));
    Commands->commands.push_back(new CreateAudioCommand(format));
    return *this;
}

//add command to set a config to the list
CommandList::CommandBuilder &CommandList::CommandBuilder::LoadConfig(const Configuration::configName &config, const std::string &value)
{
    Commands->commands.push_back(new SetSpeectConfigCommand(config,value));
    return *this;
}
