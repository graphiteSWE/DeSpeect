#include "gtest/gtest.h"
#include <QApplication>
#include <commandlist.h>
#include <unistd.h>
//#define GetCurrentDir getcwd
#include "iostream"
#include "ui_view.h"
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

TEST(SpeectWrapper,FetchNodeSuccess){
    Speect* sTest=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(sTest);
    builder->LoadConfig(Configuration::Voice,"./cmu_arctic_slt/voice.json").getCommandList()->executeAll();
    builder->LoadConfig(Configuration::UtteranceText,"hi everybody").getCommandList()->executeAll();
    std::list<std::string> l;
    l.push_back("Tokenize");
    builder->WithProcessors(l).getCommandList()->executeAll();
    EXPECT_TRUE(sTest->getNode(" .n","Token").size()>=2);
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
    builder->WithProcessors(l).getCommandList()->executeAll();
    EXPECT_TRUE(sTest->getNode(" .n.n.n.n.n.n.n","Tokenas").size()<=2);
    delete builder;
    delete sTest;
}