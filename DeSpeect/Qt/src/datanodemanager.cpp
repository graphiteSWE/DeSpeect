#include "datanodemanager.h"

/*
 * File: datanodemanager.cpp
 * Type: src
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: handles the map of data of the node to let the view show it
 */
 
//Description: DataNodeManager constructor 
DataNodeManager::DataNodeManager()
    :nodeInfo()
    ,nodeId("","")
{

}

/*
 * Description: links the model to a table view
 * @param QTableView * - Qt table view (see Qt docs for more info)
 * @return void 
 */
void DataNodeManager::linkToModel(QTableView *view)
{
    view->setModel(&nodeInfo);
}

/*
 * Description: clears the model
 * @return void
 */
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

/*
 * Description: print the node info
 * @param const std::map<std::string,std::string>& - map node to properties
 * @return void 
 */
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

/*
 * Description: returns the id of the selected node
 * @return const ID
 */
const ID DataNodeManager::getNodeId()
{
    return nodeId;
}
