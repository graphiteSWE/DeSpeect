#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QStandardItemModel>
#include <QListView>
#include "id.h"
#include "node.h"
class Item;
class Node;
//manage graphs and relation to keep coherent the two models
class GraphManager : public QObject
{
    Q_OBJECT
private:
    //radius of all nodes in the manager
    static const int Radius=15;
    //model of relation printed on graph
    QStandardItemModel* RelationsModel;
    //list of all nodes printed on graph
    QVector<Node*> Printed;
    //model of graph
    QGraphicsScene* Graph;
    //Map of all relation and the item that represent the relation on graph
    //used to hide a relation
    QMap<QString,QGraphicsRectItem*> Relations;
    //to avoid copy costruction of the manager
    GraphManager(const GraphManager&);
public:

    GraphManager();
    ~GraphManager();
    //return the model to be linked with the view(could be better do the opposite)
    void linkGraphModel(QGraphicsView* view);

    //return the model to be linked with the view(could be better do the opposite)
    void linkRelationModel(QListView*);

    //print the relations that start from the item,with the chosen name and the chosen color
    bool printRelation(const QString&, const Item*, const QColor&);

    //clear both models
    void clear();
private:
    //help methods to print relation
    //generate the relation item to use as parent of all nodes and arcs
    QGraphicsRectItem *generateRelation(const QString&,const QColor&);
    //generate the item to add into the relations model
    QStandardItem *generateItem(const QString&, const QColor &);
    //position the node in the first column where it doesn t collide
    void PositionNode(Node&);
    //position the node in the first row where it doesn t collide
    void FixHeadPosition(Node&);
    //check the relation of the first item in the list,the node that graphically represent the item
    //must be in Printed QVector, this method check the relations of the item and correctly
    //add to the list of nodes that must be checked the next and the daughter of the item
    void checkRelations(QVector<const Item*>&, const QString &relation, const QColor &color, QGraphicsItem *parentRelation);
public slots:
    //change the visibility of the relations in the graph
    void changeRelationVisibility(QStandardItem *);
//signals:
//        void focusSignal(const ID&, const QString&);
};

#endif // GRAPHMANAGER_H
