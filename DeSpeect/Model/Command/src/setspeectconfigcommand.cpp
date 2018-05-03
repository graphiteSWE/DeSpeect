
#include "setspeectconfigcommand.h"

/*
 * File: setspeectconfigcommand.cpp
 * Type: src
 * Date: 2018-04-20
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: command to set a Speect configuration
 */
 
/*
 * Description: builds a configuration command given a config name and a config value
 * @param const Configuration::configName& - config type
 * @param const std::string& - config value
 */
SetSpeectConfigCommand::SetSpeectConfigCommand(
        const Configuration::configName &name
        , const std::string &value
        )
    :AbstractCommand()
    ,name(name)
    ,value(value)
{}


//execution of config command
//check what is asked to configure and check prerequisite
//if it's voice or utterance it also ask Speect to initialize itself with the data

/*
 * Description: executes the command on the engine:
 * 				checks what it's been asked to configure and the related prerequisite,
 * 				if it's either voice or utterance it also asks Speect to initialize itself with the correct data
 * @param Speect *SpeectEngine - Speect reference
 * @return const std::string
 */
const std::string SetSpeectConfigCommand::execute(Speect *SpeectEngine) const
{
    std::string t="";
    if(SpeectEngine!=NULL){
        SpeectEngine->getConfiguration()->setConfig(name,value);
        if(name==Configuration::Voice)
        {
            t+="Initializing Voice";
            SpeectEngine->init()?t+=" Success":t+=" Failure";
        }
        else if(name==Configuration::UtteranceText)
        {
            t+="Initializing Utterance";
            SpeectEngine->createUtt()?t+=" Success":t+=" Failure";
        }
        else
        {
            t+="Setting Configuration";
        }
        t+=" Operation status:";

        t+=s_error_str(SpeectEngine->getErrorState());
    }
    return t;

}
