#ifndef NODE_H
#define NODE_H

#include "id.h"
#include <QGraphicsObject>
//node that is the graphic representation of an item
class Node:public QGraphicsObject
{
    Q_OBJECT
private:
    //id of the nodes the item defines isEqual(ID.getRelation(),ID.getId())
    ID identifier;
    //name of the item this node represent
    QString name;
    //color of node
    const QColor color;
    //radius of node
    const int radius;
public:
    //constructor
    Node(const QString& id,const QString&rel,const QString& path, const int x, const int y, const int radius,const QColor& color, QGraphicsItem*parent);
    //operator== (not used)
    bool operator==(const Node&)const;
    //define how to draw a node
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    //define the bounding rectangle of the node so that the item position is the center of the node
    QRectF boundingRect()const;
    //slot that is called when item move or change used to call the signal of position change of node
    //to notify all item watching the node the movement
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    //slot that is called when item is released from mouse click used to call the signal of position change of node
    //to notify all item watching the node the movement, done because of frame time could actually not notify the last
    //movement
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    //return the node Id and Relation
    const QString &getId();
    const QString &getRelation();
signals:
    //signals to notify if visibility is changed or if position is changed to listening items
    void notifyVisibilityChange(bool myVisibility);
    void notifyPositionChange(const QPointF&);
public slots:
    //slot to catch VisibilityChange of QGraphicsObject and call signal notifyVisibilityChange
    void catchVisibilityChange();
};

#endif // NODE_H
