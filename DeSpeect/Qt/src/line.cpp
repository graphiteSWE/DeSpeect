#include "line.h"
#include <QVector2D>
#include <qpainter.h>

//calculate if the two nodes are colliding
void Line::NodesColliding()
{
    qreal x=MyPoints.x1()-MyPoints.x2();
    qreal y=MyPoints.y1()-MyPoints.y2();
    colliding=x*x+y*y<=(2*offsetFromPoint)*(2*offsetFromPoint);

    }

//virtual destructor
Line::~Line()
{
}

//fix the starting point
QPointF Line::FixStart()
{
    //calculate direction vector and normalize it
    QVector2D directionVector(MyPoints.p1()-MyPoints.p2());
    directionVector.normalize();
    //return the fixed point of line
    return MyPoints.p1()-directionVector.toPointF()*offsetFromPoint;
}

//fix the end point
QPointF Line::FixEnd()
{
    //calculate direction vector and normalize it
    QVector2D directionVector(MyPoints.p1()-MyPoints.p2());
    directionVector.normalize();
    //return the fixed point of line
    return (MyPoints.p2()+directionVector.toPointF()*offsetFromPoint);
}


Line::Line(const int offset, const QColor&color, bool dashed, QGraphicsItem *parent)
    :QGraphicsObject(parent)
    ,offsetFromPoint(offset)
    ,color(color)
    ,colliding(true)
    ,dashed(dashed)
{
}
//slot to update the line start point
void Line::UpdateStartPoint(const QPointF& startPoint)
{
    MyPoints.setP1(startPoint);
    NodesColliding();
}
//slot to update the line end point
void Line::UpdateEndPoint(const QPointF &endPoint)
{
    MyPoints.setP2(endPoint);
    NodesColliding();
}
//slot to change visibility
void Line::changeVisibility(bool vis)
{
    //if has parent visibility depends on parent
    if(parentItem()==NULL){
        //vis is 1 if item changed to visible 0 otherwise
        //math
        Visibility-=(1-2*vis);
        if(Visibility==1)
            setVisible(true);
        else
            setVisible(false);
    }
}

//rect used for drawing
QRectF Line::boundingRect() const
{

    return QRectF(MyPoints.p1(),MyPoints.p2()).normalized();
}

//how draw the line
void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //if nodes are colliding don t draw
    if(colliding)return;
    //if line is dashed set the pen
    if(dashed)
        painter->setPen(Qt::DashLine);
    //draw the line
    painter->drawLine(QLineF(FixStart(),FixEnd()));


}
