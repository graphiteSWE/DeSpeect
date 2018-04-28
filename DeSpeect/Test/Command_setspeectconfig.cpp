#include "gtest/gtest.h"
#include "../Model/Command/header/setspeectconfigcommand.h"
#include "../Model/SpeectWrapper/header/Speect.h"
#include "../Model/Command/header/createaudiocommand.h"
#include "../Model/Command/header/commandlist.h"

TEST(Command, setspeectconfigFailure)
{
	Speect s;
    AbstractCommand* temp(new SetSpeectConfigCommand(Configuration::Voice, "aaa.json"));
    EXPECT_EQ(temp->execute(&s), "Initializing Voice Failure Operation status:Failure");
    delete temp;
}

TEST(Command, setspeectconfigSuccess)
{
	Speect s;
    AbstractCommand* temp(new SetSpeectConfigCommand(Configuration::Voice, "./cmu_arctic_slt/voice.json"));
    temp->execute(&s);
    EXPECT_FALSE(s.getUttProcessorNames().empty());
    delete temp;
}

TEST(Command, setspeectconfigutterancetest)
{
	Speect s;
    AbstractCommand* temp(new SetSpeectConfigCommand(Configuration::Voice, "./cmu_arctic_slt/voice.json"));
    temp->execute(&s);
    delete temp;
    temp=new SetSpeectConfigCommand(Configuration::UtteranceText, "testo esempio");
    EXPECT_EQ(temp->execute(&s), " Initializing Utterance Success Operation status:No error");
    delete temp;
}

/*TEST(View, VerifyRelationTest){
    Speect* s=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(s);
    CommandList* commands;
    commands=builder->LoadConfig(Configuration::Voice, "./cmu_arctic_slt/voice.json").getCommandList();
    //commands->executeAll();
    std::string text="hi everybody";
    commands=builder->LoadConfig(Configuration::UtteranceText, text).getCommandList();
    //commands->executeAll();
    std::list<std::string> processorList;
    processorList.push_back("Tokenize");
    commands=builder->WithProcessors(processorList).getCommandList();
    commands->executeAll();
    EXPECT_EQ(commands->getRelationNames().front(), "Tokenize");
    delete s;
    delete commands;
}
*/

/*
TEST(Command, tryCreateAudioFail2)
{
	Speect s;
	CreateAudioCommand* cmd=new CreateAudioCommand("hello world");
    EXPECT_EQ(cmd->execute(&s), "Failed: Utterance is not initialized");
    delete cmd;
}*/

/*
No error

Failure

Memory allocation failed

Function argument(s) invalid

Class/object method does not exist

Method/function call failed

End of file/stream

Warning, possible error

Error context continued

Undefined error

*/
