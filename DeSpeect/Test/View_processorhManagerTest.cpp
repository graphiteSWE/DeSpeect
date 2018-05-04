#include "gtest/gtest.h"
#include <QApplication>
#include <processormanager.h>
TEST(Graph, VerifyProcessorManagerIsClear){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);

    ProcessorManager *p=new ProcessorManager();

    p->clear();

    EXPECT_TRUE(p->isLayoutClean());

    delete p;

}

TEST(Graph, VerifyProcessorManagerEvidenceNext){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);

    ProcessorManager *p=new ProcessorManager();
    QListView* qList= new QListView();

    p->linkProcessorModel(qList);

    p->addProcessor("");
    p->addProcessor("a");
    p->addProcessor("b");
    p->addProcessor("c");
    p->addProcessor("d");
    p->addProcessor("e");

    p->evidenceNextProcessor();
    p->evidenceNextProcessor();
    p->evidenceNextProcessor();
    p->evidenceNextProcessor();
    p->evidenceNextProcessor();
    p->evidenceNextProcessor();

    p->clearLayoutProcessor();

    EXPECT_TRUE(p);

    delete p;

}

TEST(Graph, VerifyProcessorManagerEvidenceAll){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);

    ProcessorManager *p=new ProcessorManager();
    QListView* qList= new QListView();

    p->linkProcessorModel(qList);

    p->addProcessor("");
    p->addProcessor("a");
    p->addProcessor("b");
    p->addProcessor("c");
    p->addProcessor("d");
    p->addProcessor("e");

    p->evidenceAllProcessor();

    p->clearLayoutProcessor();

    EXPECT_TRUE(p);

    delete p;

}
