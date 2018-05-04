#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H
#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QStandardItemModel>
#include <QListView>
#include "datanodemanager.h"
#include "id.h"
#include "node.h"
class Item;
class Node;

/*
 * File: graphmanager.h
 * Type: header
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: manage graphs and relations to keep the two models coherent 
 */
 
class GraphManager : public QObject
{
    //Macro used to enable Qt signals and slots
    Q_OBJECT
    
private:
    //Field: radius of all nodes in the manager
    static const int Radius=15;
    
    //Field: model of the relation printed on the graph
    QStandardItemModel* RelationsModel;
    
    //Field: list of all the nodes printed on the graph
    QVector<Node*> Printed;
    
    //Field: model of the graph
    QGraphicsScene* Graph;
    
    //Field: map of all the relations and the items that represent the relations on the graph (used to hide a selected relation)
    QMap<QString,QGraphicsRectItem*> Relations;
    
public:

	// Description: GraphManager constructor 
    GraphManager();
    
	// Description: GraphManager destructor
    ~GraphManager();
    
    /*
     * Description: GraphManager copy constructor, made private to avoid copy costruction of the manager
     * @param const GraphManager& - GraphManager to be copied
     */
    GraphManager(const GraphManager&)=delete;

    /*
     * Description: returns the graph model to be linked with the view
     * @param QGraphicsView* view - Qt graphic view as view component (see Qt docs for more info)
     * @return void
     */
    void linkGraphModel(QGraphicsView* view);

    /*
     * Description: returns the relation model to be linked with the view
     * @param QListView* - Qt list view (see Qt docs for more info)
     * @return void
     */
    void linkRelationModel(QListView*);

    /*
     * Description: prints the relations which start from the given item, with the chosen name and the chosen color
     * @param const QString& - Qt string as relation name (see Qt docs for more info)
     * @param const Item* - initial item
     * @param const QColor& - Qt color as chosen color (see Qt docs for more info)
     * @return bool
     */
    bool printRelation(const QString&, const Item*, const QColor&);

    /*
     * Description: clears both models
     * @return void
     */
    void clear();
    
private:
    
    // Help methods to print relation 
     
    /*
     * Description: generates the relation item to use as parent of all nodes and arcs 
     * @param const QString& - Qt string as relation name (see Qt docs for more info) 
     * @param const QColor& - Qt color as relation color (see Qt docs for more info)
     * @return QGraphicsRectItem *
     */
    QGraphicsRectItem *generateRelation(const QString&,const QColor&);
    
    /*
     * Description: generates the item to be added into the relations model
     * @param const QString& - Qt string as relation name (see Qt docs for more info) 
     * @param const QColor & - Qt color as relation color (see Qt docs for more info)
     * @return QStandardItem *
     */
    QStandardItem *generateItem(const QString&, const QColor &);
    
    /*
     * Description: positions the node in the first column where it doesn't collide
     * @param Node& - node reference
     * @return void
     */
    void PositionNode(Node&);
    
    /*
     * Description: positions the node in the first row where it doesn't collide
     * @param Node& - node reference
     * @return void
     */
    void FixHeadPosition(Node&);
    
    /*
     * Description: check the relation of the first item in the list, the node that graphically represents the item
     * 				must be in Printed QVector, this method check the relations of the item and correctly
     *				add to the list of nodes that must be checked the next and the daughter of the item
     * @param QVector<const Item*>& - items vector
     * @param const QString &relation - Qt string as relation name (see Qt docs for more info) 
     * @param const QColor &color - Qt color as relation color (see Qt docs for more info)
     * @param QGraphicsItem *parentRelation - Qt graphics item as parent relation (see Qt docs for more info)
     * @return void
     */
    void checkRelations(QVector<const Item*>&, const QString &relation, const QColor &color, QGraphicsItem *parentRelation);

public slots:
    
    /*
     * Description: changes the visibility of the relations in the graph
     * @param QStandardItem * - Qt standard item as relation reference (see Qt docs for more info)
     * @return void
     */
    void changeRelationVisibility(QStandardItem *);
    
    /*
     * Description: notifies the selection/deselection of a item
     * @return void
     */
    void notifySelection();
    
    /*
     * Description: focuses the node given the relation and the path
     * @param const QString& - Qt string as relation name (see Qt docs for more info) 
     * @param const QString& - Qt string as path (see Qt docs for more info) 
     * @return void
     */
    void selectItem(const QString&,const QString&);
    
signals:
    
    /*
     * Description: signal launched when there is only one item focused and it's a node
     * @param const QString& - Qt string as relation name (see Qt docs for more info) 
     * @param const QString& - Qt string as relation ID (see Qt docs for more info) 
     * @param bool - focus/unfocus
     * @return void
     */
	void focusSignal(const QString&, const QString&, bool);
	
    /*
     * Description: clears the map and the UI
     * @return void
     */
	void cleardetails();
};

#endif // GRAPHMANAGER_H
