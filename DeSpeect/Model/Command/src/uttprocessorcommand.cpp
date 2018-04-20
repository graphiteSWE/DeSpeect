#include "uttprocessorcommand.h"

UttProcessorCommand::UttProcessorCommand(std::string processor)
    :AbstractCommand()
    ,Processor(processor)
{

}
#include "iostream"
const std::string UttProcessorCommand::execute(Speect *SpeectEngine)const
{
    std::string t="";
    const Utterance* u=SpeectEngine->getUtterance();
    if(u!=NULL){

        t+="Executing Processor:"+Processor;
        SUttProcessorRun(SpeectEngine->getUttProcessor(Processor.c_str())
                         ,u->getUtterance()
                         ,&SpeectEngine->getErrorState());
        std::cout<<t<<" "<<SpeectEngine->getUtterance()->getRelationNamesList().size();
    }
    else
    {
        t+="Failure: Utterance not Initialized";
    }
    t+=" Operation status:";

    t+=s_error_str(SpeectEngine->getErrorState());
    return t;
}


