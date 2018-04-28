#include "modelview.h"
#include "ui_view.h"
#include <QFileDialog>
#include <graphmanager.h>
#include <loadplugincommand.h>
#include <setspeectconfigcommand.h>
#include <uttprocessorcommand.h>
#include "relation.h"
#include "QTextStream"
#include <QFont>
#include <QProcess>
ModelView::ModelView(CommandList::CommandBuilder *builder, QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::View)
    ,g(new GraphManager())
    ,p(new ProcessorManager())
    ,commandsBuilder(builder)
    ,commands(NULL)
    ,properties(new DataNodeManager())
{
    ui->setupUi(this);
    g->linkGraphModel(ui->graphicsView);
    g->linkRelationModel(ui->relationsView);
    p->linkProcessorModel(ui->ProcessorsView);
    properties->linkToModel(ui->PropertyTable);
    QFileDialog *t=new QFileDialog(this);
    t->setNameFilter("*.json");
    QFileDialog *FileCreator=new QFileDialog(this);
    FileCreator->setAcceptMode(QFileDialog::AcceptSave);
    colors.push_back(QColor(qRgb(172,25,248)));
    colors.push_back(QColor(qRgb(5,210,153)));
    colors.push_back(QColor(qRgb(71,194,52)));
    colors.push_back(QColor(qRgb(24,241,95)));
    colors.push_back(QColor(qRgb(199,1,7)));
    colors.push_back(QColor(qRgb(63,230,150)));
    colors.push_back(QColor(qRgb(151,157,0)));
    connect(ui->LogClear,SIGNAL(clicked(bool)),ui->ErrorLog,SLOT(clear()));
    connect(ui->actionLoadVoiceJSon,SIGNAL(triggered(bool)),t,SLOT(open()));
    connect(ui->loadVoiceButton,SIGNAL(clicked()),t,SLOT(open()));
    connect(ui->actionSave_wav,SIGNAL(triggered(bool)),FileCreator,SLOT(open()));
    connect(t,SIGNAL(fileSelected(QString)),this,SLOT(requestConfiguration(QString)));
    connect(t,SIGNAL(fileSelected(QString)),ui->VoicePath,SLOT(setText(QString)));
    connect(FileCreator,SIGNAL(fileSelected(QString)),this,SLOT(requestAudioSave(QString)));
    connect(ui->UtteranceType,SIGNAL(currentIndexChanged(int)),this,SLOT(utteranceTypeChanged()));
    connect(ui->ExecuteAll,SIGNAL(clicked()),this,SLOT(requestProcessorRun()));
    connect(ui->ExecuteSingle,SIGNAL(clicked()),this,SLOT(runSingleStep()));
    connect(ui->LoadProcessor,SIGNAL(clicked()),this,SLOT(loadSelectedProcessor()));
    connect(g,SIGNAL(focusSignal(QString,QString,bool)),this,SLOT(findNode(QString,QString,bool)));

}

ModelView::~ModelView()
{
    delete g;
    delete ui;
}

void ModelView::printLog()
{
    foreach(auto t,commands->getErrorState())
        ui->ErrorLog->appendPlainText(t.c_str());
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

void ModelView::utteranceTypeChanged()
{
    if(ui->UtteranceType->currentData().toString().toStdString()=="UserSetting")
    {
        auto processorsNames=commands->getUttProcessorsNames();
        p->clear();
        g->clear();
        for(auto it=processorsNames.begin();it!=processorsNames.end();++it){
            p->addProcessor((*it));
        }
    }
    else
    {
        auto processorsNames=commands->getUttProcessorsNames(ui->UtteranceType->currentData().toString().toStdString());
        p->clear();
        g->clear();
        for(auto it=processorsNames.begin();it!=processorsNames.end();++it){
            p->addProcessor((*it));
        }
    }
}

void ModelView::findNode(QString rel, QString path, bool show)
{
    if(show){
        std::map<std::string,std::string> m = commands->getNode(rel.toStdString(),path.toStdString());
        properties->showNode(m);
    }
    else{
        properties->clear();
    }
}

void ModelView::requestProcessorRun(bool execSteps)
{

    if(commands==NULL || !execSteps)// || p->isLayoutClean())
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
        printLog();
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
    printLog();
    p->clearLayoutProcessor();
    unlockUpdateItem();
    commandsBuilder->WithProcessors(p->getProcessorList());
    commands=commandsBuilder->getCommandList();

}

void ModelView::requestAudioSave(QString output)
{

    commands=commandsBuilder->SaveAudio(output.toStdString()).getCommandList();
    commands->executeAll();
    printLog();
}

/*
void ModelView::requestPluginLoad(const QList<QString>& pluginPaths)
{/*
    t9.clear();
    AbstractCommand* temp;
    foreach(auto t , pluginPaths)
    {
        t9.push_back(new LoadPluginCommand(t.toStdString()));
        temp=t9.takeFirst();
        temp->execute(s);
        delete temp;   }
}*/
void ModelView::requestConfiguration(const QString &info, const Configuration::configName &config)
{

    commands=commandsBuilder->LoadConfig(config,info.toStdString()).getCommandList();
    commands->executeAll();
    printLog();
    if(config==Configuration::Voice)
    {
        utteranceTypeChanged();
        ui->UtteranceType->clear();
        ui->UtteranceType->addItem("User defined",QVariant("UserSetting"));
        foreach(auto t,commands->getUttTypeNames())
        {
            ui->UtteranceType->addItem(t.c_str(),QVariant(t.c_str()));
        }
    }
}
