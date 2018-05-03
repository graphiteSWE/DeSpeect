#include "line.h"
#include <QVector2D>
#include <qpainter.h>

/*
 * File: line.h
 * Type: header
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: graphic line connecting two nodes
 */

/*
 * Description: checks if the nodes are colliding
 * @return void
 */
void Line::NodesColliding()
{
    qreal x=MyPoints.x1()-MyPoints.x2();
    qreal y=MyPoints.y1()-MyPoints.y2();
    colliding=x*x+y*y<=(2*offsetFromPoint)*(2*offsetFromPoint);

    }

//Description: Line destructor 
Line::~Line()
{
}

/*
 * Description: fix the position of start and end to be the closest of the circle of the two nodes,
 * 				used when drawing not to draw from center to center of the nodes 
 * @return void
 */
QPointF Line::FixStart()
{
    //calculate direction vector and normalize it
    QVector2D directionVector(MyPoints.p1()-MyPoints.p2());
    directionVector.normalize();
    //return the fixed point of line
    return MyPoints.p1()-directionVector.toPointF()*offsetFromPoint;
}

QPointF Line::FixEnd()
{
    //calculate direction vector and normalize it
    QVector2D directionVector(MyPoints.p1()-MyPoints.p2());
    directionVector.normalize();
    //return the fixed point of line
    return (MyPoints.p2()+directionVector.toPointF()*offsetFromPoint);
}

/*
 * Description: Line constructor
 * @param const int radius - radius to offset
 * @param const QColor& color - Qt color as line color (see Qt docs for more info)
 * @param bool dashed - indicates if the line is dashed
 * @param QGraphicsItem*parent - Qt graphics item as parent (see Qt docs for more info)
 */
Line::Line(const int offset, const QColor&color, bool dashed, QGraphicsItem *parent)
    :QGraphicsObject(parent)
    ,offsetFromPoint(offset)
    ,color(color)
    ,colliding(true)
    ,dashed(dashed)
{
    this->color.setAlphaF(0.5);
}

/*
 * Description: slots to update the position of the line, used to update position when the item is
 * 				connected to move the QPointF given at the center of the object
 * @param const QPointF& startPoint - Qt point as starting point (see Qt docs for more info)
 * @return void
 */
void Line::UpdateStartPoint(const QPointF& startPoint)
{
    //update start point to new point
    MyPoints.setP1(startPoint);
    //check if the two nodes it connects collide
    NodesColliding();
}

void Line::UpdateEndPoint(const QPointF &endPoint)
{
    //update last point to new endpoint
    MyPoints.setP2(endPoint);
    //check if the two nodes it connect collide
    NodesColliding();
}

/*
 * Description: set visibility to:
 * 				- 1  if the line must be drawn
 * 				- 0  if one node is hidden
 * 				- -1 if both
 * @param bool - indicates the visibility state
 * @return void
 */
void Line::changeVisibility(bool vis)
{
    //if has parent visibility depends on parent
    if(parentItem()==NULL){
        //vis is 1 if item changed to visible 0 otherwise
        //check if the line should be visible
        Visibility-=vis?-1:1;
        //if it should set it visible otherwise not visible
        if(Visibility==1)
            setVisible(true);
        else
            setVisible(false);
    }
}

// QGraphicsItem interface

QRectF Line::boundingRect() const
{

    return QRectF(MyPoints.p1(),MyPoints.p2()).normalized();
}

void Line::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //if nodes are colliding don t draw
    if(colliding)return;
    //if line is dashed set the pen
    //to dashed
    QPen mypen(color);
    if(dashed)
    {   
        color.setAlphaF(1);
        mypen.setStyle(Qt::DashLine);
    }
    painter->setPen(mypen);
    //draw the line
    painter->drawLine(QLineF(FixStart(),FixEnd()));
}
