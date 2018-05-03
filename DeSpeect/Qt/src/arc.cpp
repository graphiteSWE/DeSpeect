#include "arc.h"
#include <QVector2D>
#include <qpainter.h>

/*
 * File: arc.cpp
 * Type: src
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: draws a line with an arrow on its end point
 */
 
/*
 * Description: fix the end point and arrow points when nodes move
 * @return QPointF
 */
QPointF Arc::FixEnd()
{
    //calculate and normalize the directionVector of the arc
    QVector2D directionVector(MyPoints.p1()-MyPoints.p2());
    directionVector.normalize();
    //calculate the ortogonal normalized vector of the direction
    QVector2D orthogonal(directionVector.y(),-directionVector.x());
    //calculate and assign the two point of the arrow head
    arrowPoint1=MyPoints.p2()+directionVector.toPointF()*(offsetFromPoint+arrowWidth)+orthogonal.toPointF()*arrowWidth*0.66;
    arrowPoint2=MyPoints.p2()+directionVector.toPointF()*(offsetFromPoint+arrowWidth)-orthogonal.toPointF()*arrowWidth*0.66;
    //return the end point of the head of the arrow
    return (MyPoints.p2()+directionVector.toPointF()*offsetFromPoint);

}



/*
 * Description: Arc constructor
 * @param const int arrowWidth - arrow width 
 * @param const int radius - radius of the pointed nodes, it is needed to offset from the center
 * @param const QColor& color - Qt color as the arc color (see Qt docs for more info)
 * @param bool prev_next - indicates the kind of arc
 * @param bool filled - indicates if the arrow head is filled
 * @param QGraphicsItem* parent - Qt graphic item  (see Qt docs for more info)
 * @param bool dashed - indicates if the arc is dashed
 */
Arc::Arc(const int arrowWidth,const int offset,const QColor&color,bool prev_next,bool filled, QGraphicsItem *parent,bool dashed)
    :Line(offset,color,dashed,parent)
    ,type(prev_next)
    ,isfilled(filled)
    ,arrowWidth(arrowWidth)
{
    //set zvalue so that all node have priority over arcs
    setZValue(0);
}

/*
 * Description: redefines the paint function to draw the arrow of the arc
 * @param QPainter *painter - Qt painter (see Qt docs for more info)
 * @param const QStyleOptionGraphicsItem *option - Qt style options for the graphic item (see Qt docs for more info)
 * @param const QWidget *widget - Qt widget (see Qt docs for more info)
 * @return void
 */
void Arc::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //if nodes collide don t draw
    if(colliding)return;
    //set the painter brush that fills empty space inside the line of the right color
    if(isfilled){
    painter->setBrush(QBrush(color));
    }
    //set the pen that draw the outside line
    QPen mypen(color);
    mypen.setWidthF(1.5F);
    painter->setPen(mypen);
    QVector2D directionVector(MyPoints.p1()-MyPoints.p2());
    directionVector.normalize();
    //create the arrow polygon to be drawn

    QPolygonF head;
    head.clear();
    QPointF end=FixEnd();
    if(type){
    head<<end<<arrowPoint1<<end+directionVector.toPointF()*arrowWidth/2<<arrowPoint2<<end;
    }
    else
    {
        head<<end<<arrowPoint1<<arrowPoint2<<end;
    }
    //draw the polygon and the line
    painter->drawPolygon(head);

    mypen.setWidth(2);
    painter->setPen(mypen);
    Line::paint(painter,option,widget);
}
