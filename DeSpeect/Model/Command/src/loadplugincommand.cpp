#include "loadplugincommand.h"
LoadPluginCommand::LoadPluginCommand(Speect *engine,const std::__cxx11::string & PluginPath)
    :AbstractCommand(engine)
    ,PluginPath(PluginPath)
{

}

const std::string LoadPluginCommand::execute() const
{
    std::string t=" Adding Plugin:"+PluginPath;

    if(!SpeectEngine->addPlugin(PluginPath))
        t+=" Failed";

    t+=" Operation status:";

    t+=s_error_str(SpeectEngine->getErrorState());
    return t;
}
