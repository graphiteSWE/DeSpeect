#include "line.h"
#include <QVector2D>
#include <qpainter.h>
bool Line::NodesColliding() const
{
    qreal x=MyPoints.x1()-MyPoints.x2();
    qreal y=MyPoints.y1()-MyPoints.y2();
    return x*x+y*y<=(2*offsetFromPoint)*(2*offsetFromPoint);

    }

Line::~Line()
{
}

QPointF Line::FixStart()
{
    QVector2D directionVector(MyPoints.p1()-MyPoints.p2());
    directionVector.normalize();
    return MyPoints.p1()-directionVector.toPointF()*offsetFromPoint;
}

QPointF Line::FixEnd()
{
    QVector2D directionVector(MyPoints.p1()-MyPoints.p2());
    directionVector.normalize();
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

void Line::UpdateStartPoint(const QPointF& startPoint)
{
    MyPoints.setP1(startPoint);
}

void Line::UpdateEndPoint(const QPointF &endPoint)
{
    MyPoints.setP2(endPoint);
}

void Line::changeVisibility(bool vis)
{
    if(parentItem()==NULL)
    Visibility+=-(1-2*vis);
    if(Visibility==1)
        setVisible(true);
    else
        setVisible(false);
}


QRectF Line::boundingRect() const
{

    return QRectF(MyPoints.p1(),MyPoints.p2()).normalized();
}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(NodesColliding())return;
    if(dashed)
        painter->setPen(Qt::DashLine);
    else
        painter->setPen(Qt::SolidLine);
    painter->drawLine(QLineF(FixStart(),FixEnd()));


}
