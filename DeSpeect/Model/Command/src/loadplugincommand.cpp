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
    //start the string of log
    std::string t="Adding Plugin:"+PluginPath;
    if(SpeectEngine!=NULL){
        //if speect fail to load add it to the log
        if(!SpeectEngine->addPlugin(PluginPath))
            t+=" Failed";
        //tell the operation status of speect
        //this is to tell if speect actually fail or it's a Despeect problem
        t+=" Operation status:";

        t+=s_error_str(SpeectEngine->getErrorState());
    }
    return t;
}
