#include "arc.h"

#include <QVector2D>
#include <qpainter.h>
bool Arc::NodesColliding() const
{
    return MyPoints.length()<2*offsetFromPoint;
}

QPointF Arc::FixEnd()
{
    QVector2D directionVector(MyPoints.p1()-MyPoints.p2());
    directionVector.normalize();
    QVector2D orthogonal(directionVector.y(),-directionVector.x());
    arrowPoint1=MyPoints.p2()+directionVector.toPointF()*(offsetFromPoint+arrowWidth)+orthogonal.toPointF()*arrowWidth;
    arrowPoint2=MyPoints.p2()+directionVector.toPointF()*(offsetFromPoint+arrowWidth)-orthogonal.toPointF()*arrowWidth;
    return (MyPoints.p2()+directionVector.toPointF()*offsetFromPoint);

}


Arc::Arc(const int arrowWidth,const int offset,const QColor&color, QGraphicsItem *parent,bool dashed)
    :Line(offset,color,dashed,parent)
    ,arrowWidth(arrowWidth)
{
}


void Arc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(NodesColliding())return;
    painter->setBrush(QBrush(color));
    painter->setPen(Qt::black);
    QPolygonF head;
    head.clear();
    QPointF end=FixEnd();
    head<<end<<arrowPoint1<<arrowPoint2;
    painter->drawPolygon(head);
    painter->drawLine(QLineF(FixStart(),end));


}
