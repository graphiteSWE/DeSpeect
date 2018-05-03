#ifndef UTTPROCESSORCOMMAND_H
#define UTTPROCESSORCOMMAND_H
#include "abstractcommand.h"

/*
 * File: uttprocessorcommand.h
 * Type: header
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: command to run a utterance processor
 */
 
class UttProcessorCommand:public AbstractCommand
{
    //Field: name of the utterance processor to be executed
    std::string Processor;
public:

	/*
	 * Description: builds a utterance processor command given a utterance processor name
	 * @param std::string& - utterance processor name
	 */
    explicit UttProcessorCommand(std::string);
    
	/*
	 * Description: executes the command on the engine
	 * @param Speect *SpeectEngine - Speect reference
	 * @return std::string
	 */
    const std::string execute(Speect *SpeectEngine) const;
};
#endif // UTTPROCESSORCOMMAND_H
