#include "gtest/gtest.h"
#include "../Model/Command/header/setspeectconfigcommand.h"
#include "../Model/SpeectWrapper/header/Speect.h"
#include "../Model/Command/header/createaudiocommand.h"
#include "../Model/Command/header/commandlist.h"
#include <fstream>

TEST(Command, CommandList_test){
    Speect* sTest=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(sTest);
    builder->LoadConfig(Configuration::Voice,"./cmu_arctic_slt/voice.json").getCommandList()->executeAll();
    builder->LoadConfig(Configuration::UtteranceText,"hi everybody").getCommandList()->executeAll();
    std::list<std::string> l;
    l.push_back("Tokenize");
    l.push_back("Normalize");
    builder->WithProcessors(l).getCommandList()->executeAll();
    CommandList* t=builder->getCommandList();
    t->getNode("Token", " ");
    std::string str="Node search success,Speect Status:No error";
    ASSERT_EQ(*(t->getErrorState().begin()), str);
}
