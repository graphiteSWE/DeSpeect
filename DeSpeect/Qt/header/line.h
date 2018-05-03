#ifndef LINE_H
#define LINE_H
#include <QGraphicsObject>

/*
 * File: line.h
 * Type: header
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: graphic line connecting two nodes
 */
 
class Line:public QGraphicsObject
{
    //Macro used to enable Qt signals and slots
    Q_OBJECT
    
private:

    //Field: used to show the line only if both its nodes are visible, if no parent relation is set
    int Visibility=1;

protected:
    
    //Field: radius of the node to offset from its center
    const int offsetFromPoint;
    
    //Field: color of empty space, draw line is still black
    QColor color;
    
    //Field:the start and ending point of the line
    QLineF MyPoints;
    
    //Field: true if the two nodes are colliding
    bool colliding;
    
    //Field: true if the line is dashed
    bool dashed;
    
    /*
     * Description: checks if the nodes are colliding
     * @return void
     */
    virtual void NodesColliding();
    
    /*
     * Description: fix the position of start and end to be the closest of the circle of the two nodes,
     * 				used when drawing not to draw from center to center of the nodes 
     * @return void
     */
    virtual QPointF FixStart();
    virtual QPointF FixEnd();
    
public:
    
    /*
     * Description: Line constructor
     * @param const int radius - radius to offset
     * @param const QColor& color - Qt color as line color (see Qt docs for more info)
     * @param bool dashed - indicates if the line is dashed
     * @param QGraphicsItem*parent - Qt graphics item as parent (see Qt docs for more info)
     */
    Line(const int radius, const QColor& color, bool dashed=0, QGraphicsItem*parent=0);
    
    //Description: Line destructor 
    virtual ~Line();
    
public slots:
    
    /*
     * Description: slots to update the position of the line, used to update position when the item is
     * 				connected to move the QPointF given at the center of the object
     * @param const QPointF& startPoint - Qt point as starting point (see Qt docs for more info)
     * @return void
     */
    void UpdateStartPoint(const QPointF& startPoint);
    void UpdateEndPoint(const QPointF& endPoint);
    
    /*
     * Description: set visibility to:
     * 				- 1  if the line must be drawn
     * 				- 0  if one node is hidden
     * 				- -1 if both
     * @param bool - indicates the visibility state
     * @return void
     */
    void changeVisibility(bool);
    
    // QGraphicsItem interface

public:
    
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};
#endif // LINE_H
