#include "gtest/gtest.h"
#include <QApplication>
#include "line.h"

#include <QVector2D>
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include <QColor>
#include "item.h"

TEST(Graph, VerifyLineCollidingDashed){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    QPainter* p = new QPainter();
    QWidget* temp= new QWidget();
    QColor colore(255,255,255);
    Line* l1;
    l1=new Line(12,colore,1,NULL);

    QStyleOptionGraphicsItem *option = new QStyleOptionGraphicsItem();
    l1->paint(p,option,temp);

    EXPECT_TRUE(l1);

    delete l1;
    delete p;
    delete temp;
    delete option;

}

TEST(Graph, VerifyLineNotCollidingDashed){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    QPainter* p = new QPainter();
    QWidget* temp= new QWidget();
    QColor colore(255,255,255);
    Line* l1;
    l1=new Line(12,colore,1,NULL);

    QStyleOptionGraphicsItem *option = new QStyleOptionGraphicsItem();
    QPointF* start = new QPointF(0,0);
    QPointF* end = new QPointF(10,10);

    l1->UpdateStartPoint(*start);
    l1->UpdateEndPoint(*end);
    l1->paint(p,option,temp);

    EXPECT_TRUE(l1);

    delete l1;
    delete p;
    delete temp;
    delete option;

}


TEST(Graph, VerifyLineCollidingNotDashed){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    QPainter* p = new QPainter();
    QWidget* temp= new QWidget();
    QColor colore(255,255,255);
    Line* l1;
    l1=new Line(12,colore,0,NULL);

    QStyleOptionGraphicsItem *option = new QStyleOptionGraphicsItem();
    l1->paint(p,option,temp);

    EXPECT_TRUE(l1);

    delete l1;
    delete p;
    delete temp;
    delete option;

}

TEST(Graph, ChangeVisibilityFalseParentShow){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    QPainter* p = new QPainter();
    QWidget* temp= new QWidget();
    QColor colore(255,255,255);
    QGraphicsItem* parent= new Line(0,colore,0,NULL);
    Line* l1;
    l1=new Line(12,colore,0,parent);

    l1->changeVisibility(false);

    EXPECT_TRUE(l1->isVisible());

    delete l1;
    delete p;
    delete temp;

}

TEST(Graph, ChangeVisibilityFalseParentHidden){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    QPainter* p = new QPainter();
    QWidget* temp= new QWidget();
    QColor colore(255,255,255);
    QGraphicsItem* parent= new Line(0,colore,0,NULL);
    parent->hide();
    Line* l1;
    l1=new Line(12,colore,0,parent);

    l1->changeVisibility(false);

    EXPECT_FALSE(l1->isVisible());

    delete l1;
    delete p;
    delete temp;

}

TEST(Graph, ChangeVisibilityFalse){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    QPainter* p = new QPainter();
    QWidget* temp= new QWidget();
    QColor colore(255,255,255);
    Line* l1;
    l1=new Line(12,colore,0,NULL);

    l1->changeVisibility(false);

    EXPECT_FALSE(l1->isVisible());

    delete l1;
    delete p;
    delete temp;

}

TEST(Graph, ChangeVisibilityFalseFalseTrue){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    QPainter* p = new QPainter();
    QWidget* temp= new QWidget();
    QColor colore(255,255,255);
    Line* l1;
    l1=new Line(12,colore,0,NULL);

    l1->changeVisibility(false);
    l1->changeVisibility(false);
    l1->changeVisibility(true);

    EXPECT_FALSE(l1->isVisible());

    delete l1;
    delete p;
    delete temp;

}

TEST(Graph, ChangeVisibilityFalseTrue){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    QPainter* p = new QPainter();
    QWidget* temp= new QWidget();
    QColor colore(255,255,255);
    Line* l1;
    l1=new Line(12,colore,0,NULL);

    l1->changeVisibility(false);
    l1->changeVisibility(true);

    EXPECT_TRUE(l1->isVisible());

    delete l1;
    delete p;
    delete temp;

}


