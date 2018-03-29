#include "graphmanager.h"

#include <QGraphicsItemGroup>
#include <QGraphicsView>
#include <arc.h>
#include <item.h>
#include <node.h>

GraphManager::GraphManager(const GraphManager &)
{
}

GraphManager::GraphManager()
    :Graph(new QGraphicsScene())
    ,Relations()
    ,RelationsModel(new QStandardItemModel())
{
    connect(RelationsModel,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(changeRelationVisibility(QStandardItem*)));

}

GraphManager::~GraphManager()
{
    Graph->clear();
    Relations.clear();
    delete Graph;

}

QGraphicsScene *GraphManager::getGraphModel()const
{
    return Graph;
}

QAbstractItemModel *GraphManager::getRelationModel()const
{
    return RelationsModel;
}

bool GraphManager::printRelation(const QString &id, const Item *SpeectNode, const QColor &Color)
{
    QVector<const Item*>ToBeChecked;

    QGraphicsRectItem* parentRelation=generateRelation(id,Color);
    if(parentRelation!=NULL){
    Graph->addItem(parentRelation);
    ToBeChecked.push_back(SpeectNode);
    Node* t=new Node(QString(SpeectNode->getId().c_str()),id,QString(SpeectNode->getName().c_str()),0,0,Radius,Color,parentRelation);
    Printed.push_back(t);
    FixHeadPosition(*t);
    while(!ToBeChecked.isEmpty())
    {
        checkRelations(ToBeChecked,id,Color,parentRelation);
    }
    }
}

QGraphicsRectItem *GraphManager::generateRelation(const QString &id, const QColor &color)
{
    if(!Relations.contains(id)) {
        RelationsModel->appendRow(generateItem(id,color));
        QGraphicsRectItem* t=new QGraphicsRectItem();
        Relations.insert(id,t);
        return t;
     }
    return NULL;

}

QStandardItem *GraphManager::generateItem(const QString &id,const QColor&color)
{
    QStandardItem* item=new QStandardItem(id);
    item->setBackground(QBrush(color));
    item->setCheckable(true);
    item->setEditable(false);
    item->setCheckState(Qt::Checked);
    item->setSelectable(false);
    return item;
}
#include "iostream"
void GraphManager::PositionNode(Node &me)
{
    while(me.collidingItems().size()>1){
        me.setX(me.x()+(4*Radius));
    }
}

void GraphManager::FixHeadPosition(Node &me)
{
    while(me.collidingItems().size()>1){
        me.setY(me.y()+(4*Radius));
    }
}
#include "iostream"
void GraphManager::checkRelations(QVector<const Item*> &tbc, const QString& relation, const QColor& color, QGraphicsItem *parentRelation)
{
    const Item* toBeChecked=tbc.takeFirst();
    bool hasFather=toBeChecked->hasFather();
    bool hasDaughter=toBeChecked->hasDaughter();
    bool hasNext=toBeChecked->hasNext();
    bool hasPrev=toBeChecked->hasPrev();
    const Item father=toBeChecked->father()
            ,daughter=toBeChecked->daughter()
            ,next=toBeChecked->next()
            ,prev=toBeChecked->prev();
    Node* me=NULL;;
    foreach(Node* node,Printed)
    {
       if(toBeChecked->IsEqual(node->getRelation().toStdString(),node->getId().toStdString())==1){
            me=node;
       }
    }
    foreach(Node* node,Printed)
        {


        if(toBeChecked->IsEqual(node->getRelation().toStdString(),node->getId().toStdString())==2)
        {
            Line* a=new Line(Radius,color,1,NULL);
            connect(node,SIGNAL(notifyVisibilityChange(bool)),a,SLOT(changeVisibility(bool)));
            connect(node,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateEndPoint(QPointF)));
            connect(me,SIGNAL(notifyVisibilityChange(bool)),a,SLOT(changeVisibility(bool)));
            connect(me,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateStartPoint(QPointF)));
            Graph->addItem(a);
            a->UpdateStartPoint(me->pos());
            a->UpdateEndPoint(node->pos());
        }
        if(hasFather&&father.IsEqual(node->getRelation().toStdString(),node->getId().toStdString())==1)
        {
            Arc* a=new Arc(10,Radius,color,parentRelation,true);
            connect(node,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateEndPoint(QPointF)));
            connect(me,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateStartPoint(QPointF)));
            hasFather=false;

            a->UpdateEndPoint(node->pos());

        }
/*

        if(hasDaughter&&daughter.IsEqual(node->getRelation().toStdString(),node->getId().toStdString())==1)
        {
            Arc* a=new Arc(10,Radius,color,parentRelation,true);
            connect(node,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateEndPoint(QPointF)));

            connect(me,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateStartPoint(QPointF)));
            hasDaughter=false;

            a->UpdateEndPoint(node->pos());
        }
*/
        if(hasPrev&&prev.IsEqual(node->getRelation().toStdString(),node->getId().toStdString())==1)
        {
            Arc* a=new Arc(10,Radius,color,parentRelation,true);
            connect(node,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateEndPoint(QPointF)));

            connect(me,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateStartPoint(QPointF)));
            hasPrev=false;

            a->UpdateEndPoint(node->pos());
        }
/*
        if(hasNext&&next.IsEqual(node->getRelation().toStdString(),node->getId().toStdString())==1)
        {
            Arc* a=new Arc(10,Radius,color,parentRelation,true);
            connect(node,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateEndPoint(QPointF)));

            connect(me,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateStartPoint(QPointF)));
            hasNext=false;
            a->UpdateEndPoint(node->pos());
        }
        */
    }
    if(hasNext)
    {
        tbc.push_front(new Item(next));
        Node* temp=new Node(QString(next.getId().c_str()),relation,QString(next.getName().c_str()),me->pos().x()+4*Radius,me->pos().y(),Radius,color,parentRelation);
        Printed.push_back(temp);
        Arc* a=new Arc(10,Radius,color,parentRelation,true);
        connect(temp,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateEndPoint(QPointF)));
        connect(me,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateStartPoint(QPointF)));

        PositionNode(*temp);
        a->UpdateEndPoint(temp->pos());

    }
    if(hasDaughter)
    {
        Node* temp=new Node(QString(daughter.getId().c_str()),relation,QString(daughter.getName().c_str()),me->pos().x(),me->pos().y()+4*Radius,Radius,color,parentRelation);
        tbc.push_front(new Item(daughter));
        Printed.push_back(temp);
        Arc* a=new Arc(10,Radius,color,parentRelation,true);

        connect(temp,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateEndPoint(QPointF)));
        connect(me,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateStartPoint(QPointF)));
        PositionNode(*temp);
        a->UpdateEndPoint(temp->pos());


    }

    me->notifyPositionChange(me->pos());
}

void GraphManager::changeRelationVisibility(QStandardItem *key)
{
    auto it=Relations.find(key->text());
    (*it)->setVisible(!(*it)->isVisible());
}
