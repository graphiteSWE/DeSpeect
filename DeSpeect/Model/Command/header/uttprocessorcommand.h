#ifndef UTTPROCESSORCOMMAND_H
#define UTTPROCESSORCOMMAND_H
#include "abstractcommand.h"

class UttProcessorCommand: public AbstractCommand
{
    //name of the processor to be executed
   std::string Processor;
public:
    //create the command
    explicit UttProcessorCommand(std::string);

    //execute the command
    const std::string execute(Speect *SpeectEngine)const;

};

#endif // UTTPROCESSORCOMMAND_H
