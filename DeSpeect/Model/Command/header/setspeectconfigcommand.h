#ifndef SETSPEECTCONFIGCOMMAND_H
#define SETSPEECTCONFIGCOMMAND_H
#include "abstractcommand.h"
#include "configuration.h"

/*
 * File: setspeectconfigcommand.h
 * Type: header
 * Date: 2018-04-20
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: command to set a Speect configuration
 */
 
class SetSpeectConfigCommand:public AbstractCommand
{
    //Field: Speect configuration name
    const Configuration::configName name;
    
    //Field: value for the configuration
    const std::string value;
    
    // AbstractCommand interface
public:

	/*
	 * Description: builds a configuration command given a config name and a config value
	 * @param const Configuration::configName& - config type
	 * @param const std::string& - config value
	 */
    SetSpeectConfigCommand(const Configuration::configName&, const std::string&);
    
	/*
	 * Description: executes the command on the engine
	 * @param Speect *SpeectEngine - Speect reference
	 * @return const std::string
	 */
    const std::string execute(Speect *SpeectEngine) const;
};
#endif // SETSPEECTCONFIGCOMMAND_H
