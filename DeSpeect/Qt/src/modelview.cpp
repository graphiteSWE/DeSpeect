#include "modelview.h"
#include "ui_view.h"
#include <QFileDialog>
#include <graphmanager.h>
#include <loadplugincommand.h>
#include <setspeectconfigcommand.h>
#include <uttprocessorcommand.h>
#include "relation.h"

#include <QFont>
ModelView::ModelView(CommandList::CommandBuilder *builder, QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::View)
    ,g(new GraphManager())
    ,p(new ProcessorManager())
    ,commandsBuilder(builder)
    ,commands(NULL)
{
    ui->setupUi(this);
    g->linkGraphModel(ui->graphicsView);
    g->linkRelationModel(ui->relationsView);
    p->linkProcessorModel(ui->ProcessorsView);
    QFileDialog *t=new QFileDialog(this);
    t->setNameFilter("*.json");
    colors.push_back(QColor(qRgb(172,25,248)));
    colors.push_back(QColor(qRgb(5,210,153)));
    colors.push_back(QColor(qRgb(71,194,52)));
    colors.push_back(QColor(qRgb(24,241,95)));
    colors.push_back(QColor(qRgb(199,1,7)));
    colors.push_back(QColor(qRgb(63,230,150)));
    colors.push_back(QColor(qRgb(151,157,0)));
    connect(ui->actionLoadVoice,SIGNAL(triggered(bool)),t,SLOT(open()));
    connect(ui->loadVoiceButton,SIGNAL(clicked()),t,SLOT(open()));
    connect(t,SIGNAL(fileSelected(QString)),this,SLOT(requestConfiguration(QString)));
    connect(t,SIGNAL(fileSelected(QString)),ui->VoicePath,SLOT(setText(QString)));

    connect(ui->ExecuteAll,SIGNAL(clicked()),this,SLOT(requestProcessorRun()));
    connect(ui->ExecuteSingle,SIGNAL(clicked()),this,SLOT(runSingleStep()));
    connect(ui->LoadProcessor,SIGNAL(clicked()),this,SLOT(loadSelectedProcessor()));

}

ModelView::~ModelView()
{
    delete g;
    delete ui;
}

void ModelView::lockUpdateItem(){
    ui->UtteranceText->setEnabled(false);
    p->lockUpdateItem();
}

void ModelView::unlockUpdateItem(){
    ui->UtteranceText->setEnabled(true);    
    ui->ExecuteSingle->setEnabled(true);
    p->unlockUpdateItem();
}


void ModelView::requestProcessorRun(bool execSteps)
{

    if(commands==NULL || !execSteps || p->isLayoutClean())
        loadSelectedProcessor();

    if(ui->UtteranceText->toPlainText()!=NULL && commands!=NULL){

        if(!execSteps){
            p->evidenceAllProcessor();
            unlockUpdateItem();
            commands->executeAll();            
            ui->ExecuteSingle->setEnabled(false);
        }
        else{
            if(commands->getNumberCommands()<=1){
                unlockUpdateItem();
                ui->ExecuteSingle->setEnabled(false);
            }
            else{
                lockUpdateItem();
            }
            p->evidenceNextProcessor();
            commands->executeStep();
        }

        int i=0;

        g->clear();

        foreach (auto t,commands->getRelationNames())
        {
            const Relation* currentRelation = commands->getRelation(t);
            Item temp(currentRelation->getRelationHead());
            g->printRelation(QString(t.c_str()),&temp,colors.at(i));
            delete currentRelation;
            ++i;
        }
    }
}

void ModelView::runSingleStep()
{
    requestProcessorRun(true);
}

void ModelView::loadSelectedProcessor(){

    g->clear();
    commandsBuilder->LoadConfig(Configuration::UtteranceText,ui->UtteranceText->toPlainText().toStdString());
    commands=commandsBuilder->getCommandList();
    commands->executeAll();//Execute load configuration commands

    p->clearLayoutProcessor();
    unlockUpdateItem();

    commandsBuilder->WithProcessors(p->getProcessorList());
    commands=commandsBuilder->getCommandList();

}

void ModelView::requestPluginRun()
{

}


void ModelView::requestPluginLoad(const QList<QString>& pluginPaths)
{
/*
    t9.clear();
    AbstractCommand* temp;
    foreach(auto t , pluginPaths)
    {
        t9.push_back(new LoadPluginCommand(t.toStdString()));
        temp=t9.takeFirst();
        tem//p->execute(s);
        delete temp;
    }
*/
}
void ModelView::requestConfiguration(const QString &info, const Configuration::configName &config)
{

    commands=commandsBuilder->LoadConfig(config,info.toStdString()).getCommandList();
    commands->executeAll();
    if(config==Configuration::Voice)
    {
        auto processorsNames=commands->getUttProcessorsNames();
        p->clear();
        for(auto it=processorsNames.begin();it!=processorsNames.end();++it){
            p->addProcessor((*it));
        }
    }
}
