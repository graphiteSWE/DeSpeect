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

/*
 * File: modelview.cpp
 * Type: src
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: handles all the connections among the models that define how the view is printed and communicate with the model
 */
 
/*
 * Description: ModelView constructor
 * @param CommandList::CommandBuilder* commandBuilder - builder for the command list
 * @param QWidget *parent - Qt widget as parent (see Qt docs for more info)
 */
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
    pathInput->setOkButtonText("Search");
    pathInput->setWindowTitle("Search Node path");
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

/*
 * Description: returns the View
 * @return Ui::View* 
 */
Ui::View* ModelView::getUiView() const{
    return ui;
}

//Description: ModelView destructor
ModelView::~ModelView()
{
    delete g;
    delete ui;
    delete properties;
    delete p;
}

/*
 * Description: private utility function telling the UI not to change the model dependant graphics and prints the log
 * @return void
 */
void ModelView::printLog()
{
    foreach(auto t,commands->getErrorState())
        ui->ErrorLog->appendPlainText(t.c_str());
}

/*
 * Description: doesn't allow changing while executing
 * @return void
 */
void ModelView::lockUpdateItem(){
    ui->UtteranceText->setEnabled(false);
    p->lockUpdateItem();
}

/*
 * Description: re enables changing after executing
 * @return void
 */
void ModelView::unlockUpdateItem(){
    ui->UtteranceText->setEnabled(true);
    ui->ExecuteSingle->setEnabled(true);
    p->unlockUpdateItem();
}

/*
 * Description: slots to catch ui signals and act according to the request the selectbox of utterance type changed,
 * 				tells THE processor manager to show the processors 
 * @return void
 */
void ModelView::utteranceTypeChanged()
{
    if(ui->UtteranceType->currentData().toString().toStdString()=="UserSetting")
    {
        auto processorsNames=commands->getUttProcessorsNames();
        p->clear();
        g->clear();
        for(auto it=processorsNames.begin();it!=processorsNames.end();++it){
            p->addProcessor(*it);
        }
    }
    else
    {
        auto processorsNames=commands->getUttProcessorsNames(ui->UtteranceType->currentData().toString().toStdString());
        p->clear();
        g->clear();
        for(auto it=processorsNames.begin();it!=processorsNames.end();++it){
            p->addProcessor(*it);
        }
    }
}

/*
 * Description: if a node is selected, asks the model for the real node information and then tells datanodemanager to print them
 * @param QString - Qt string as relation name (see Qt docs for more info)
 * @param QString - Qt string as path to node (see Qt docs for more info)
 * @param bool - showing status
 * @return void
 */
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

/*
 * Description: catches the request to create and execute the selected processors, also creates the utterance.
 * @param execSteps - step by step execution status
 * @return void
 */
void ModelView::requestProcessorRun(bool execSteps)
{

    if(commands==NULL || commands->getNumberCommands()<=0)// || p->isLayoutClean())
        loadSelectedProcessor();

    if(commands!=NULL && commands->getNumberCommands()>0){

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
    if(commands!=NULL && commands->getNumberCommands()==0)
        unlockUpdateItem();
}

/*
 * Description: call the request processor run with execStep=1 and allow single step execution
 * @return void
 */
void ModelView::runSingleStep()
{
    requestProcessorRun(true);
}

/*
 * Description: called by requestProcessorsRun to initialize the utterance
 * 				and by the view button to create a utterance and load the single step run
 * @return void
 */
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

/*
 * Description: requests to save the audio to the file, it's connected to the signal of the file browser
 * @param QString - Qt string as output destination (see Qt docs for more info)
 * @return void
 */
void ModelView::requestAudioSave(QString output)
{

    commands=commandsBuilder->SaveAudio(output.toStdString()).getCommandList();
    commands->executeAll();
    printLog();
}

/*
void ModelView::requestPluginLoad(const QList<QString>& pluginPaths)
{
    t9.clear();
    AbstractCommand* temp;
    foreach(auto t , pluginPaths)
    {
        t9.push_back(new LoadPluginCommand(t.toStdString()));
        temp=t9.takeFirst();
        temp->execute(s);
        delete temp;   }
}*/


/*
 * Description: creates the command to request the configuration
 * @param const QString& info - Qt string as configuration info (see Qt docs for more info)
 * @param const Configuration::configName&config = Configuration::Voice - voice config 
 * @return void
 */
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

/*
 * Description: asks the model to search the path from the selected node and print it if it's been found
 * @param const QString& - Qt string as search path (see Qt docs for more info)
 * @return void
 */
void ModelView::search(const QString &search)
{

    QString path=properties->getNodeId().getID();
    QString rel=properties->getNodeId().getRelation();

    if(rel!=""){
        path=path+"."+search;
        findNode(rel,path,false);
    }
}

