#ifndef LOADPLUGINCOMMAND_H
#define LOADPLUGINCOMMAND_H
#include "abstractcommand.h"
class LoadPluginCommand:public AbstractCommand
{
    //path of the plugins (see speect documentation for more information)
    const std::string PluginPath;
    // AbstractCommand interface
public:
    //create the plugin command
    LoadPluginCommand(const std::string&);
    //execute the command on the engine
    const std::string execute(Speect *SpeectEngine) const;
};
#endif // LOADPLUGINCOMMAND_H
