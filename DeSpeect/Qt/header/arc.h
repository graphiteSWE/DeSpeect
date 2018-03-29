#ifndef ARC_H
#define ARC_H
#include "line.h"

#include <QGraphicsObject>
//Draw a line with an arrow on end point
class Arc:public Line
{
    Q_OBJECT
private:
    //the triangle base = 2*arrowWidth triangle heigth arrowWidth
    const int arrowWidth;
    //point needed to draw the arrow
    QPointF arrowPoint1;
    QPointF arrowPoint2;
    //fix the end point and arrow points when nodes move
    QPointF FixEnd();
public:
    //radius is needed to offset from the center
    Arc(const int arrowWidth, const int radius, const QColor& color, QGraphicsItem*parent=0, bool dashed=0);
public:
    //redefine paint function to draw the arrow of arc
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public slots:

};
#endif // ARC_H
