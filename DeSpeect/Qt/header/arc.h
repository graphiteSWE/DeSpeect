#ifndef ARC_H
#define ARC_H
#include "line.h"
#include <QGraphicsObject>

/*
 * File: arc.h
 * Type: header
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: draws a line with an arrow on its end point
 */
 
class Arc:public Line
{
    //Macro used to enable Qt signals and slots
    Q_OBJECT
    
private:
    
    /* 
     * Field: arrow width, note that:
     * 		  - triangle base   = 2*arrowWidth
     * 		  - triangle heigth = arrowWidth
     */
    const int arrowWidth;
    
    //Field: indicates if the arrow head is filled
    const bool isfilled;
    
    //Field: indicates the type of the arrow
    const bool type;
    
    //Fields: points needed to draw the arrow
    QPointF arrowPoint1;
    QPointF arrowPoint2;
    
    //Field: fix the end point and arrow points when nodes move
    QPointF FixEnd();

public:

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
    Arc(const int arrowWidth, const int radius, const QColor& color, bool prev_next=1, bool filled=1, QGraphicsItem*parent=0, bool dashed=0);

public:
    
    /*
     * Description: redefines the paint function to draw the arrow of the arc
     * @param QPainter *painter - Qt painter (see Qt docs for more info)
     * @param const QStyleOptionGraphicsItem *option - Qt style options for the graphic item (see Qt docs for more info)
     * @param const QWidget *widget - Qt widget (see Qt docs for more info)
     * @return void
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public slots:

};
#endif // ARC_H
