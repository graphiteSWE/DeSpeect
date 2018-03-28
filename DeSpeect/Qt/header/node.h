#ifndef NODE_H
#define NODE_H

#include "id.h"
#include <QGraphicsObject>
class Node:public QGraphicsObject
{
    Q_OBJECT
private:
    ID identifier;
    QString name;
    const QColor color;
    const int radius;
public:
    Node(const QString& id,const QString&rel,const QString& path, const int x, const int y, const int radius,const QColor& color, QGraphicsItem*parent);
    bool operator==(const Node&)const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect()const;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    const QString &getId();
    const QString &getRelation();
signals:
    void notifyVisibilityChange(bool myVisibility);
    void notifyPositionChange(const QPointF&);
public slots:
    void catchVisibilityChange();
};

#endif // NODE_H
