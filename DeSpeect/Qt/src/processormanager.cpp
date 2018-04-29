#include "processormanager.h"

//initialize the processor manager to point to no processor and have a clear model
ProcessorManager::ProcessorManager():indexProcessor(-1),ProcessorModel(new QStandardItemModel())
{}

//clear and delete all data from the manager before delete
ProcessorManager::~ProcessorManager()
{
    clear();
    delete ProcessorModel;
}

//accept a view and it link to the model
void ProcessorManager::linkProcessorModel(QListView* v)
{
    v->setModel(ProcessorModel);
}

//clear the layout
void ProcessorManager::clearLayoutProcessor(){
    //create a new standard font
    QFont font;
    font.setBold(false);
    //foreach processor set that is checkable and editable,also set the base font and the color
    for(int i=0;i<ProcessorModel->rowCount();++i){
        ProcessorModel->item(i)->setCheckable(true);
        ProcessorModel->item(i)->setEditable(true);
        ProcessorModel->item(i)->setFont(font);
        ProcessorModel->item(i)->setForeground(Qt::white);
    }
    //set the current processor to outof bound (none selected)
    indexProcessor=-1;
}

//lock the items so that they can't be modified
void ProcessorManager::lockUpdateItem(){
    for(int i=0;i<ProcessorModel->rowCount();++i)
    {
        ProcessorModel->item(i)->setCheckable(false);
        ProcessorModel->item(i)->setEnabled(false);
    }
}

//unlock each item of the model
void ProcessorManager::unlockUpdateItem(){
    for(int i=0;i<ProcessorModel->rowCount();++i)
    {
        ProcessorModel->item(i)->setCheckable(true);
        ProcessorModel->item(i)->setEnabled(true);
    }
}


//evidence the processor
void ProcessorManager::evidenceNextProcessor(){
    //create a new font
    QFont font;
    //if there is a processor in the model and if the selected processor
    //the selected processor is not the last 
    if(ProcessorModel->rowCount()-1>indexProcessor){
        //store the index of the processor
        int oldIndex = indexProcessor;
        //find the next processor that is checked in the model and set the index to that
        do{
            indexProcessor++;
        }while(ProcessorModel->rowCount()>indexProcessor && ProcessorModel->item(indexProcessor)->checkState()!=Qt::Checked);
        //if the new index of processor is in the bound of the processors model
        if(ProcessorModel->rowCount()>indexProcessor){
            if(oldIndex!=-1){
                //if there was an old selected processor
                //reset it's font to standard
                font.setBold(false);
                ProcessorModel->item(oldIndex)->setFont(font);
            }
            //set the new processor font to the focused font
            font.setBold(true);
            ProcessorModel->item(indexProcessor)->setFont(font);
            ProcessorModel->item(indexProcessor)->setForeground(Qt::green);
        }
    }
}

//evidence all the processor in the model
void ProcessorManager::evidenceAllProcessor(){
    QFont font;
    font.setBold(false);
    //if there are processors in the model
    if(ProcessorModel->rowCount()>0)
    {
        //for each processor if item is checked set execution font
        for(int i=0;i<ProcessorModel->rowCount();++i){
            if(ProcessorModel->item(i)->checkState()==Qt::Checked){
                ProcessorModel->item(i)->setFont(font);
                ProcessorModel->item(i)->setForeground(Qt::green);
                indexProcessor=i;
            }
        }
        //if the selected processor is in bound set the focus font
        if(indexProcessor!=-1){
            font.setBold(true);
            ProcessorModel->item(indexProcessor)->setFont(font);
        }
    }
}


//return the processor list name
std::list<std::string> ProcessorManager::getProcessorList(){
    std::list<std::string> list;
    //if the processor is checked add it to the list of processor that have to be runned
    for(int i=0;i<ProcessorModel->rowCount();++i){
        if(ProcessorModel->item(i)->checkState()==Qt::Checked){
            list.push_back(ProcessorModel->item(i)->text().toStdString());
        }
    }
    return list;
}

//check if there is a focused processor
bool ProcessorManager::isLayoutClean(){
    return indexProcessor==-1;
}

//add a processor to the model
void ProcessorManager::addProcessor(std::string name){
    //set the mane to the processor name
    QStandardItem* item = new QStandardItem(name.c_str());
    //set that is checkable to allow selection
    item->setCheckable(true);
    //set that is not selectable to avoid change to the name
    item->setSelectable(false);
    //set the default state to checked
    item->setCheckState(Qt::Checked);
    //add the item to the model
    ProcessorModel->appendRow(item);
}

//clear the model
void ProcessorManager::clear()
{

    //for each item in the model delete it
    for(int i=0;i<ProcessorModel->rowCount();++i)
    {
        delete ProcessorModel->item(i);
    }
    //remove all item from the model otherwise would have bad pointer in it
    ProcessorModel->clear();
}
