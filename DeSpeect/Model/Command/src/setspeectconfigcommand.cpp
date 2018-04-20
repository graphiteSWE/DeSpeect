
#include "setspeectconfigcommand.h"
SetSpeectConfigCommand::SetSpeectConfigCommand(
        const Configuration::configName &name
        , const std::string &value
        )
    :AbstractCommand()
    ,name(name)
    ,value(value)
{

}

const std::string SetSpeectConfigCommand::execute(Speect *SpeectEngine) const
{
    std::string t="";
    SpeectEngine->getConfiguration()->setConfig(name,value);
    bool error=true;
    if(name==Configuration::Voice)
    {
        t+="Initializing Voice";
        SpeectEngine->init()?t+=" Success":t+=" Failure";
    }
    else if(name==Configuration::UtteranceText)
    {
        t+=" Initializing Utterance";
        SpeectEngine->createUtt()?t+=" Success":t+=" Failure";
    }
    else
    {
        t+=" Setting Configuration";
    }
    t+=" Operation status:";

    t+=s_error_str(SpeectEngine->getErrorState());
    return t;

}
