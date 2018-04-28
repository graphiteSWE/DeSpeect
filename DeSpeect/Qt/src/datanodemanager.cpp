#include "datanodemanager.h"


void DataNodeManager::linkToModel(QTableView *view)
{
    view->setModel(&nodeInfo);
}

void DataNodeManager::clear(){
    nodeInfo.clear();
}

void DataNodeManager::showNode(const std::map<std::string, std::string> &features)
{
    nodeInfo.clear();
    QStringList headers;
    int i=0;
    QStandardItem * temp = NULL;
    for(auto it=features.begin();it!=features.end();++it)
    {
        temp = new QStandardItem(it->second.c_str());
        temp->setBackground(QBrush(QColor(255,255,255)));
        headers.append(it->first.c_str());
        nodeInfo.setItem(i,temp);
        ++i;
    }
    nodeInfo.setVerticalHeaderLabels(headers);
    nodeInfo.setColumnCount(1);
}
