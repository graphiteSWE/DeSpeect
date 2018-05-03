#include "configuration.h"

/*
 * File: configuration.cpp
 * Type: src
 * Date: 2018-04-20
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: contains all the Speect configuration data (voicefile path, input text, and outputfile for audio)
 * 				and knows if the config could be different from last set
 */
 
//Description: configuration builder, initializes the configuration as an empty string and set changed to true
Configuration::Configuration()
    :config(std::vector<std::string>())
    ,changed(std::vector<bool>())
{
    for(int i=0;i<MAXSIZE;++i)
    {
        config.push_back(std::string(""));
        changed.push_back(true);
    }
}

/*
 * Description: sets the named configuration with the given string
 * @param configName - config
 * @param const std::string& - config value
 * @return bool
 */
bool Configuration::setConfig(Configuration::configName name,const std::string& Data)
{
    if(name!=MAXSIZE)
    {
        config[name]=Data;
        changed[name]=true;
        return true;
    }
    return false;
}

/*
 * Description: returns if the named configuration has changed since last set
 * @param configName - config name
 * @return bool
 */
bool Configuration::hasChanged(Configuration::configName name)
{
    return changed[name];
}

/*
 * Description: returns the named configuration
 * @param configName - config name
 * @return const std::string &
 */
const std::string& Configuration::getConfig(Configuration::configName name)
{
    if(name!=MAXSIZE)
    {
        changed[name]=false;
        return config[name];
    }
}
