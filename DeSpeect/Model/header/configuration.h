#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include "vector"
#include "string"
//contains all data configuration of speect
//voicefile path, input text, and outputfile for audio
//also know if the config could be different from last get
class Configuration
{

private:
    std::vector<std::string> config;
    std::vector<bool> changed;
public:
    //initialize the configuration as empty string and change as true
    Configuration();
    //define the names to access the configuration
    enum configName
    {
        Voice=0,
        Audio=1,
        UtteranceType=2,
        UtteranceText=3,
        MAXSIZE=4
    };
    //set the named configuration with the string
    bool setConfig(configName,const std::string&);
    //return if the named configuration has changed since last get
    bool hasChanged(configName);
    //return the named configuration
    const std::string &getConfig(configName);
};

#endif // CONFIGURATION_H
