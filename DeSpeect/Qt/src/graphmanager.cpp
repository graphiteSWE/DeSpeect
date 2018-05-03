#include "graphmanager.h"
#include <QFocusEvent>
#include <QGraphicsItemGroup>
#include <QGraphicsView>
#include <arc.h>
#include <item.h>
#include <node.h>

/*
 * File: graphmanager.cpp
 * Type: src
 * Date: 2018-04-23
 * E-mail: graphite.swe@gmail.com
 * 
 * Description: manage graphs and relations to keep the two models coherent 
 */
 
/*
 * Description: GraphManager copy constructor, made private to avoid copy costruction of the manager
 * @param const GraphManager& - GraphManager to be copied
 */
GraphManager::GraphManager(const GraphManager &)
{
}

// Description: GraphManager constructor 
GraphManager::GraphManager()
    :Graph(new QGraphicsScene())
    ,Relations()
    ,RelationsModel(new QStandardItemModel())
{
    //when an item in the relations model get checked or unchecked graph manager will tell to the graph to hide or show the relation
    connect(RelationsModel,SIGNAL(itemChanged(QStandardItem*)),this,SLOT(changeRelationVisibility(QStandardItem*)));
    connect(Graph,SIGNAL(selectionChanged()),this,SLOT(notifySelection()));
}

// Description: GraphManager destructor
GraphManager::~GraphManager()
{

    clear();

    delete Graph;
    delete RelationsModel;

}

/*
 * Description: returns the graph model to be linked with the view
 * @param QGraphicsView* view - Qt graphic view as view component (see Qt docs for more info)
 * @return void
 */
void GraphManager::linkGraphModel(QGraphicsView* v)
{
    v->setScene(Graph);
}

/*
 * Description: returns the relation model to be linked with the view
 * @param QListView* - Qt list view (see Qt docs for more info)
 * @return void
 */
void GraphManager::linkRelationModel(QListView* v)
{
    v->setModel(RelationsModel);
}

/*
 * Description: prints the relations which start from the given item, with the chosen name and the chosen color
 * @param const QString& - Qt string as relation name (see Qt docs for more info)
 * @param const Item* - initial item
 * @param const QColor& - Qt color as chosen color (see Qt docs for more info)
 * @return bool
 */
bool GraphManager::printRelation(const QString &id, const Item *SpeectNode, const QColor &Color)
{
    //items that must have their relations check
    QVector<const Item*>ToBeChecked;
    //generate the relation
    QGraphicsRectItem* parentRelation=generateRelation(id,Color);
    //if no error in generation of relations
    if(parentRelation!=NULL){
    //add to graph the relation
        Graph->addItem(parentRelation);
        //add to nodes that must be checked the head node
        ToBeChecked.push_back(SpeectNode);
        Node* t=new Node(QString(SpeectNode->getId().c_str()),id,QString(SpeectNode->getName().c_str()),Radius+10,Radius+20,Radius,Color,parentRelation);
        Printed.push_back(t);
        FixHeadPosition(*t);
        //cicle till there is no more nodes to be checked
        while(!ToBeChecked.isEmpty())
        {
            //fix the relations and print next and daughter
            checkRelations(ToBeChecked,id,Color,parentRelation);
        }
    }
}

/*
 * Description: clears both models
 * @return void
 */
#include "iostream"
void GraphManager::clear()
{
    //clear the vector and the Relations
    Relations.clear();
    Printed.clear();
    //clear the graph (delete all items inside)
    Graph->clear();

    //clear the relationsModel and delete all item in it
    for(int i=0;i<RelationsModel->rowCount();++i)
    {
        delete RelationsModel->item(0);
    }
    RelationsModel->clear();
}


/*
 * Description: generates the relation item to use as parent of all nodes and arcs 
 * @param const QString& - Qt string as relation name (see Qt docs for more info) 
 * @param const QColor& - Qt color as relation color (see Qt docs for more info)
 * @return QGraphicsRectItem *
 */
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

/*
 * Description: generates the item to be added into the relations model
 * @param const QString& - Qt string as relation name (see Qt docs for more info) 
 * @param const QColor & - Qt color as relation color (see Qt docs for more info)
 * @return QStandardItem *
 */
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

/*
 * Description: positions the node in the first column where it doesn't collide
 * @param Node& - node reference
 * @return void
 */
void GraphManager::PositionNode(Node &me)
{
    while(me.collidingItems().size()>1){
        me.setX(me.x()+(4*Radius));
    }
}

/*
 * Description: positions the node in the first row where it doesn't collide
 * @param Node& - node reference
 * @return void
 */
void GraphManager::FixHeadPosition(Node &me)
{
    while(me.collidingItems().size()>1){
        me.setY(me.y()+(4*Radius));
    }
}

/*
 * Description: check the relation of the first item in the list, the node that graphically represents the item
 * 				must be in Printed QVector, this method check the relations of the item and correctly
 *				add to the list of nodes that must be checked the next and the daughter of the item
 * @param QVector<const Item*>& - items vector
 * @param const QString &relation - Qt string as relation name (see Qt docs for more info) 
 * @param const QColor &color - Qt color as relation color (see Qt docs for more info)
 * @param QGraphicsItem *parentRelation - Qt graphics item as parent relation (see Qt docs for more info)
 * @return void
 */
void GraphManager::checkRelations(QVector<const Item*> &tbc, const QString& relation, const QColor& color, QGraphicsItem *parentRelation)
{
    //take first item
    const Item* toBeChecked=tbc.takeFirst();
    //check if item has other pointer
    bool hasFather=toBeChecked->hasFather();
    bool hasDaughter=toBeChecked->hasDaughter();
    bool hasNext=toBeChecked->hasNext();
    bool hasPrev=toBeChecked->hasPrev();
    //get the items
    const Item father=toBeChecked->father()
            ,daughter=toBeChecked->daughter()
            ,next=toBeChecked->next()
            ,prev=toBeChecked->prev();


    //find which node represent the items
    Node* me=NULL;
    for(auto it=Printed.begin();it!=Printed.end()&&me==NULL;++it)
    {
       if(toBeChecked->IsEqual((*it)->getRelation().toStdString(),(*it)->getId().toStdString())==1){
            me=*it;
       }
    }
    //if find the node continue otherwise stop and fail
    if(me)
    {
        foreach(Node* node,Printed)
        {
            //If item is equal and have different relation draw a dashed line
            if(toBeChecked->IsEqual(node->getRelation().toStdString(),node->getId().toStdString())==2)
            {
                Line* a=new Line(Radius,QColor(qRgb(0,0,0)),1,NULL);
                connect(node,SIGNAL(notifyVisibilityChange(bool)),a,SLOT(changeVisibility(bool)));
                connect(node,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateEndPoint(QPointF)));
                connect(me,SIGNAL(notifyVisibilityChange(bool)),a,SLOT(changeVisibility(bool)));
                connect(me,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateStartPoint(QPointF)));
                Graph->addItem(a);
                a->UpdateStartPoint(me->pos());
                a->UpdateEndPoint(node->pos());
            }
            else
            {
                //otherwise check if it's my father in the same relation
                if(hasFather&&father.IsEqual(node->getRelation().toStdString(),node->getId().toStdString())==1)
                {
                    Arc* a=new Arc(12,Radius,color,0,0,parentRelation,false);
                    connect(node,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateEndPoint(QPointF)));
                    connect(me,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateStartPoint(QPointF)));
                    hasFather=false;
                    a->UpdateEndPoint(node->pos());
                }
                //and check if it's my prev in the same relations
                //not in exclusive else because don t know if it's impossible to happen in speect HRG
                if(hasPrev&&prev.IsEqual(node->getRelation().toStdString(),node->getId().toStdString())==1)
                {
                    Arc* a=new Arc(12,Radius,color,1,0,parentRelation,false);
                    connect(node,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateEndPoint(QPointF)));

                    connect(me,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateStartPoint(QPointF)));
                    hasPrev=false;

                    a->UpdateEndPoint(node->pos());
                }
            }
        }
    //if exist add the next nodes to the printed items and to the one that must be checked
    if(hasNext)
    {
        tbc.push_front(new Item(next));
        Node* temp=new Node(QString(next.getId().c_str()),relation,QString(next.getName().c_str()),me->pos().x()+4*Radius,me->pos().y(),Radius,color,parentRelation);
        Printed.push_back(temp);
        temp->clearFocus();
        Arc* a=new Arc(12,Radius,color,1,1,parentRelation,false);
        connect(temp,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateEndPoint(QPointF)));
        connect(me,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateStartPoint(QPointF)));

        PositionNode(*temp);
        a->UpdateEndPoint(temp->pos());

    }
    //if exist add the daughter to the printed items and to the one that must be checked
    if(hasDaughter)
    {
        Node* temp=new Node(QString(daughter.getId().c_str()),relation,QString(daughter.getName().c_str()),me->pos().x(),me->pos().y()+4*Radius,Radius,color,parentRelation);
        tbc.push_front(new Item(daughter));
        Printed.push_back(temp);
        temp->clearFocus();
        Arc* a=new Arc(12,Radius,color,0,1,parentRelation,false);

        connect(temp,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateEndPoint(QPointF)));
        connect(me,SIGNAL(notifyPositionChange(QPointF)),a,SLOT(UpdateStartPoint(QPointF)));
        PositionNode(*temp);
        a->UpdateEndPoint(temp->pos());
    }
        me->notifyPositionChange(me->pos());
    }

}

/*
 * Description: changes the visibility of the relations in the graph
 * @param QStandardItem * - Qt standard item as relation reference (see Qt docs for more info)
 * @return void
 */
void GraphManager::changeRelationVisibility(QStandardItem *key)
{
    //find the item that represent the relation in the graph model and hide it
    auto it=Relations.find(key->text());
    (*it)->setVisible(!(*it)->isVisible());
}

/*
 * Description: notifies the selection/deselection of a item
 * @return void
 */
void GraphManager::notifySelection()
{
    QList<QGraphicsItem*> selected(Graph->selectedItems());
    if(!selected.empty())
    {
    auto myNode=std::find(Printed.begin(),Printed.end(),selected.first());

        if(myNode!=Printed.end())
        {
            focusSignal((*myNode)->getRelation(),(*myNode)->getId(),true);
        }

    }
    else{
        cleardetails();
    }
}

/*
 * Description: selects and focuses the node given the relation and the path
 * @param const QString& - Qt string as relation name (see Qt docs for more info) 
 * @param const QString& - Qt string as path (see Qt docs for more info) 
 * @return void
 */
void GraphManager::selectItem(const QString &relation, const QString &path)
{
    ID searchedItem(path,relation);
    foreach(Node* item,Printed)
    {
        if((*item)==searchedItem)
            item->setFocus();
    }
}
