#include "gtest/gtest.h"
#include "setspeectconfigcommand.h"
#include "../Model/Command/header/commandlist.h"
#include "../Model/SpeectWrapper/header/relation.h"
#include "../Model/Command/header/uttprocessorcommand.h"


TEST(Graph, VerifyRelationName){
    Speect* s=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(s);
    CommandList* commands;
    commands=builder->LoadConfig(Configuration::Voice, "./cmu_arctic_slt/voice.json").getCommandList();
    commands->executeAll();
    std::string text="hi everybody";
    commands=builder->LoadConfig(Configuration::UtteranceText, text).getCommandList();
    commands->executeAll();
    std::list<std::string> processorList;
    processorList.push_back("Tokenize");
    commands=builder->WithProcessors(processorList).getCommandList();
    commands->executeAll();
    EXPECT_EQ(commands->getRelationNames().front(), "Token");
    delete s;
    delete commands;
    delete builder;
}

/*TEST(Graph, VerifyUtteranceProcessorFailure){
    Speect* s=new Speect();
    UttProcessorCommand* utt=new UttProcessorCommand("ciao");
    EXPECT_EQ(utt->execute(s), "Failure: Utterance not Initialized");
    delete s;
}*/

TEST(Graph, VerifyRelationByName){
    Speect* s=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(s);
    CommandList* commands;
    commands=builder->LoadConfig(Configuration::Voice, "./cmu_arctic_slt/voice.json").getCommandList();
    commands->executeAll();
    std::string text="hi everybody";
    commands=builder->LoadConfig(Configuration::UtteranceText, text).getCommandList();
    commands->executeAll();
    std::list<std::string> processorList;
    processorList.push_back("Tokenize");
    commands=builder->WithProcessors(processorList).getCommandList();
    commands->executeAll();
    EXPECT_EQ(commands->getRelation("Token")->getName(), "Token");
    delete s;
    delete commands;
    delete builder;
}
