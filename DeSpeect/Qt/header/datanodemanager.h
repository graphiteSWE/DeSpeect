#ifndef DATANODEMANAGER_H
#define DATANODEMANAGER_H

#include <QStandardItemModel>
#include <QStringListModel>
#include <QTableView>

class DataNodeManager
{
private:
    std::string identifierPath;
    std::string identifierRelation;
    QStandardItemModel nodeInfo;
public:
    void linkToModel(QTableView *);
    void clear();
    void showNode(const std::map<std::string,std::string>&);
};
#endif // DATANODEMANAGER_H
