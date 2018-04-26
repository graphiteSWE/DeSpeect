#include "datanodemanager.h"


void DataNodeManager::linkToModel(QTableView *view)
{
    view->setModel(&nodeInfo);
}

void DataNodeManager::showNode(const std::map<std::string, std::string> &features)
{
    nodeInfo.clear();
    QStringList headers;
    int i=0;
    for(auto it=features.begin();it!=features.end();++it)
    {
        headers.append(it->first.c_str());
        nodeInfo.setItem(i,new QStandardItem(it->second.c_str()));
        ++i;
    }
    nodeInfo.setVerticalHeaderLabels(headers);
    nodeInfo.setColumnCount(1);
}
