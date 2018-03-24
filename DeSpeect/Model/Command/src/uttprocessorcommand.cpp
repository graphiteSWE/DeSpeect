#include "uttprocessorcommand.h"

UttProcessorCommand::UttProcessorCommand(Speect*engine, const std::string &processor)
    :AbstractCommand(engine)
    ,Processor(processor)
{

}

const std::string UttProcessorCommand::execute()const
{
    std::string t="";
    const Utterance* u=SpeectEngine->getUtterance();
    if(u!=NULL){
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
    return t;
}


