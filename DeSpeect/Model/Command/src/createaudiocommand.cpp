#include "createaudiocommand.h"
#include "configuration.h"


/*
 * Description: builds an audio command given the format
 * @param std::string& - audio format
 */
CreateAudioCommand::CreateAudioCommand(const std::string &format)
    :AbstractCommand()
    ,AudioFormat(format)
{}


/*
 * Description: executes the command on the engine:
 * 				save audio feature and generate the log
 * 				if the utterance exists, checks if the audio feature exists
 *				if it exists, uses Speect function to save the utterance fetched from the engine and sets the log, otherwise declares why the saving failed
 *				gets the saving location of the audio file from the configuration
 *				gets the audio feature from the utterance
 * @param Speect* engine - Speect reference
 * @return std::string
 */
 
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
