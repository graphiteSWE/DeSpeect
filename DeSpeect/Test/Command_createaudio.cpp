#include "gtest/gtest.h"
#include "../Model/Command/header/setspeectconfigcommand.h"
#include "../Model/SpeectWrapper/header/Speect.h"
#include "../Model/Command/header/createaudiocommand.h"
#include "../Model/Command/header/commandlist.h"
#include <fstream>

TEST(Command, createaudiosuccess){
    Speect* s=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(s);
    CommandList* commands;
    commands=builder->LoadConfig(Configuration::Voice, "./cmu_arctic_slt/voice.json").getCommandList();
    commands->executeAll();
    std::string text="hi everybody";
    commands=builder->LoadConfig(Configuration::UtteranceText, text).getCommandList();
    commands->executeAll();
    std::list<std::string> processorList;
    std::list<std::string> processorName= commands->getUttProcessorsNames();
    for(std::list<std::string>::iterator it=processorName.begin(); it!=processorName.end(); it++) {
        processorList.push_back(it->c_str());
    }
    builder->WithProcessors(processorList);
    commands=builder->getCommandList();
    commands->executeAll();

    std::string str="prova.wav";
    commands=builder->SaveAudio(str).getCommandList();
    commands->executeAll();
    //std::ofstream file1("prova.wav");
    //file1.close();
    std::ifstream file("prova.wav");
    file.open("prova.wav");
    bool ok=file.is_open();
    EXPECT_EQ(ok, true);
    delete s;
    delete commands;
    delete builder;
}
/*
TEST(Command, createaudiofail){
Speect s;
CreateAudioCommand* cmd=new CreateAudioCommand("wav");
EXPECT_EQ(cmd->execute(&s), "Failed: Utterance is not initialized");
delete cmd;
}*/
