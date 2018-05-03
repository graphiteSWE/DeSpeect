#include "loadplugincommand.h"

/*
 * Description: builds a plugin command given the path to the plugin
 * @param std::string& - path to the plugin
 */
LoadPluginCommand::LoadPluginCommand(const std::string & PluginPath)
    :AbstractCommand()
    ,PluginPath(PluginPath)
{

}

/*
 * Description: executes the command on the engine:
 * 				requests the engine to load the plugin, note that this is the only command executed inside Speect
 * 				since it's a memory management task and it is SpeectWrapper responsibility to handle that
 * @param Speect *SpeectEngine - Speect reference
 * @return std::string
 */
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
