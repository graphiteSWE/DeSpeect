#ifndef DATANODEMANAGER_H
#define DATANODEMANAGER_H
#include <QStandardItemModel>
#include <QStringListModel>
#include <QTableView>
#include "id.h"

/*
 * File: datanodemanager.h
 * Type: header
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: handles the map of data of the node to let the view show it
 */
 
class DataNodeManager:public QObject
{
    //Macro used to enable Qt signals and slots
    Q_OBJECT
    
private:
    //Field: models the item info view
    QStandardItemModel nodeInfo;
    
    //Field: node identifier
    ID nodeId;

public:
    //Description: DataNodeManager constructor 
    DataNodeManager();
    
    /*
     * Description: links the model to a table view
     * @param QTableView * - Qt table view (see Qt docs for more info)
     * @return void 
     */
    void linkToModel(QTableView *);
    
    /*
     * Description: print the node info
     * @param const std::map<std::string,std::string>& - map node to properties
     * @return void 
     */
    void showNode(const std::map<std::string,std::string>&);
    
    /*
     * Description: returns the id of the selected node
     * @return const ID
     */
    const ID getNodeId();

public slots:
    
    /*
     * Description: clears the model
     * @return void
     */
    void clear();

};
#endif // DATANODEMANAGER_H
