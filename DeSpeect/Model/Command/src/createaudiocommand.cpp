#include "createaudiocommand.h"
#include "configuration.h"

//create a command to save the utterance as audio
CreateAudioCommand::CreateAudioCommand(const std::string &format)
    :AbstractCommand()
    ,AudioFormat(format)
{}


//save audio feature and generate the log
//if the utterance exist check if the audio feature exist
//if it exist use Speect function to save utterance fetched from the engine and
//set log otherwise tell why the save failed
//get the file audio where to save from the configuration
//get the audio feature from the utterance
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
        t+="Saved audio Feature to file, Operation status:";
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
