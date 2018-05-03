#ifndef MOC_H
#define MOC_H
#include "speect.h"
#include <list>
#include "string"
#include "utterance.h"
#include <map>

class Configuration;
class Utterance;

/*
 * File: Speect.h
 * Type: header
 * Date: 2018-04-20
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: manages the memory of all Speect components, note that some functions that should be const can't be because of how Speect handles errors internally
 */
 
class Speect
{
private:
    //Field: Speect error (see speect documentation for more information)
    s_erc error;
    
    //Field: wrapper for Speect SUtterance
    Utterance* utt;
    
    //Field: Speect voice (see speect documentation for more information)
    SVoice* voice;
    
    //Field: Speect configuration
    Configuration* config;
    
    //Field: list of plugins that are loaded into speect
    std::list<SPlugin*> plugins;
    
    /*
    * Description: given an SItem, returns the path from the head to it
    * @param const SItem* - Speect Item
    * @return std::string
    */
    std::string createId(const SItem*);
    
public:
    
    //Description: Speect constructor, initializes Speect
    Speect();
    
    //Description: Speect destructor, deletes his object, all loaded plugins and then removes Speect
    ~Speect();
      
    /*
    * Description: returns errors as integers (the meaning is the same as described in Speect documentation)
    * @return std::s_erc&
    */
    s_erc& getErrorState();
    
    /*
    * Description: returns the utterance
    * @return const Utterance*
    */
    const Utterance* getUtterance()const;
    
    /*
    * Description: returns the current config
    * @return Configuration*
    */
    Configuration* getConfiguration()const;
    
    /*
    * Description: adds a Speect plugin
    * @param const std::string &PluginPath - path to the plugin
    * @return bool
    */
    bool addPlugin(const std::string &PluginPath);
    
    /*
    * Description: generates the utterance if the configuration of utterancetext has changed
    * @return bool
    */
    bool createUtt();
    
    /*
    * Description: initialize the voice, notice that configuration voice must be set
    * @return bool
    */
    bool init();
    
    /*
    * Description: returns a list containing the utterance processors names
    * @return const std::list<std::string>
    */
    const std::list<std::string> getUttProcessorNames();
    
    /*
    * Description: if the voice is correctly initialized, returns the named utterance processor or NULL if it doesn't exist
    * @param const std::string& Name - name of the utterance processor to be returned
    * @return const SUttProcessor *
    */
    const SUttProcessor *getUttProcessor(const std::string& Name);
    
    /*
    * Description: if the voice is correctly initialized, returns the list of utterance types defined in it
    * @return const std::list<std::string>
    */
    const std::list<std::string> getUttTypeName();
    
    /*
    * Description: if the voice is initialized, returns the list of processors names for the given utterance type
    * @param const std::string& - name of the utterance type
    * @return const std::list<std::string>
    */
    const std::list<std::string> getUttProcessorNames(const std::string&);
    
    /*
    * Description: searches and returns a node given the relation and the path from the head, also builds the path to that item
    * @param const std::string &relation - relation name
    * @param const std::string &path - path from the head
    * @return const std::map<std::string,std::string>
    */
    const std::map<std::string,std::string> getNode(const std::string &relation, const std::string &path);
};

#endif // MOC_H
