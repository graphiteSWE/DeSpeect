#ifndef DATANODEMANAGER_H
#define DATANODEMANAGER_H

#include <QStandardItemModel>
#include <QStringListModel>
#include <QTableView>
#include "id.h"
//this class handle the map of data of the node to
//let the view show it
class DataNodeManager:public QObject
{
    Q_OBJECT
private:
    //model the item info view
    QStandardItemModel nodeInfo;
    ID nodeId;
public:
    //constructor
    DataNodeManager();
    //link the model to a table view
    void linkToModel(QTableView *);
    //print the node info
    void showNode(const std::map<std::string,std::string>&);
    //return the id of the selected node
    const ID getNodeId();

public slots:
    //clear the model
    void clear();

};
#endif // DATANODEMANAGER_H
