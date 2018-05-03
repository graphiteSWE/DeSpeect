#include "datanodemanager.h"

//link the manager model to the view
DataNodeManager::DataNodeManager()
    :nodeInfo()
    ,nodeId("","")
{

}

void DataNodeManager::linkToModel(QTableView *view)
{
    view->setModel(&nodeInfo);
}

//clear all item
void DataNodeManager::clear(){
    //for each item in the model
    for(int i=0;i<nodeInfo.rowCount();++i)
    {
        //delete the item
        delete nodeInfo.item(i);
    }
    //clear the model
    nodeInfo.clear();
    nodeId=ID("", "");
}
//clear all node information
void DataNodeManager::showNode(const std::map<std::string, std::string> &features)
{
    //clear the model
    nodeInfo.clear();
    auto it=features.find("DespeectItemIDPath");
    QString path="";
    QString relation="";
    if(it!=features.end())
    {
        path=it->second.c_str();
    }
    it=features.find("DespeectItemIDRelation");
    if(it!=features.end())
    {
        relation=it->second.c_str();
    }

    nodeId=ID(path,relation);
    //list of all the headers
    //gonna be filled with map key
    QStringList headers;
    int i=0;
    //temp item to store item while adding to the model
    QStandardItem * temp = NULL;
    for(auto it=features.begin();it!=features.end();++it)
    {
        //create the item with the value of the map
        temp = new QStandardItem(it->second.c_str());
        //set the backgroud color to white this is done because otherwise would be black
        temp->setBackground(QBrush(QColor(255,255,255)));
        //append to the list the key of the map
        headers.append(it->first.c_str());
        //add the item to the list
        nodeInfo.setItem(i,temp);
        ++i;
    }
    //set the labels to the key of the map
    nodeInfo.setVerticalHeaderLabels(headers);
    //tell that there is only one columns
    nodeInfo.setColumnCount(1);
}

const ID DataNodeManager::getNodeId()
{
    return nodeId;
}
