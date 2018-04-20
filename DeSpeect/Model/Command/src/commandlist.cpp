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
std::list<std::string> CommandList::getErrorState() const{
   return ErrorLog;
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

int CommandList::getNumberCommands(){
    return commands.size();

}

const Relation* CommandList::getRelation(const std::string& relation)const
{
    if(Speectengine->getUtterance()!=NULL)
    {
        return Speectengine->getUtterance()->getRelationByName(relation);
    }
    else
        return NULL;


}

const std::list<std::string> CommandList::getRelationNames() const
{
    if(Speectengine->getUtterance()!=NULL){
        return Speectengine->getUtterance()->getRelationNamesList();
    }
    return std::list<std::string>();
}

const Configuration *CommandList::getConfiguration() const
{

}

const std::list<std::string> CommandList::getUttProcessorsNames() const
{
    return Speectengine->getUttProcessorNames();
}



CommandList::CommandList(Speect *engine)
    :Speectengine(engine)
{

}
//builder
CommandList::CommandBuilder::CommandBuilder(Speect *engine)
   :engine(engine)
   ,Commands(new CommandList(engine))
{

}

CommandList::CommandBuilder::~CommandBuilder()
{
    delete Commands;
}

CommandList *CommandList::CommandBuilder::getCommandList()
{
    auto tempPtr=new CommandList(engine);
    tempPtr->addCommand(*Commands);
    return tempPtr;
}

CommandList::CommandBuilder &CommandList::CommandBuilder::WithProcessors(const std::list<std::string> &ProcessorsList)
{
    for (auto ProcessorName=ProcessorsList.begin();ProcessorName!=ProcessorsList.end();++ProcessorName) {
        Commands->commands.push_back(new UttProcessorCommand(*ProcessorName));
    }
    return *this;
}

CommandList::CommandBuilder &CommandList::CommandBuilder::SaveAudio(const std::string & outPutFile, const std::string& format)
{
    Commands->commands.push_back(new SetSpeectConfigCommand(Configuration::Audio,outPutFile));
    Commands->commands.push_back(new CreateAudioCommand(format));
    return *this;
}

CommandList::CommandBuilder &CommandList::CommandBuilder::SaveUtteranceAs(const std::string &, const std::string &)
{
    return *this;
}

CommandList::CommandBuilder &CommandList::CommandBuilder::LoadPlugins(const std::list<const std::string> & plugins)
{
 /*   for(auto PluginName=plugins.begin();PluginName!=plugins.end();++PluginName) {
        Commands.push_back(new LoadPluginCommand((*PluginName)));
    }*/
    return *this;
}

CommandList::CommandBuilder &CommandList::CommandBuilder::LoadConfig(const Configuration::configName &config, const std::string &value)
{
    Commands->commands.push_back(new SetSpeectConfigCommand(config,value));
    return *this;
}
