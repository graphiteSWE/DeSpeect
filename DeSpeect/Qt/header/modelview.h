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

class ModelView : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModelView(CommandList::CommandBuilder* commandBuilder,QWidget *parent = 0);
    ~ModelView();
private:
    CommandList::CommandBuilder* commandsBuilder;
    CommandList* commands;
    //here start the real var
    bool utteranceIsProcessed=false;
    GraphManager* g;
    DataNodeManager *properties;
    ProcessorManager* p;
    Ui::View *ui;
    QVector<QColor>colors;
    void printLog();
    void clearLayoutProcessor();
    void lockUpdateItem();
    void unlockUpdateItem();
    void evidenceNextProcessor();
    void evidenceAllProcessor();
public slots:
    void utteranceTypeChanged();
    void findNode(QString,QString,bool);
    void requestProcessorRun(bool execSteps=0);
    void runSingleStep();
    void loadSelectedProcessor();
    void requestAudioSave(QString);
    void requestConfiguration(const QString& info,const Configuration::configName&config = Configuration::Voice);


    //void requestPluginLoad(const QList<QString>&);

};

#endif // MODELVIEW_H
