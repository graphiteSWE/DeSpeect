#ifndef ARC_H
#define ARC_H
#include "line.h"

#include <QGraphicsObject>
class Arc:public Line
{
    Q_OBJECT
private:
    const int arrowWidth;
    QPointF arrowPoint1;
    QPointF arrowPoint2;
    bool NodesColliding()const;
    QPointF FixEnd();
public:
    Arc(const int arrowWidth, const int radius, const QColor& color, QGraphicsItem*parent=0, bool dashed=0);
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public slots:

};
#endif // ARC_H
