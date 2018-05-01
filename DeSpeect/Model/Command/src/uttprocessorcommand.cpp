#include "uttprocessorcommand.h"


//create an utterance processor command
UttProcessorCommand::UttProcessorCommand(std::string processor)
    :AbstractCommand()
    ,Processor(processor)
{

}
//execution of a processor command
//check if utterance exist
//if it exists request the processor to Speect,and run it on the utterance
const std::string UttProcessorCommand::execute(Speect *SpeectEngine)const
{
    std::string t="";
    if(SpeectEngine!=NULL){
        const Utterance* u=SpeectEngine->getUtterance();
        if(u!=NULL)
        {
            t+="Executing Processor:"+Processor;
            SUttProcessorRun(SpeectEngine->getUttProcessor(Processor.c_str())
                             ,u->getUtterance()
                             ,&SpeectEngine->getErrorState());
        }
        else
        {
            t+="Failure: Utterance not Initialized";
        }
        t+=" Operation status:";

        t+=s_error_str(SpeectEngine->getErrorState());
    }
    return t;
}


