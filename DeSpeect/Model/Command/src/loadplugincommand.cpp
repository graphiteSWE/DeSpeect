#include "loadplugincommand.h"
LoadPluginCommand::LoadPluginCommand(const std::string & PluginPath)
    :AbstractCommand()
    ,PluginPath(PluginPath)
{

}

const std::string LoadPluginCommand::execute(Speect *SpeectEngine) const
{
    std::string t="Adding Plugin:"+PluginPath;

    if(!SpeectEngine->addPlugin(PluginPath))
        t+=" Failed";

    t+=" Operation status:";

    t+=s_error_str(SpeectEngine->getErrorState());
    return t;
}
