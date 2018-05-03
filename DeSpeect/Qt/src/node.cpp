#include "node.h"
#include <QFocusEvent>
#include <QPainter>
#include <QGraphicsScene>

/*
 * File: node.cpp
 * Type: src
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: models a node, which is the graphic representation of an item
 */

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
Node::Node(const QString& id,const QString& rel,const QString& path, const int x, const int y, const int radius,const QColor& color, QGraphicsItem*parent)
   :QGraphicsObject(parent)
   ,color(color)
   ,identifier(id,rel)
   ,name(path)
   ,radius(radius)
{
    //link QGraphicsObject signal to the slot
    connect(this,SIGNAL(visibleChanged()),this,SLOT(catchVisibilityChange()));
    //allow item movement selection and allow item notification to scene Model
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    //enable itemChange slot
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    //set the item position
    setX(x);
    setY(y);
    //so that is over arrow but not over lines
    setZValue(1);
}

/*
 * Description: redefinition of the == operator (never used)
 * @param const Node& - node to be compared
 * @return bool 
 */
bool Node::operator==(const Node &other) const
{
    return identifier==other.identifier;
}

/*
 * Description: redefinition of the == operator (never used)
 * @param const ID identifier - ID to be compared
 * @return bool 
 */
bool Node::operator==(const ID identifier)
{
    return identifier==this->identifier;
}

/*
 * Description: defines how to draw a node
 * @param QPainter *painter - Qt painter (see Qt docs for more info)
 * @param const QStyleOptionGraphicsItem *option - Qt style options for graphic items  (see Qt docs for more info)
 * @param QWidget *widget - Qt widget as widget  (see Qt docs for more info)
 * @return void
 */
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //default pen and brush
    QPen myPen = QPen(Qt::black);

    color.setAlphaF(0.5);
    QBrush Brush=QBrush(color);
    //when selected
    if(isSelected())
    {

        QColor tempC=color;
        tempC.setAlphaF(1);
        myPen.setWidth(5);
        Brush.setColor(tempC);
        myPen.setStyle(Qt::SolidLine);
    }//only when focused
    else if(hasFocus())
    {
        QColor tempC=color;
        tempC.setAlphaF(1);
        myPen.setColor(tempC);
        Brush.setColor(color);
        myPen.setWidth(5);

    }

    //set the brush and color
    painter->setBrush(Brush);
    painter->setPen(myPen);
    //draw and ellipse inside the bounding rect of this item
    QRectF t=boundingRect();
    //bounding rect is a square so ellipse is a circle
    painter->drawEllipse(t);
    //draw the name info at bottom of item
    t.setBottom(t.top());
    t.setTop(t.top()-15);
    painter->drawText(t,Qt::AlignCenter|Qt::TextDontClip,name);

}

/*
 * Description: defines the bounding rectangle of the node so that the item position is at its center
 * @return QRectF
 */
QRectF Node::boundingRect() const
{
    //draw the rect so that it's position is in the middle of rect
    return QRectF(-radius,-radius,radius*2,radius*2);
}

/*
 * Description: slot that is called when an item moves or changes, used to call the signal of position changing of a node
 *				to notify all item observing the node about its movement
 * @param GraphicsItemChange change - indicates the graphic item changing status
 * @param const QVariant &value - Qt variant as value (see Qt docs for more info)
 * @return QVariant
 */
QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    //if changed position notify all my arcs my movement
    if (change == ItemPositionChange&&scene()) {
        notifyPositionChange(pos());
    }
    //if selected for search reason set own flag
    return QGraphicsItem::itemChange(change,value);
}

/*
 * Description: slot that is called when an item is released from mouse click, used to call the signal of position changing of a node
 *				to notify all the items observing the node about its movement (done because of frame time which could not actually notify the last movement)
 * @param QGraphicsSceneMouseEvent *event Qt graphic scene mouse event as event (see Qt docs for more info)
 * @return void
 */
void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //call super
    QGraphicsItem::mouseReleaseEvent(event);
    //notify all arcs my last position
    notifyPositionChange(pos());
}

/*
 * Description: returns the item ID 
 * @return const QString &
 */
const QString& Node::getId()
{
    return identifier.getID();
}

/*
 * Description: returns the relation 
 * @return const QString &
 */
const QString &Node::getRelation()
{
    return identifier.getRelation();
}

/*
 * Description: slot to catch VisibilityChange of QGraphicsObject and call signal notifyVisibilityChange
 * @return void
 */
void Node::catchVisibilityChange()
{
    notifyVisibilityChange(isVisible());
}
