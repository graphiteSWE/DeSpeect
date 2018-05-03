#include "uttprocessorcommand.h"

/*
 * File: uttprocessorcommand.cpp
 * Type: src
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: command to run a utterance processor
 */

/*
 * Description: builds a utterance processor command given a utterance processor name
 * @param std::string& - utterance processor name
 */
UttProcessorCommand::UttProcessorCommand(std::string processor)
    :AbstractCommand()
    ,Processor(processor)
{

}

/*
 * Description: executes the command on the engine:
 * 				checks if the utterance exists and, if it does, requests the processor from Speect and runs it on the utterance	
 * @param Speect *SpeectEngine - Speect reference
 * @return const std::string
 */
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


