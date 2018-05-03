#include "gtest/gtest.h"
#include <QApplication>
#include "arc.h"

#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include <QColor>
#include "item.h"
#include "graphmanager.h"
#include "relation.h"
#include <QGraphicsView>

#include "../Model/Command/header/setspeectconfigcommand.h"
#include "../Model/SpeectWrapper/header/Speect.h"
#include "../Model/Command/header/createaudiocommand.h"
#include "../Model/Command/header/commandlist.h"

TEST(Graph, VerifyChangeRelationVisibility){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    GraphManager* g = new GraphManager();
    g->changeRelationVisibility(new QStandardItem());
    EXPECT_TRUE(g);

    delete g;
}

TEST(Graph, VerifyChangeRelationVisibility2){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);

    GraphManager* g = new GraphManager();

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
    foreach (auto t,commands->getRelationNames())
    {
        const Relation* currentRelation = commands->getRelation(t);
        Item temp(currentRelation->getRelationHead());
        g->printRelation(QString(t.c_str()),&temp,QColor(255,255,255));
        delete currentRelation;


    }
    QStandardItem* i=new QStandardItem("Token");
    g->changeRelationVisibility(i);
    EXPECT_TRUE(g);

    delete g;
}

TEST(Graph, VerifyNotifySelection){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    GraphManager* g = new GraphManager();
    g->notifySelection();
    EXPECT_TRUE(g);
    delete g;
}

TEST(Graph, VerifyNotifySelection1){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);

    GraphManager* g = new GraphManager();

    QGraphicsView* gView= new QGraphicsView();
    g->linkGraphModel(gView);

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
    foreach (auto t,commands->getRelationNames())
    {
        const Relation* currentRelation = commands->getRelation(t);
        Item temp(currentRelation->getRelationHead());
        g->printRelation(QString(t.c_str()),&temp,QColor(255,255,255));
        delete currentRelation;
    }
    QList<QGraphicsItem *> list = gView->items();

    foreach(auto item,list)
    {
        item->setSelected(true);
    }

    g->notifySelection();

    EXPECT_TRUE(g);
}

TEST(Graph, VerifySelectItem){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    GraphManager* g = new GraphManager();
    g->selectItem("Token"," ");
    EXPECT_TRUE(g);

    delete g;
}


TEST(Graph, VerifyGenerateRelation){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);

    GraphManager* g = new GraphManager();

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
    foreach (auto t,commands->getRelationNames())
    {
        const Relation* currentRelation = commands->getRelation(t);
        Item temp(currentRelation->getRelationHead());
        g->printRelation(QString(t.c_str()),&temp,QColor(255,255,255));
        g->printRelation(QString(t.c_str()),&temp,QColor(255,255,255));
        delete currentRelation;
    }

    g->notifySelection();

    EXPECT_TRUE(g);
}

