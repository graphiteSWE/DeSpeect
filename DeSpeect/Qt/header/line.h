#ifndef LINE_H
#define LINE_H

#include <QGraphicsObject>
//
class Line:public QGraphicsObject
{
    Q_OBJECT
private:
    int Visibility=1;
protected:
    const int offsetFromPoint;
    const QColor color;
    QLineF MyPoints;
    bool colliding;
    bool dashed;

    bool NodesColliding()const;
    virtual ~Line();
    virtual QPointF FixStart();
    virtual QPointF FixEnd();
public:
    Line(const int radius,const QColor& color,bool dashed=0, QGraphicsItem*parent=0);
public slots:
    void UpdateStartPoint(const QPointF& startPoint);
    void UpdateEndPoint(const QPointF& endPoint);
    void changeVisibility(bool);
    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};
#endif // LINE_H
