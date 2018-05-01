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
    //initialize the log string
    std::string t="";
    if(SpeectEngine!=NULL){
        t="Generating audio to File:"+
                SpeectEngine->getConfiguration()->getConfig(Configuration::Audio)+" ";
        //check if utterance exists
        if(SpeectEngine->getUtterance())
        {
            //get the utterance
            SUtterance* utt=SpeectEngine->getUtterance()->getUtterance();
            //check if the audio feature is present in the utterance
            if(SUtteranceFeatureIsPresent(utt,"audio",&SpeectEngine->getErrorState())){
                //save the object
                SObjectSave(
                            //get the feature audio
                                    SUtteranceGetFeature(
                                        utt
                                        ,"audio"
                                        ,&SpeectEngine->getErrorState()
                                        )
                            //get the audio file output
                                    ,SpeectEngine->getConfiguration()->getConfig(Configuration::Audio).c_str()
                                    ,AudioFormat.c_str()
                                    ,&SpeectEngine->getErrorState()
                                    );
                //report the ending status
            t+="Saved audio Feature to file, Operation status:";
            t+=s_error_str(SpeectEngine->getErrorState());
            }
            else
            {
                //set the status to failure because feature not present
                t+="Audio Feature not present, failed to save";
            }
        }
        else
        {
            t+=" Failed: Utterance is not initialized";
        }
    }
    return t;
}
