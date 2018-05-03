#ifndef PROCESSORMANAGER_H
#define PROCESSORMANAGER_H
#include <QStandardItemModel>
#include <QStandardItem>
#include <QListView>

/*
 * File: processormanager.h
 * Type: header
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: handles the model that allows the printing of the processors
 */
 
class ProcessorManager : public QObject
{
    //Macro used to enable Qt signals and slots
    Q_OBJECT
    
private:
    //Field: model of the processors
    QStandardItemModel* ProcessorModel;

    //Field: index of the current processor execution
    int indexProcessor;

public:
    // Description: ProcessorManager constructor
    ProcessorManager();
    // Description: ProcessorManager destructor
    ~ProcessorManager();

    /*
     * Description: links the view to the model
     * @param QListView* v - Qt list view (see Qt docs for more info)
     * @return void
     */
    void linkProcessorModel(QListView* v);
    
    /*
     * Description: sets all the items to the normal font and the last executed processor to none
     * @return void
     */
    void clearLayoutProcessor();
    
    /*
     * Description: locks changes in the model, used while executing
     * @return void
     */
    void lockUpdateItem();
    
    /*
     * Description: unlocks changes in the model
     * @return void
     */
    void unlockUpdateItem();
    
    /*
     * Description: changes the font color to the next processor
     * @return void
     */
    void evidenceNextProcessor();
    
    /*
     * Description: changes the font color of all the processors, if index is valid set the item to bold
     * @return void
     */
    void evidenceAllProcessor();
    
    /*
     * Description: returns whether the index of the processor is valid
     * @return bool
     */
    bool isLayoutClean();
    
    /*
     * Description: returns the list of the selected processor
     * @return std::list<std::string>
     */
    std::list<std::string> getProcessorList();
    
    /*
     * Description: adds a processor to the model
     * @param std::string name - processor name
     * @return void
     */
    void addProcessor(std::string name);
    
    /*
     * Description: clears the model
     * @return void
     */
    void clear();
};

#endif // PROCESSORMANAGER_H
