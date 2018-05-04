#include "gtest/gtest.h"
#include <QApplication>
#include <commandlist.h>
#include <unistd.h>
//#define GetCurrentDir getcwd

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
#include <QGraphicsItem>

TEST(View, Graphprint){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    Speect* sTest=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(sTest);
    ModelView mv(builder);
    mv.requestConfiguration("./cmu_arctic_slt/voice.json", Configuration::Voice);
    mv.loadSelectedProcessor();
    builder->LoadConfig(Configuration::UtteranceText,"hi").getCommandList()->executeAll();
    mv.runSingleStep();
    mv.requestProcessorRun();
    mv.requestAudioSave("test.wav");
    mv.utteranceTypeChanged();
    mv.loadSelectedProcessor();
    mv.findNode("Token","",false);
    mv.findNode("Token","",true);
    sTest->getUttTypeName();
    EXPECT_TRUE(NULL!=sTest->getUtterance()->getUtterance());

    delete builder;
    delete sTest;
}

TEST(View, Graphprintcomplete){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    Speect* sTest=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(sTest);
    ModelView* mv = new ModelView(NULL);
    delete mv;
    mv= new ModelView(builder);
    mv->requestConfiguration("./cmu_arctic_slt/voice.json", Configuration::Voice);
    Ui::View* ui = mv->getUiView();
    ui->UtteranceText->setPlainText("hi");
    //mv->loadSelectedProcessor();

    mv->runSingleStep();
    mv->requestProcessorRun(false);
    mv->utteranceTypeChanged();
    ui->UtteranceType->setCurrentIndex(1);
    mv->utteranceTypeChanged();
    sTest->getUttTypeName();

    EXPECT_TRUE(NULL!=sTest->getUtterance()->getUtterance());

    delete builder;
    delete sTest;
    delete mv;
}

TEST(View, ModelViewSearch){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    Speect* sTest=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(sTest);
    ModelView* mv = new ModelView(NULL);
    delete mv;
    mv= new ModelView(builder);
    mv->requestConfiguration("./cmu_arctic_slt/voice.json", Configuration::Voice);
    Ui::View* ui = mv->getUiView();
    ui->UtteranceText->setPlainText("hi world");

    mv->loadSelectedProcessor();
    mv->requestProcessorRun(false);
    mv->findNode("Token"," ",false);
    mv->search(" .n");

    EXPECT_TRUE(NULL!=sTest->getUtterance()->getUtterance());

    delete builder;
    delete sTest;
    delete mv;
}

TEST(View, Graphprintwithmoreprocessor){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    Speect* sTest=new Speect();
    CommandList::CommandBuilder* builder=new CommandList::CommandBuilder(sTest);
    ModelView mv(builder);
    mv.requestConfiguration("./cmu_arctic_slt/voice.json", Configuration::Voice);
    mv.loadSelectedProcessor();
    builder->LoadConfig(Configuration::UtteranceText,"hi everybody").getCommandList()->executeAll();
    mv.runSingleStep();
    mv.runSingleStep();
    mv.runSingleStep();
    mv.requestProcessorRun();
    mv.requestAudioSave("test.wav");
    mv.utteranceTypeChanged();
    mv.loadSelectedProcessor();
    mv.findNode("Token","",false);
    mv.findNode("Token","",true);
    sTest->getUttTypeName();
    EXPECT_TRUE(NULL!=sTest->getUtterance()->getUtterance());

    delete builder;
    delete sTest;
}
