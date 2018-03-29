#include "node.h"

#include <QPainter>

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
    //enable itemChange slot
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    //set the item position
    setX(x);
    setY(y);
    //so that is over arrow but not over lines
    setZValue(1);
}
//never used
bool Node::operator==(const Node &other) const
{
    return identifier==other.identifier;
}
//paint the circle of node
void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //default pen and brush
    QPen myPen = QPen(Qt::black);
    QBrush Brush = QBrush(color);
    if(isSelected())
    {
        //if item is selected draw bigger perimeter line
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

QRectF Node::boundingRect() const
{
    //draw the rect so that it's position is in the middle of rect
    return QRectF(-radius,-radius,radius*2,radius*2);
}
//virtual method called when item change
QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    //if changed position notify all my arcs my movement
    if (change == ItemPositionChange&&scene()) {
        notifyPositionChange(pos());
    }
    return QGraphicsItem::itemChange(change,value);
}

//method called when mouse is released from item
void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //call super
    QGraphicsItem::mouseReleaseEvent(event);
    //notify all arcs my last position
    notifyPositionChange(pos());
}
//getter
const QString& Node::getId()
{
    return identifier.getID();
}
//getter
const QString &Node::getRelation()
{
    return identifier.getRelation();
}
//catch when I change visibility and signals to listener
void Node::catchVisibilityChange()
{
    notifyVisibilityChange(isVisible());
}
