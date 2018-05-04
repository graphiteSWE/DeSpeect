#include "gtest/gtest.h"
#include <QApplication>
#include <processormanager.h>

#include <QStandardItemModel>
#include <QStandardItem>
#include <QListView>
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



TEST(Graph, VerifyProcessorManagerEvidenceAll2){
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

    QAbstractItemModel* qListModel=qList->model();

    QStandardItemModel* model = dynamic_cast <QStandardItemModel*>(qListModel);

    if(model){
        model->item(2)->setCheckState(Qt::Unchecked);
    }


    p->evidenceNextProcessor();
    p->evidenceNextProcessor();
    p->evidenceNextProcessor();
    p->evidenceAllProcessor();

    p->clearLayoutProcessor();

    EXPECT_TRUE(p);

    delete p;

}
