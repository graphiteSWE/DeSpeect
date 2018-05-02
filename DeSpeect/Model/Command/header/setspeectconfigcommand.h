#ifndef SETSPEECTCONFIGCOMMAND_H
#define SETSPEECTCONFIGCOMMAND_H
#include "abstractcommand.h"
#include "configuration.h"

class SetSpeectConfigCommand: public AbstractCommand
{
    //configuration name of speect
    const Configuration::configName name;

    //value to set
    const std::string value;

    // AbstractCommand interface
public:
    //create the command
    explicit SetSpeectConfigCommand(const Configuration::configName&, const std::string&);

    //execute the command on the engine
    const std::string execute(Speect *SpeectEngine) const;

};
#endif // SETSPEECTCONFIGCOMMAND_H
