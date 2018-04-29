#ifndef DATANODEMANAGER_H
#define DATANODEMANAGER_H

#include <QStandardItemModel>
#include <QStringListModel>
#include <QTableView>
//this class handle the map of data of the node to
//let the view show it
class DataNodeManager
{
private:
    //model the item info view
    QStandardItemModel nodeInfo;
public:
    //link the model to a table view
    void linkToModel(QTableView *);
    //clear the model
    void clear();
    //print the node info
    void showNode(const std::map<std::string,std::string>&);
};
#endif // DATANODEMANAGER_H
