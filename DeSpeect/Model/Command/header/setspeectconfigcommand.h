#ifndef SETSPEECTCONFIGCOMMAND_H
#define SETSPEECTCONFIGCOMMAND_H
#include "abstractcommand.h"
#include "configuration.h"
class SetSpeectConfigCommand:public AbstractCommand
{
    const Configuration::configName name;
    const std::string value;
    // AbstractCommand interface
public:
    SetSpeectConfigCommand(Speect*,const Configuration::configName&,const std::string&);
    const std::string execute() const;
};
#endif // SETSPEECTCONFIGCOMMAND_H
