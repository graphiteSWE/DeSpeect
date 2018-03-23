#ifndef MOC_H
#define MOC_H

#include "speect.h"
#include "list"
#include "string"
#include "utterance.h"
class Configuration;
class Utterance;
//this class will manage all memory of Speect component
//some function that should be const can t be because of how speect handle errors
class Speect
{
private:
    //speect error,see speect documentation for more information
    s_erc error;
    //class that wrap SUtterance of Speect
    Utterance* utt;
    //speect voice,see speect documentation for more information
    SVoice* voice;
    //contains speect configuration
    Configuration* config;
    //list of plugins that are loaded into speect
    std::list<SPlugin*> plugins;
public:
    //initialize speect
    Speect();
    //delete his object and all plugin loaded and then remove speect
    ~Speect();
    //return error as a integer, meaning is the same as speect documentation
    s_erc& getErrorState();
    //return the utterance modifiable
    const Utterance* getUtterance()const;
    //return the configuration modifiable
    Configuration* getConfiguration()const;
    //add a plugin of speect with speect function
    bool addPlugin(const std::string &PluginPath);
    //generate the utterance if the configuration of utterancetext has changed
    bool createUtt();
    //initialize the voice configuration voice must be set
    bool init();
    //if voice is initialize correctly return the utterance processors name
    const std::list<std::string> getUttProcessorNames();
    //if voice is initialize correctly return the named utterance processor or NULL if not exist
    const SUttProcessor *getUttProcessor(const std::string& Name);
};

#endif // MOC_H
