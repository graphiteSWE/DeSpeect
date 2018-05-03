#ifndef NODE_H
#define NODE_H
#include "id.h"
#include <QGraphicsObject>

/*
 * File: node.h
 * Type: header
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: models a node, which is the graphic representation of an item
 */
 
class Node:public QGraphicsObject
{
    //Macro used to enable Qt signals and slots
    Q_OBJECT
    
private:
    //Field: ID of the nodes the item defines - isEqual(ID.getRelation(),ID.getId())
    ID identifier;
    
    //Field: name of the item the node represents
    QString name;
    
    //Field: color of node
    QColor color;
    
    //Field: radius of node
    const int radius;
    
public:
    
    /*
     * Description: Node constructor
     * @param const QString& id - id of the node
     * @param const QString&rel - name of the corresponding relation
     * @param const QString& path - node path
     * @param const int x - x axis value
     * @param const int y - y axis value
     * @param const int radius - node radius
     * @param const QColor& color - node color
     * @param QGraphicsItem*parent - Qt graphic item as parent (see Qt docs for more info)
     */
    Node(const QString& id,const QString&rel,const QString& path, const int x, const int y, const int radius,const QColor& color, QGraphicsItem*parent);
    
    /*
     * Description: redefinition of the == operator (never used)
     * @param const Node& - node to be compared
     * @return bool 
     */
    bool operator==(const Node&)const;
    
    /*
     * Description: redefinition of the == operator (never used)
     * @param const ID identifier - ID to be compared
     * @return bool 
     */
    bool operator==(const ID identifier);
    
    /*
     * Description: defines how to draw a node
     * @param QPainter *painter - Qt painter (see Qt docs for more info)
     * @param const QStyleOptionGraphicsItem *option - Qt style options for graphic items  (see Qt docs for more info)
     * @param QWidget *widget - Qt widget as widget  (see Qt docs for more info)
     * @return void
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    
    /*
     * Description: defines the bounding rectangle of the node so that the item position is at its center
     * @return QRectF
     */
    QRectF boundingRect()const;
    
    /*
     * Description: slot that is called when an item moves or changes, used to call the signal of position changing of a node
	 *				to notify all item observing the node about its movement
	 * @param GraphicsItemChange change - indicates the graphic item changing status
	 * @param const QVariant &value - Qt variant as value (see Qt docs for more info)
     * @return QVariant
     */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    
    /*
     * Description: slot that is called when an item is released from mouse click, used to call the signal of position changing of a node
     *				to notify all the items observing the node about its movement (done because of frame time which could not actually notify the last movement)
	 * @param QGraphicsSceneMouseEvent *event Qt graphic scene mouse event as event (see Qt docs for more info)
     * @return void
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    
    /*
     * Description: returns the item ID 
     * @return const QString &
     */
    const QString &getId();
    
    /*
     * Description: returns the relation 
     * @return const QString &
     */
    const QString &getRelation();
    
signals:

    /*
     * Description: signals to notify if visibility has changed to observing items 
     * @param bool myVisibility - visibility status
     * @return void
     */
    void notifyVisibilityChange(bool myVisibility);
    
    /*
     * Description: signals to notify if position has changed to observing items 
     * @param const QPointF& - position status
     * @return void
     */
    void notifyPositionChange(const QPointF&);
    
public slots:
    
    /*
     * Description: slot to catch VisibilityChange of QGraphicsObject and call signal notifyVisibilityChange
     * @return void
     */
    void catchVisibilityChange();
};

#endif // NODE_H
