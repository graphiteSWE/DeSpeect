#ifndef COMMAND_H
#define COMMAND_H
#include "Speect.h"

/*
 * File: abstractcommand.h
 * Type: header
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: defines a Speect function that can be executed and doesn't return any value
 */

class AbstractCommand

{

public:

    // Description: default constructor
    AbstractCommand();

    // Description: default destructor made virtual for hierachy
    virtual ~AbstractCommand()=0;

    /*
     * Description: executes the function and returns the log of execution. Errors follow the syntax := Operation,Status speect post execution
     * @param Speect* engine - Speect reference
     * @return std::string
     */
    virtual const std::string execute(Speect* engine) const =0 ;

};

#endif // COMMAND_H

