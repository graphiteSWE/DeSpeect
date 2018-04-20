#include "createaudiocommand.h"
#include "configuration.h"
CreateAudioCommand::CreateAudioCommand(const std::string &format)
    :AbstractCommand()
    ,AudioFormat(format)
{

}

const std::string CreateAudioCommand::execute(Speect *SpeectEngine) const
{

    std::string t="Generating audio to File:"+
            SpeectEngine->getConfiguration()->getConfig(Configuration::Audio)+" ";

    if(SpeectEngine->getUtterance())
    {
        SUtterance* utt=SpeectEngine->getUtterance()->getUtterance();
        if(SUtteranceFeatureIsPresent(utt,"audio",&SpeectEngine->getErrorState())){
                    SObjectSave(
                                SUtteranceGetFeature(
                                    SpeectEngine->getUtterance()->getUtterance()
                                    ,"audio"
                                    ,&SpeectEngine->getErrorState()
                                    )
                                ,SpeectEngine->getConfiguration()->getConfig(Configuration::Audio).c_str()
                                ,AudioFormat.c_str()
                                ,&SpeectEngine->getErrorState()
                                );
        t+=" Saved audio Feature to file, Operation status:";
        t+=s_error_str(SpeectEngine->getErrorState());
        }
        else
        {
            t+="Audio Feature not present, failed to save";
        }
    }
    else
    {
        t+=" Failed: Utterance is not initialized";
    }
    return t;
}
