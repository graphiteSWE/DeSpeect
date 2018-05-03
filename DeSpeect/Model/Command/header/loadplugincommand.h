#ifndef LOADPLUGINCOMMAND_H
#define LOADPLUGINCOMMAND_H
#include "abstractcommand.h"

/*
 * File: loadplugincommand.h
 * Type: header
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: command for the plugin loading
 */
 
class LoadPluginCommand:public AbstractCommand
{
    //Field: path to the plugin (see speect documentation for more information)
    const std::string PluginPath;
    
    // AbstractCommand interface
public:

	/*
	 * Description: builds a plugin command given the path to the plugin
	 * @param const std::string& - path to the plugin
	 */
    explicit LoadPluginCommand(const std::string&);
    
	/*
	 * Description: executes the command on the engine
	 * @param Speect *SpeectEngine - Speect reference
	 * @return std::string
	 */
	const std::string execute(Speect *SpeectEngine) const;
};
#endif // LOADPLUGINCOMMAND_H
