#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include "vector"
#include "string"

/*
 * File: configuration.h
 * Type: header
 * Date: 2018-04-20
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: contains all the Speect configuration data (voicefile path, input text, and outputfile for audio)
 * 				and knows if the config could be different from last set
 */

class Configuration
{

private:
	//Field: configuration type
    std::vector<std::string> config;
    
    //Field: boolean indicating if the configuration has changed
    std::vector<bool> changed;
public:

    //Description: configuration builder, initializes the configuration as an empty string and set changed to true
    Configuration();
    
    //Enum defining the names to access the configuration
    enum configName
    {
        Voice=0,
        Audio=1,
        UtteranceType=2,
        UtteranceText=3,
        MAXSIZE=4
    };
    
	/*
	 * Description: sets the named configuration with the given string
	 * @param configName - config
	 * @param const std::string& - config value
	 * @return bool
	 */
    bool setConfig(configName,const std::string&);
    
	/*
	 * Description: returns if the named configuration has changed since last set
	 * @param configName - config name
	 * @return bool
	 */
    bool hasChanged(configName);
    
	/*
	 * Description: returns the named configuration
	 * @param configName - config name
	 * @return const std::string &
	 */
    const std::string &getConfig(configName);
};

#endif // CONFIGURATION_H
