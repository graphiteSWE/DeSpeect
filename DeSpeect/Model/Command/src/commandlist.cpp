#include "commandlist.h"
#include <createaudiocommand.h>
#include <loadplugincommand.h>
#include <setspeectconfigcommand.h>
#include <uttprocessorcommand.h>
#include "regex"

/*
 * File: commandlist.cpp
 * Type: src
 * Date: 2018-04-20
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: list of commands that allows their execution
 */
 
/*
 * Description: executes all the commands in the list invoking their execute method, empties the list and fills the log with their return data
 * @return void
 */
void CommandList::executeAll(){
    while(!commands.empty()){
        CommandList::executeStep();
    }

}

/*
 * Description: executes the first command of the list, fills the log and pops the command from the list
 * @return void
 */
void CommandList::executeStep(){
    if(!commands.empty()){
        AbstractCommand* pHead=*(commands.begin());
        commands.pop_front();

        ErrorLog.push_back(pHead->execute(Speectengine));
        delete pHead;
    }
}

/*
 * Description: returns the error log of the executed command and clears all the ones returned from the log
 * @return std::list<std::string>
 */
std::list<std::string> CommandList::getErrorState(){
   std::list<std::string>Error(ErrorLog);
   ErrorLog.clear();
   return Error;
}

/*
 * Description: clears the ErrorLog list
 * @return std::void
 */
void CommandList::clearErrorState(){
   ErrorLog.clear();
}

/*
 * Description: allows to add a command to the list
 * @param AbstractCommand* - command to be added
 * @return std::void
 */
void CommandList::addCommand(AbstractCommand* command){
    commands.push_back(command);
}

/*
 * Description: allows to queue a commandlist to this command list
 * @param CommandList& - command list to be added
 * @return std::void
 */
void CommandList::addCommand(CommandList &listOfCommands){
     while(!listOfCommands.commands.empty()){
         AbstractCommand* command=*(listOfCommands.commands.begin());
         addCommand(command);
         listOfCommands.commands.pop_front();
     }

}

/*
 * Description: returns the number of commands in the list
 * @return std::int
 */
int CommandList::getNumberCommands(){
    return commands.size();

}

/*
 * Description: if exists, returns the named Relation, NULL otherwise
 * @param const std::string & - relation name
 * @return const Relation*
 */
const Relation* CommandList::getRelation(const std::string& relation)const
{
    if(Speectengine->getUtterance()!=NULL)
    {
        return Speectengine->getUtterance()->getRelationByName(relation);
    }
    else
        return NULL;

}

/*
 * Description: returns the list of the relations names
 * @return const std::list<std::string>
 */
const std::list<std::string> CommandList::getRelationNames() const
{
    if(Speectengine->getUtterance()!=NULL){
        return Speectengine->getUtterance()->getRelationNamesList();
    }
    return std::list<std::string>();
}

/*
 * Description: returns the list of the utterance processors names
 * @return std::list<std::string>
 */
const std::list<std::string> CommandList::getUttProcessorsNames() const
{
    return Speectengine->getUttProcessorNames();
}

/*
 * Description: returns the list of the utterance processors names in the selected utterance type
 * @param const std::string& - utterance type name
 * @return std::list<std::string>
 */
const std::list<std::string> CommandList::getUttProcessorsNames(const std::string &uttType) const
{
    return Speectengine->getUttProcessorNames(uttType);
}


/*
 * Description: returns the list of the utterance type names in the loaded voice
 * @return std::list<std::string>
 */
const std::list<std::string> CommandList::getUttTypeNames() const
{
    return Speectengine->getUttTypeName();
}

/*
 * Description: returns the data related to the node given a relation and the path from head (ID of a graphic Node)
 * @param const std::string& path - path to the node
 * @param const std::string& rel - relation name
 * @return const std::map<std::string,std::string>
 */
const std::map<std::string, std::string> CommandList::getNode(const std::string &rel, const std::string &path)
{
    std::string t="";
    auto map=Speectengine->getNode(path,rel);
    if(map.size()<=2)
        t+="Node search failed,Speect Status:";
    else
        t+="Node search success,Speect Status:";
    t+=s_error_str(Speectengine->getErrorState());
    ErrorLog.push_back(t);
    return map;
}


CommandList::CommandList(Speect *engine)
    :Speectengine(engine)
{

}



//Start of command builder method definition

/*
 * Description: builder constructor
 * @param Speect* engine - Speect reference
 */
CommandList::CommandBuilder::CommandBuilder(Speect *engine)
   :engine(engine)
   ,Commands(new CommandList(engine))
{

}

//Description: builder destructor
CommandList::CommandBuilder::~CommandBuilder()
{
    delete Commands;
}


/*
 * Description: returns the built CommandList
 * @return CommandList*
 */
CommandList *CommandList::CommandBuilder::getCommandList()
{
    auto tempPtr=new CommandList(engine);
    tempPtr->addCommand(*Commands);
    return tempPtr;
}

/*
 * Description: adds the commands related to the utterance processors whose names are in the given list (it doesn't check if they actually exist)
 * @param const std::list<std::string>& - list of the utterance processors names
 * @return CommandBuilder&
 */
CommandList::CommandBuilder &CommandList::CommandBuilder::WithProcessors(const std::list<std::string> &ProcessorsList)
{
    for (auto ProcessorName=ProcessorsList.begin();ProcessorName!=ProcessorsList.end();++ProcessorName) {
        Commands->commands.push_back(new UttProcessorCommand(*ProcessorName));
    }
    return *this;
}

/*
 * Description: adds the command needed to save the audio given the output file and the format (the default format is wav)
 * @param const std::string& - path to output file
 * @param const std::string& format - format to save the generated audio
 * @return CommandBuilder&
 */
CommandList::CommandBuilder &CommandList::CommandBuilder::SaveAudio(const std::string & outPutFile, const std::string& format)
{
    Commands->commands.push_back(new SetSpeectConfigCommand(Configuration::Audio,outPutFile));
    Commands->commands.push_back(new CreateAudioCommand(format));
    return *this;
}


/*
 * Description: adds the command to set the Speect engine configuration
 * @param const configName& - enum of the configuration type
 * @param const string& - configuration
 * @return CommandBuilder&
 */
CommandList::CommandBuilder &CommandList::CommandBuilder::LoadConfig(const Configuration::configName &config, const std::string &value)
{
    Commands->commands.push_back(new SetSpeectConfigCommand(config,value));
    return *this;
}
