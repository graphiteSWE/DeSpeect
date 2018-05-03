#include "gtest/gtest.h"
#include <commandlist.h>
#include <unistd.h>

#include "modelview.h"
#include <QFileDialog>
#include <graphmanager.h>
#include <loadplugincommand.h>
#include <setspeectconfigcommand.h>
#include <uttprocessorcommand.h>
#include "relation.h"
#include "QTextStream"
#include <QFont>
#include <QProcess>
#include <thread>

TEST(SpeectWrapper,FetchNodeSuccessDaughter){
    Speect* sTest=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(sTest);
    builder->LoadConfig(Configuration::Voice,"./cmu_arctic_slt/voice.json").getCommandList()->executeAll();
    builder->LoadConfig(Configuration::UtteranceText,"hi everybody").getCommandList()->executeAll();
    std::list<std::string> l;
    l.push_back("Tokenize");
    l.push_back("Normalize");
    builder->WithProcessors(l).getCommandList()->executeAll();
    EXPECT_TRUE(sTest->getNode(" .n.p.daughter.R:Word.R:Token.parent.daughter","Token").size()>=2);
    delete builder;
    delete sTest;
}
TEST(SpeectWrapper,FetchNodeSuccessNext){
    Speect* sTest=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(sTest);
    builder->LoadConfig(Configuration::Voice,"./cmu_arctic_slt/voice.json").getCommandList()->executeAll();
    builder->LoadConfig(Configuration::UtteranceText,"hi everybody").getCommandList()->executeAll();
    std::list<std::string> l;
    l.push_back("Tokenize");
    l.push_back("Normalize");
    builder->WithProcessors(l).getCommandList()->executeAll();
    EXPECT_TRUE(sTest->getNode(" .n.p.daughter.R:Word.R:Token.parent.n.daughter","Token").size()>=2);
    delete builder;
    delete sTest;
}
TEST(SpeectWrapper,FetchNodeFailPath){
    Speect* sTest=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(sTest);
    builder->LoadConfig(Configuration::Voice,"./cmu_arctic_slt/voice.json").getCommandList()->executeAll();
    builder->LoadConfig(Configuration::UtteranceText,"hi everybody").getCommandList()->executeAll();
    std::list<std::string> l;
    l.push_back("Tokenize");
    l.push_back("Normalize");
    builder->WithProcessors(l).getCommandList()->executeAll();
    EXPECT_TRUE(sTest->getNode(" ..sad.n","Token").size()<2);
    delete builder;
    delete sTest;
}
TEST(SpeectWrapper,FetchNodeWrongRelation){
    Speect* sTest=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(sTest);
    builder->LoadConfig(Configuration::Voice,"./cmu_arctic_slt/voice.json").getCommandList()->executeAll();
    builder->LoadConfig(Configuration::UtteranceText,"hi everybody").getCommandList()->executeAll();
    std::list<std::string> l;
    l.push_back("Tokenize");
    l.push_back("Normalize");
    builder->WithProcessors(l).getCommandList()->executeAll();
    EXPECT_TRUE(sTest->getNode(" .n","Tokenas").size()<2);
    delete builder;
    delete sTest;
}
TEST(SpeectWrapper,FetchNodeWrongRelationANDPath){
    Speect* sTest=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(sTest);
    builder->LoadConfig(Configuration::Voice,"./cmu_arctic_slt/voice.json").getCommandList()->executeAll();
    builder->LoadConfig(Configuration::UtteranceText,"hi everybody").getCommandList()->executeAll();
    std::list<std::string> l;
    l.push_back("Tokenize");
    l.push_back("Normalize");
    builder->WithProcessors(l).getCommandList()->executeAll();
    EXPECT_TRUE(sTest->getNode(" .n.asdg.a","Tokenas").size()<=2);
    delete builder;
    delete sTest;
}
TEST(SpeectWrapper,FetchNodeOutOfBoundPath){
    Speect* sTest=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(sTest);
    builder->LoadConfig(Configuration::Voice,"./cmu_arctic_slt/voice.json").getCommandList()->executeAll();
    builder->LoadConfig(Configuration::UtteranceText,"hi everybody").getCommandList()->executeAll();
    std::list<std::string> l;
    l.push_back("Tokenize");
    l.push_back("Normalize");
    builder->WithProcessors(l).getCommandList()->executeAll();
    EXPECT_TRUE(sTest->getNode(" .n.n.n.n.n.n.n","Tokenas").size()<=2);
    delete builder;
    delete sTest;
}
TEST(SpeectWrapper,FetchNodeOutOfBoundPathReinitializedUtt){
    Speect* sTest=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(sTest);
    builder->LoadConfig(Configuration::Voice,"./cmu_arctic_slt/voice.json").getCommandList()->executeAll();
    builder->LoadConfig(Configuration::UtteranceText,"hi everybody").getCommandList()->executeAll();
    builder->LoadConfig(Configuration::UtteranceText,"hi everybody Jonny").getCommandList()->executeAll();
    std::list<std::string> l;
    l.push_back("Tokenize");
    l.push_back("Normalize");
    builder->WithProcessors(l).getCommandList()->executeAll();
    EXPECT_TRUE(sTest->getNode(" .n.n.n.n.n.n.n","Tokenas").size()<=2);
    delete builder;
    delete sTest;
}