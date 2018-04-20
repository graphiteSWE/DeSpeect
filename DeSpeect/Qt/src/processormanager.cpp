#include "processormanager.h"

ProcessorManager::ProcessorManager():indexProcessor(-1),ProcessorModel(new QStandardItemModel())
{

}

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

void ProcessorManager::clearLayoutProcessor(){
    QFont font;
    font.setBold(false);
    for(int i=0;i<ProcessorModel->rowCount();++i){
        ProcessorModel->item(i)->setCheckable(true);
        ProcessorModel->item(i)->setEditable(true);
        ProcessorModel->item(i)->setFont(font);
        ProcessorModel->item(i)->setForeground(Qt::white);
    }
    indexProcessor=-1;
}

void ProcessorManager::lockUpdateItem(){
    for(int i=0;i<ProcessorModel->rowCount();++i)
    {
        ProcessorModel->item(i)->setCheckable(false);
        ProcessorModel->item(i)->setEnabled(false);
    }
}

void ProcessorManager::unlockUpdateItem(){
    for(int i=0;i<ProcessorModel->rowCount();++i)
    {
        ProcessorModel->item(i)->setCheckable(true);
        ProcessorModel->item(i)->setEnabled(true);
    }
}


void ProcessorManager::evidenceNextProcessor(){
    QFont font;
    if(ProcessorModel->rowCount()-1>indexProcessor){
        int oldIndex = indexProcessor;

        do{
            indexProcessor++;
        }while(ProcessorModel->rowCount()>indexProcessor && ProcessorModel->item(indexProcessor)->checkState()!=Qt::Checked);

        if(ProcessorModel->rowCount()>indexProcessor){
            if(oldIndex!=-1){
                font.setBold(false);
                ProcessorModel->item(oldIndex)->setFont(font);
            }
            font.setBold(true);
            ProcessorModel->item(indexProcessor)->setFont(font);
            ProcessorModel->item(indexProcessor)->setForeground(Qt::green);
        }
    }
}


void ProcessorManager::evidenceAllProcessor(){
    QFont font;
    font.setBold(false);
    for(int i=0;i<ProcessorModel->rowCount();++i){
        if(ProcessorModel->item(i)->checkState()==Qt::Checked){
            ProcessorModel->item(i)->setFont(font);
            ProcessorModel->item(i)->setForeground(Qt::green);
            indexProcessor=i;
        }
    }
    if(ProcessorModel->rowCount()>0){
        font.setBold(true);
        ProcessorModel->item(indexProcessor)->setFont(font);
    }
}

std::list<std::string> ProcessorManager::getProcessorList(){
    std::list<std::string> list;

    for(int i=0;i<ProcessorModel->rowCount();++i){
        if(ProcessorModel->item(i)->checkState()==Qt::Checked){
            list.push_back(ProcessorModel->item(i)->text().toStdString());
        }
    }
    return list;
}

bool ProcessorManager::isLayoutClean(){
    return indexProcessor==-1;
}

void ProcessorManager::addProcessor(std::string name){
    QStandardItem* item = new QStandardItem(name.c_str());
    item->setCheckable(true);
    item->setSelectable(false);
    item->setCheckState(Qt::Checked);
    ProcessorModel->appendRow(item);
}

void ProcessorManager::clear()
{
    for(int i=0;i<ProcessorModel->rowCount();++i)
    {
        delete ProcessorModel->item(0);
    }
    ProcessorModel->clear();
}
