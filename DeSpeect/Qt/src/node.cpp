#include "node.h"

#include <QPainter>
#include "iostream"
Node::Node(const QString& id,const QString& rel,const QString& path, const int x, const int y, const int radius,const QColor& color, QGraphicsItem*parent)
   :QGraphicsObject(parent)
   ,color(color)
   ,identifier(id,rel)
   ,name(path)
   ,radius(radius)
{
    connect(this,SIGNAL(visibleChanged()),this,SLOT(catchVisibilityChange()));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setX(x);
    setY(y);
}

bool Node::operator==(const Node &other) const
{
    return identifier==other.identifier;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QPen myPen = QPen(Qt::black);
    QBrush Brush = QBrush(color);
    if(isSelected()){

        //painter->setBrush(Qt::yellow);
        myPen.setWidth(5);
        }

    painter->setBrush(color);
    painter->setPen(myPen);
    //disegna il cerchio
    painter->drawEllipse(boundingRect());
    //disegna l'id al centro
    painter->drawText(-radius,+radius*2,name);

}

QRectF Node::boundingRect() const
{
    return QRectF(-radius,-radius,radius*2,radius*2);
}
QVariant Node::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange&&scene()) {
        //dico ai miei archi che mi sono spostato
        notifyPositionChange(pos());
    }
    return QGraphicsItem::itemChange(change,value);
}

void Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    notifyPositionChange(pos());
}

const QString& Node::getId()
{
    return identifier.getID();
}

const QString &Node::getRelation()
{
    return identifier.getRelation();
}

void Node::catchVisibilityChange()
{
    notifyVisibilityChange(isVisible());
}
