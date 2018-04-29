#include "loadplugincommand.h"

//create a command
LoadPluginCommand::LoadPluginCommand(const std::string & PluginPath)
    :AbstractCommand()
    ,PluginPath(PluginPath)
{

}

//execution of the plugins command
//request the engine to load the plugin this is the only command done inside speect
//because it's a memory management and is SpeectWrapper job to handle that
const std::string LoadPluginCommand::execute(Speect *SpeectEngine) const
{
    std::string t="Adding Plugin:"+PluginPath;

    if(!SpeectEngine->addPlugin(PluginPath))
        t+=" Failed";

    t+=" Operation status:";

    t+=s_error_str(SpeectEngine->getErrorState());
    return t;
}
