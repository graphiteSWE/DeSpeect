#ifndef LOADPLUGINCOMMAND_H
#define LOADPLUGINCOMMAND_H
#include "abstractcommand.h"
class LoadPluginCommand:public AbstractCommand
{
    const std::string PluginPath;
    // AbstractCommand interface
public:
    LoadPluginCommand(const std::string&);
    const std::string execute(Speect *SpeectEngine) const;
};
#endif // LOADPLUGINCOMMAND_H
