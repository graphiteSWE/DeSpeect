#ifndef COMMANDLIST_H
#define COMMANDLIST_H
#include "abstractcommand.h"
#include <list>
#include "string"
#include "configuration.h"
#include <bits/stl_map.h>

/*
 * File: commandlist.h
 * Type: header
 * Date: 2018-04-20
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: list of commands that allows their execution
 */

class CommandList
{
private:
    //Field: list of commands to be executed
    std::list<AbstractCommand*> commands;

    //Field: stack of the log that each command returns
    std::list<std::string> ErrorLog;

    //Field: wrapper that contains the data that every command uses
    Speect* Speectengine;

public:

    //Description: builder of an AbstractCommandList
    class CommandBuilder
    {
    private:
        //Field: engine used by the command list
        Speect* engine;
        
        //Field: list of commands
        CommandList* Commands;
    public:
    
		/*
		 * Description: builder constructor
		 * @param Speect* engine - Speect reference
		 */
        explicit CommandBuilder(Speect* engine);
    
        //Description: builder destructor
        ~CommandBuilder();
        
		/*
		 * Description: returns the built CommandList
		 * @return CommandList*
		 */
        CommandList* getCommandList();
        
		/*
		 * Description: adds the commands related to the utterance processors whose names are in the given list (it doesn't check if they actually exist)
		 * @param std::list<std::string>& - list of the utterance processors names
		 * @return CommandBuilder&
		 */
        CommandBuilder& WithProcessors(const std::list<std::string>&);
        
		/*
		 * Description: adds the command needed to save the audio given the output file and the format (the default format is wav)
		 * @param std::string& - path to output file
		 * @param std::string& format - format to save the generated audio
		 * @return const CommandBuilder&
		 */
        CommandBuilder& SaveAudio(const std::string&, const std::string & format="riff");
        
		/*
		 * Description: adds the command to set the Speect engine configuration
		 * @param configName& - enum of the configuration type
		 * @param string& - configuration
		 * @return CommandBuilder&
		 */
        CommandBuilder& LoadConfig(const Configuration::configName&,const std::string&);

    };
    
    //virtual ~CommandList()=0;
    
	/*
	 * Description: executes all the commands in the list, empties the list and fills the log with their return data
	 * @return void
	 */
    void executeAll();
    
	/*
	 * Description: executes the first command of the list, fills the log and pops the command from the list
	 * @return void
	 */
    void executeStep();
    
	/*
	 * Description: returns the error log of the executed command and clears all the ones returned from the log
	 * @return std::list<std::string>
	 */
    std::list<std::string> getErrorState();

	/*
	 * Description: clears the ErrorLog list
	 * @return std::void
	 */
    void clearErrorState();
    
	/*
	 * Description: allows to add a command to the list
	 * @param AbstractCommand* - command to be added
	 * @return std::void
	 */
    void addCommand(AbstractCommand*);
    
	/*
	 * Description: allows to queue a commandlist to this command list
	 * @param CommandList& - command list to be added
	 * @return std::void
	 */
    void addCommand(CommandList&);
    
	/*
	 * Description: returns the number of commands in the list
	 * @return std::int
	 */
    int getNumberCommands();

    //The following methods allow to get data from the engine on which the command are gonna run

	/*
	 * Description: if exists, returns the named Relation, NULL otherwise
	 * @param const std::string & - relation name
	 * @return Relation*
	 */
    const Relation* getRelation(const std::string &)const;
    
	/*
	 * Description: returns the list of the relations names
	 * @return std::list<std::string>
	 */
    const std::list<std::string> getRelationNames()const ;
    
	/*
	 * Description: returns the list of the utterance processors names
	 * @return std::list<std::string>
	 */
    const std::list<std::string> getUttProcessorsNames()const;
    
	/*
	 * Description: returns the list of the utterance processors names in the selected utterance type
	 * @param std::string& - utterance type name
	 * @return std::list<std::string>
	 */
    const std::list<std::string> getUttProcessorsNames(const std::string&)const;
    
	/*
	 * Description: returns the list of the utterance type names in the loaded voice
	 * @return std::list<std::string>
	 */
    const std::list<std::string> getUttTypeNames()const;
    
	/*
	 * Description: returns the data related to the node given a relation and the path from head (ID of a graphic Node)
	 * @param std::string& path - path to the node
	 * @param const std::string& rel - relation name
	 * @return std::map<std::string,std::string>
	 */
    const std::map<std::string,std::string> getNode(const std::string& path, const std::string& rel);

private:

    //Description: command list constructor, it's private so that construction outside the builder isn't allowed
    CommandList();
    
	/*
	 * Description: command list constructor, it's private so that construction outside the builder isn't allowed
	 * @param Speect* engine - Speect reference
	 */
    explicit CommandList(Speect* engine);

};
#endif // COMMANDLIST_H

