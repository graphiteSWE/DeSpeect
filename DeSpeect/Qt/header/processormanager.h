#ifndef PROCESSORMANAGER_H
#define PROCESSORMANAGER_H

#include <QStandardItemModel>
#include <QStandardItem>
#include <QListView>

class ProcessorManager : public QObject
{
    Q_OBJECT
private:
    QStandardItemModel* ProcessorModel;
    int indexProcessor;

public:
    ProcessorManager();
    ~ProcessorManager();

    void linkProcessorModel(QListView* v);
    void clearLayoutProcessor();
    void lockUpdateItem();
    void unlockUpdateItem();
    void evidenceNextProcessor();
    void evidenceAllProcessor();
    bool isLayoutClean();

    std::list<std::string> getProcessorList();
    void addProcessor(std::string name);

    void clear();
};

#endif // PROCESSORMANAGER_H
