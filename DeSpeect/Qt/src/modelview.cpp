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
#include <QInputDialog>
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
    QInputDialog *pathInput=new QInputDialog(this);
    pathInput->setInputMode(QInputDialog::TextInput);
    //this is the relations colors after 10 relation start from beginning
    colors.push_back(QColor(qRgb(213,0,0)));
    colors.push_back(QColor(qRgb(120,144,156)));
    colors.push_back(QColor(qRgb(170,0,255)));
    colors.push_back(QColor(qRgb(109,76,65)));
    colors.push_back(QColor(qRgb(251,140,0)));
    colors.push_back(QColor(qRgb(67,160,61)));
    colors.push_back(QColor(qRgb(41,98,255)));
    colors.push_back(QColor(qRgb(255,214,0)));
    colors.push_back(QColor(qRgb(0,184,212)));
    colors.push_back(QColor(qRgb(0,191,165)));
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
    connect(g,SIGNAL(focusSignal(QString,QString,bool)),this,SLOT(findNode(QString,QString,bool)));
    connect(ui->actionExit,SIGNAL(triggered(bool)),qApp,SLOT(quit()));
    connect(ui->actionSearch_path,SIGNAL(triggered(bool)),pathInput,SLOT(open()));
    connect(pathInput,SIGNAL(textValueSelected(QString)),this,SLOT(search(QString)));
    connect(g,SIGNAL(cleardetails()),properties,SLOT(clear()));
}

Ui::View* ModelView::getUiView() const{
    return ui;
}

ModelView::~ModelView()
{
    delete g;
    delete ui;
    delete properties;
    delete p;
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
#include "iostream"
void ModelView::findNode(QString rel, QString path, bool show)
{
    std::map<std::string,std::string> m = commands->getNode(rel.toStdString(),path.toStdString());

    if(show){
        properties->showNode(m);
    }
    else{
        auto it=m.find("DespeectItemIDPath");
        QString path="";
        QString relation="";
        if(it!=m.end())
        {
            path=it->second.c_str();
        }
        it=m.find("DespeectItemIDRelation");
        if(it!=m.end())
        {
            relation=it->second.c_str();
        }
        if(relation!="")
        {
        ui->graphicsView->setFocus();
        g->selectItem(relation,path);
        }
        else{
            ui->ErrorLog->setFocus();
        }
        printLog();

    }
    commands->clearErrorState();
}

void ModelView::requestProcessorRun(bool execSteps)
{

    if(commands==NULL || commands->getNumberCommands()<=0)// || p->isLayoutClean())
        loadSelectedProcessor();

    if(commands!=NULL&&commands->getNumberCommands()>0){

        if(!execSteps){
            p->evidenceAllProcessor();
            unlockUpdateItem();
            commands->executeAll();
        }
        else{
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
            g->printRelation(QString(t.c_str()),&temp,colors.at(i%colors.size()));
            delete currentRelation;
            ++i;
        }
    }
    if(commands->getNumberCommands()==0)
        unlockUpdateItem();
}

void ModelView::runSingleStep()
{
    requestProcessorRun(true);
}

void ModelView::loadSelectedProcessor(){

    if(ui->UtteranceText->toPlainText()!=NULL){
    g->clear();
    commandsBuilder->LoadConfig(Configuration::UtteranceText,ui->UtteranceText->toPlainText().toStdString());
    commands=commandsBuilder->getCommandList();
    commands->executeAll();//Execute load configuration commands
    printLog();
    p->clearLayoutProcessor();
    lockUpdateItem();
    commandsBuilder->WithProcessors(p->getProcessorList());
    commands=commandsBuilder->getCommandList();
    }
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
void ModelView::search(const QString &search)
{

    QString path=properties->getNodeId().getID();
    QString rel=properties->getNodeId().getRelation();
    if(rel!=""){
    path=path+"."+search;
    findNode(rel,path,false);
    }
}

