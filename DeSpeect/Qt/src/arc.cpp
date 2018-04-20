#include "arc.h"

#include <QVector2D>
#include <qpainter.h>

QPointF Arc::FixEnd()
{
    //calculate and normalize the directionVector of the arc
    QVector2D directionVector(MyPoints.p1()-MyPoints.p2());
    directionVector.normalize();
    //calculate the ortogonal normalized vector of the direction
    QVector2D orthogonal(directionVector.y(),-directionVector.x());
    //calculate and assign the two point of the arrow head
    arrowPoint1=MyPoints.p2()+directionVector.toPointF()*(offsetFromPoint+arrowWidth)+orthogonal.toPointF()*arrowWidth;
    arrowPoint2=MyPoints.p2()+directionVector.toPointF()*(offsetFromPoint+arrowWidth)-orthogonal.toPointF()*arrowWidth;
    //return the end point of the head of the arrow
    return (MyPoints.p2()+directionVector.toPointF()*offsetFromPoint);

}


Arc::Arc(const int arrowWidth,const int offset,const QColor&color, QGraphicsItem *parent,bool dashed)
    :Line(offset,color,dashed,parent)
    ,arrowWidth(arrowWidth)
{
    setZValue(0);
}


void Arc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //if nodes collide don t draw
    if(colliding)return;
    //set the painter brush that fills empty space inside the line of the right color
    painter->setBrush(QBrush(color));
    //set the pen that draw the outside line to black
    painter->setPen(QPen(painter->brush(),2));
    //create the arrow polygon to be drawn
    QPolygonF head;
    head.clear();
    QPointF end=FixEnd();
    head<<end<<arrowPoint1<<arrowPoint2;
    //draw the polygon and the line
    painter->drawLine(end,arrowPoint1);
    painter->drawLine(end,arrowPoint2);
    painter->drawLine(QLineF(FixStart(),end));


}
