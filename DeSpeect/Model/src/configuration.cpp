#include "configuration.h"
//initialize the configuration as empty string and say that all configuration where never asked
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
//set the new string in the right place and tell that the string could be different
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
//return if the string in the name could be changed since last get
bool Configuration::hasChanged(Configuration::configName name)
{
    return changed[name];
}
//return the string and tell that is same as last get
const std::string& Configuration::getConfig(Configuration::configName name)
{
    if(name!=MAXSIZE)
    {
        changed[name]=false;
        return config[name];
    }
}
