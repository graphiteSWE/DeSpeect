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
    SetSpeectConfigCommand(const Configuration::configName&, const std::string&);
    const std::string execute(Speect *SpeectEngine) const;
};
#endif // SETSPEECTCONFIGCOMMAND_H
