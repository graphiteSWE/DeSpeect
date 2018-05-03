#ifndef CREATEAUDIOCOMMAND_H
#define CREATEAUDIOCOMMAND_H
#include "abstractcommand.h"

/*
 * File: createaudiocommand.h
 * Type: header
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: command for the audio generation
 */
 
class CreateAudioCommand:public AbstractCommand
{
private:
    //Field: audio format
    const std::string AudioFormat;

    // AbstractCommand interface
public:

	/*
	 * Description: builds an audio command given the format
	 * @param std::string& - audio format
	 */
    explicit CreateAudioCommand(const std::string&);
    
	/*
	 * Description: executes the command on the engine
	 * @param Speect* engine - Speect reference
	 * @return std::string
	 */
    const std::string execute(Speect* engine) const;
};
#endif // CREATEAUDIOCOMMAND_H
