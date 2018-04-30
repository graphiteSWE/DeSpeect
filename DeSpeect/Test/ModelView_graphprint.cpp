#include "gtest/gtest.h"
#include <QApplication>
#include <commandlist.h>
#include <unistd.h>
//#define GetCurrentDir getcwd
#include "modelview.h"

TEST(View, Graphprint){
    Speect* sTest=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(sTest);
    ModelView mv(builder);
    mv.requestConfiguration("./cmu_arctic_slt/voice.json", Configuration::Voice);
    mv.loadSelectedProcessor();
    builder->LoadConfig(Configuration::UtteranceText,"hi").getCommandList()->executeAll();
    mv.runSingleStep();
    mv.requestProcessorRun();

    mv.utteranceTypeChanged();
    mv.loadSelectedProcessor();
    mv.findNode("Token","",false);
    sTest->getUttTypeName();
    EXPECT_TRUE(NULL!=sTest->getUtterance()->getUtterance());

    delete builder;
    delete sTest;
}
