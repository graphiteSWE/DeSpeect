#ifndef MODELVIEW_H
#define MODELVIEW_H
namespace Ui {
class View;
}
#include <QMainWindow>
#include <QStandardItemModel>
#include <Speect.h>
#include <commandlist.h>
#include "configuration.h"
#include "datanodemanager.h"
#include <processormanager.h>


class GraphManager;
//this class handle all connection between the models that
//defines how the view is printed and communicate with the model
class ModelView : public QMainWindow
{
    //derives from qobject and implement signals and slot
    Q_OBJECT

public:
    //allow to build the model view
    explicit ModelView(CommandList::CommandBuilder* commandBuilder,QWidget *parent = 0);
    //destroy the modelview
    Ui::View* getUiView() const;
    ~ModelView();
private:
    //pointer to the builder that will allow to build commandlist
    CommandList::CommandBuilder* commandsBuilder;
    //allow to execute commands on the model and request specific data from it
    CommandList* commands;
    //models the speect graph,and allow the display of it
    GraphManager* g;
    //model the properties of a node and the display of them
    DataNodeManager *properties;
    //model the processors in a given utterance and allow to display them
    ProcessorManager* p;
    //QML of the view
    Ui::View *ui;
    //list of all colors available to print the graph
    QVector<QColor>colors;
    //private function of utility
    //that tell the ui to change not model dependant graphics
    //print the error log
    void printLog();
    //don't allow change while executing
    void lockUpdateItem();
    //re enable changes to execution
    void unlockUpdateItem();
public slots:
    //slots to catch ui signal and act based on the request
    //the selectbox of utterance type changed, tell processor manager to show the processors
    void utteranceTypeChanged();
    //a node is selected ask the model the real node information and then tell datanodemanager to print them
    void findNode(QString,QString,bool);
    //catch the request to create and execute the selected processors, also create the utterance.
    void requestProcessorRun(bool execSteps=0);
    //this call the request processor run with execStep=1 and allow single step execution
    void runSingleStep();
    //called by request processors run to initialize the utterance,
    //and by the view button to create a utterance and load the single step run
    void loadSelectedProcessor();
    //request to save the audio to the file, it's connected to the signal of the file browser
    void requestAudioSave(QString);
    //create the command to request the configuration
    void requestConfiguration(const QString& info,const Configuration::configName&config = Configuration::Voice);

    //void requestPluginLoad(const QList<QString>&);

};

#endif // MODELVIEW_H
