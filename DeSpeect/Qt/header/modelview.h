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

/*
 * File: modelview.h
 * Type: header
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: handles all the connections among the models that define how the view is printed and communicate with the model
 */
 
class ModelView : public QMainWindow
{
    //Macro used to enable Qt signals and slots
    Q_OBJECT
    
public:
    /*
     * Description: ModelView constructor
     * @param CommandList::CommandBuilder* commandBuilder - builder for the command list
     * @param QWidget *parent - Qt widget as parent (see Qt docs for more info)
     */
    explicit ModelView(CommandList::CommandBuilder* commandBuilder,QWidget *parent = 0);
    
    /*
     * Description: returns the View
     * @return Ui::View* 
     */
    Ui::View* getUiView() const;
    
    //Description: ModelView destructor
    ~ModelView();
private:

	//Field: pointer to the builder that allows to build a command list
    CommandList::CommandBuilder* commandsBuilder;
    
    //Field: allows to execute commands on the model and request specific data from it
    CommandList* commands;
    
    //Field: models the speect graph and allows its display
    GraphManager* g;
    
    //Field: models the set of properties of a node and their display
    DataNodeManager *properties;
    
    //Field: models the processors in a given utterance and allows their display
    ProcessorManager* p;
    
    //Field: qml of the view (see Qt docs for more info)
    Ui::View *ui;
    
    //Field: list of all colors available to print the graph
    QVector<QColor>colors;
    
    /*
     * Description: private utility function telling the UI not to change the model dependant graphics and prints the log
     * @return void
     */
    void printLog();
    
    /*
     * Description: doesn't allow changing while executing
     * @return void
     */
    void lockUpdateItem();
    
    /*
     * Description: re enables changing after executing
     * @return void
     */
    void unlockUpdateItem();
    
public slots:
    
    /*
     * Description: slots to catch ui signals and act according to the request the selectbox of utterance type changed,
     * 				tells THE processor manager to show the processors 
     * @return void
     */
    void utteranceTypeChanged();
    
    /*
     * Description: if a node is selected, asks the model for the real node information and then tells datanodemanager to print them
     * @param QString - Qt string as relation name (see Qt docs for more info)
     * @param QString - Qt string as path to node (see Qt docs for more info)
     * @param bool - showing status
     * @return void
     */
    void findNode(QString,QString,bool);
    
    /*
     * Description: catches the request to create and execute the selected processors, also creates the utterance.
     * @param execSteps - step by step execution status
     * @return void
     */
    void requestProcessorRun(bool execSteps=0);
    
    /*
     * Description: call the request processor run with execStep=1 and allow single step execution
     * @return void
     */
    void runSingleStep();
    
    /*
     * Description: called by requestProcessorsRun to initialize the utterance
     * 				and by the view button to create a utterance and load the single step run
     * @return void
     */
    void loadSelectedProcessor();
    
    /*
     * Description: requests to save the audio to the file, it's connected to the signal of the file browser
     * @param QString - Qt string as output destination (see Qt docs for more info)
     * @return void
     */
    void requestAudioSave(QString);
    
    /*
     * Description: creates the command to request the configuration
     * @param const QString& info - Qt string as configuration info (see Qt docs for more info)
     * @param const Configuration::configName&config = Configuration::Voice - voice config 
     * @return void
     */
    void requestConfiguration(const QString& info,const Configuration::configName&config = Configuration::Voice);
    
    /*
     * Description: asks the model to search the path from the selected node and print it if it's been found
     * @param const QString& - Qt string as search path (see Qt docs for more info)
     * @return void
     */
    void search(const QString&);

    /*
     * Description: open the user manual
     * @return void
     */
    void manual();
};

#endif // MODELVIEW_H
