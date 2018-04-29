#ifndef PROCESSORMANAGER_H
#define PROCESSORMANAGER_H

#include <QStandardItemModel>
#include <QStandardItem>
#include <QListView>
//this class handle the model that allow printing of the processors

class ProcessorManager : public QObject
{
    Q_OBJECT
private:
    //model of the processors
    QStandardItemModel* ProcessorModel;
    //index of current processor execution
    int indexProcessor;

public:
    //build the manager
    ProcessorManager();
    //clear memory before destruction
    ~ProcessorManager();

    //link the view to the model
    void linkProcessorModel(QListView* v);
    //set all items to normal font and last executed processor to none
    void clearLayoutProcessor();
    //lock changes in the model
    //used while executing
    void lockUpdateItem();
    //unlock changes in the model
    void unlockUpdateItem();
    //change font color to the next processor
    void evidenceNextProcessor();
    //change font color of all processors if index is valid set item to bold
    void evidenceAllProcessor();
    //return if index of processor is valid
    bool isLayoutClean();
    //return the list of selected processor
    std::list<std::string> getProcessorList();
    //add a processor to the model
    void addProcessor(std::string name);
    //clear the  model
    void clear();
};

#endif // PROCESSORMANAGER_H
