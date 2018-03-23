#ifndef CREATEAUDIOCOMMAND_H
#define CREATEAUDIOCOMMAND_H
#include "abstractcommand.h"
class CreateAudioCommand:public AbstractCommand
{
private:
    const std::string AudioFormat;

    // AbstractCommand interface
public:
    CreateAudioCommand(Speect*,const std::string&);
    const std::string execute() const;
};
#endif // CREATEAUDIOCOMMAND_H
