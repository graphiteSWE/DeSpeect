#include "gtest/gtest.h"
#include "../Model/Command/header/setspeectconfigcommand.h"
#include "../Model/SpeectWrapper/header/Speect.h"
#include "../Model/Command/header/createaudiocommand.h"
#include "../Model/Command/header/commandlist.h"
#include <fstream>

TEST(Command, getuttnamesuccess){
    Speect* s=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(s);
    CommandList* commands;
    commands=builder->getCommandList();
    commands->getRelationNames();
    commands->getRelation("");
    commands=builder->LoadConfig(Configuration::Voice, "./cmu_arctic_slt/voice.json").getCommandList();
    commands->executeAll();
    commands->clearErrorState();
    std::string name=commands->getUttTypeNames().begin()->c_str();
    EXPECT_EQ(name, "text");
    delete s;
    delete commands;
    delete builder;
}

