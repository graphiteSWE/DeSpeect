#ifndef UTTPROCESSORCOMMAND_H
#define UTTPROCESSORCOMMAND_H
#include "abstractcommand.h"
class UttProcessorCommand:public AbstractCommand
{
   const std::string Processor;
public:

    UttProcessorCommand(Speect *, const std::string&);
    const std::string execute()const;
};
#endif // UTTPROCESSORCOMMAND_H
