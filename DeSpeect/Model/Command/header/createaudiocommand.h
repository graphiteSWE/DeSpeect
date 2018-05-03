#ifndef CREATEAUDIOCOMMAND_H
#define CREATEAUDIOCOMMAND_H
#include "abstractcommand.h"
class CreateAudioCommand:public AbstractCommand
{
private:
    //audio format
    const std::string AudioFormat;

    // AbstractCommand interface
public:
    //build an audio command given the format
    CreateAudioCommand(const std::string&);
    //execute the command on the engine
    const std::string execute(Speect* engine) const;
};
#endif // CREATEAUDIOCOMMAND_H
