#ifndef COMMAND_H
#define COMMAND_H
#include "Speect.h"
//abstract command
//define a function of speect that can be executed
class AbstractCommand
{

public:
    AbstractCommand();
    virtual ~AbstractCommand()=0;
    //execute the function and return the log of execution
    //:= Status Speect Pre execution,Operation,Status speect post execution
    virtual const std::string execute(Speect* engine)const =0 ;
};
#endif // COMMAND_H
