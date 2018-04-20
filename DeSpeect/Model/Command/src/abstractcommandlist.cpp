#include "abstractcommandlist.h"

#include <createaudiocommand.h>
#include <loadplugincommand.h>
#include <setspeectconfigcommand.h>
#include <uttprocessorcommand.h>

//Invokes the execute method of all commands in the list and clean the list
void AbstractCommandList::executeAll(){
    while(!commands.empty()){
        AbstractCommandList::executeStep();
    }

}

//Invokes the execute method of the first command in the list and remove command
void AbstractCommandList::executeStep(){
    if(!commands.empty()){
        AbstractCommand* pHead=*(commands.begin());
        commands.pop_front();

        ErrorLog.push_back(pHead->execute(Speectengine));
        delete pHead;
    }
}

//Return ErrorLog list
std::list<std::string> AbstractCommandList::getErrorState() const{
   return ErrorLog;
}


//Clear ErrorLog list
void AbstractCommandList::clearErrorState(){
   ErrorLog.clear();
}

//Add command to list commands
void AbstractCommandList::addCommand(AbstractCommand* command){
    commands.push_back(command);
}


//Add all commands inside listOfCommands
void AbstractCommandList::addCommand(AbstractCommandList &listOfCommands){
     while(!listOfCommands.commands.empty()){
         AbstractCommand* command=*(listOfCommands.commands.begin());
         addCommand(command);
         listOfCommands.commands.pop_front();
     }

}

int AbstractCommandList::getNumberCommands(){
    return commands.size();

}

const Relation* AbstractCommandList::getRelation(const std::string& relation)const
{
    if(Speectengine->getUtterance()!=NULL)
    {
        return Speectengine->getUtterance()->getRelationByName(relation);
    }
    else
        return NULL;


}

const std::list<std::string> AbstractCommandList::getRelationNames() const
{
    if(Speectengine->getUtterance()!=NULL){
        return Speectengine->getUtterance()->getRelationNamesList();
    }
    return std::list<std::string>();
}

const Configuration *AbstractCommandList::getConfiguration() const
{

}

const std::list<std::string> AbstractCommandList::getUttProcessorsNames() const
{
    return Speectengine->getUttProcessorNames();
}



AbstractCommandList::AbstractCommandList(Speect *engine)
    :Speectengine(engine)
{

}
//builder
AbstractCommandList::CommandBuilder::CommandBuilder(Speect *engine)
   :engine(engine)
   ,Commands(new AbstractCommandList(engine))
{

}

AbstractCommandList::CommandBuilder::~CommandBuilder()
{
    delete Commands;
}

AbstractCommandList *AbstractCommandList::CommandBuilder::getCommandList()
{
    auto tempPtr=new AbstractCommandList(engine);
    tempPtr->addCommand(*Commands);
    return tempPtr;
}

AbstractCommandList::CommandBuilder &AbstractCommandList::CommandBuilder::WithProcessors(const std::list<std::string> &ProcessorsList)
{
    for (auto ProcessorName=ProcessorsList.begin();ProcessorName!=ProcessorsList.end();++ProcessorName) {
        Commands->commands.push_back(new UttProcessorCommand(*ProcessorName));
    }
    return *this;
}

AbstractCommandList::CommandBuilder &AbstractCommandList::CommandBuilder::SaveAudio(const std::string & outPutFile, const std::string& format)
{
    Commands->commands.push_back(new SetSpeectConfigCommand(Configuration::Audio,outPutFile));
    Commands->commands.push_back(new CreateAudioCommand(format));
    return *this;
}

AbstractCommandList::CommandBuilder &AbstractCommandList::CommandBuilder::SaveUtteranceAs(const std::string &, const std::string &)
{
    return *this;
}

AbstractCommandList::CommandBuilder &AbstractCommandList::CommandBuilder::LoadPlugins(const std::list<const std::string> & plugins)
{
 /*   for(auto PluginName=plugins.begin();PluginName!=plugins.end();++PluginName) {
        Commands.push_back(new LoadPluginCommand((*PluginName)));
    }*/
    return *this;
}

AbstractCommandList::CommandBuilder &AbstractCommandList::CommandBuilder::LoadConfig(const Configuration::configName &config, const std::string &value)
{
    Commands->commands.push_back(new SetSpeectConfigCommand(config,value));
    return *this;
}
