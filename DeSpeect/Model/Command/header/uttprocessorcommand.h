#ifndef UTTPROCESSORCOMMAND_H
#define UTTPROCESSORCOMMAND_H
#include "abstractcommand.h"
class UttProcessorCommand:public AbstractCommand
{
   std::string Processor;
public:

    UttProcessorCommand(std::string);
    const std::string execute(Speect *SpeectEngine)const;
};
#endif // UTTPROCESSORCOMMAND_H
