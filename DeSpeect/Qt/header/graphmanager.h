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
class GraphManager:public QObject
{
    Q_OBJECT
private:
    QStandardItemModel* RelationsModel;
    QVector<Node*> Printed;
    QGraphicsScene* Graph;
    QMap<QString,QGraphicsRectItem*> Relations;
    GraphManager(const GraphManager&);
public:
    const int Radius=15;
    GraphManager();
    ~GraphManager();
    QGraphicsScene *getGraphModel() const;
    QAbstractItemModel *getRelationModel()const;
    bool printRelation(const QString&, const Item*, const QColor&);
        void clear();
private:
        QGraphicsRectItem *generateRelation(const QString&,const QColor&);
        QStandardItem *generateItem(const QString&, const QColor &);
        void PositionNode(Node&);
        void FixHeadPosition(Node&);
        void checkRelations(QVector<const Item*>&, const QString &relation, const QColor &color, QGraphicsItem *parentRelation);
public slots:
        void changeRelationVisibility(QStandardItem *);
//signals:
//        void focusSignal(const ID&, const QString&);
};

#endif // GRAPHMANAGER_H
