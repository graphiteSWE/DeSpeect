#ifndef LINE_H
#define LINE_H

#include <QGraphicsObject>
//graphic line between two nodes
class Line:public QGraphicsObject
{
    Q_OBJECT
private:
    //used to show the line only if both it's nodes are visible if no parent relation is set
    int Visibility=1;
protected:
    //radius of the node to offset from center of them
    const int offsetFromPoint;
    //color of empty space
    //draw line is still black
    const QColor color;
    //the start and ending point of the line
    QLineF MyPoints;
    //true if the two nodes are colliding
    bool colliding;
    //true if the line is dashed
    bool dashed;
    //check if the nodes are colliding
    virtual void NodesColliding();

    virtual ~Line();
    //fix the position of start and end to be the closest of the circle of the two nodes
    //used when drawing to not draw from center of node to center
    virtual QPointF FixStart();
    virtual QPointF FixEnd();
public:
    Line(const int radius,const QColor& color,bool dashed=0, QGraphicsItem*parent=0);
public slots:
    //slots to update the position of the line, used to update position when the item it's
    //connected to move the QPointF given are the center of the object
    void UpdateStartPoint(const QPointF& startPoint);
    void UpdateEndPoint(const QPointF& endPoint);
    //set Visibility to 1 is line must be drawn otherwise to 0 if one node is hidden to -1 if both
    //nodes are hidden
    void changeVisibility(bool);
    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};
#endif // LINE_H
