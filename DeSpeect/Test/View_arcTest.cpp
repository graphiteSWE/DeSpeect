#include "gtest/gtest.h"
#include <QApplication>
#include "arc.h"

#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include <QColor>
#include "item.h"

TEST(Graph, VerifyArc){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    QPainter* p = new QPainter();
    QWidget* temp= new QWidget();
    QColor colore(255,255,255);
    const int Radius=1;
    Arc* a1;
    a1=new Arc(12,Radius,colore,1,1,NULL,0);
    a1->UpdateStartPoint(QPoint(0,0));
    a1->UpdateEndPoint(QPoint(10,10));

    QStyleOptionGraphicsItem *option = new QStyleOptionGraphicsItem();
    a1->paint(p,option,temp);

    EXPECT_TRUE(a1);

    delete a1;
    delete p;
    delete temp;
    delete option;


}


TEST(Graph, VerifyArcParam){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    QPainter* p = new QPainter();
    QWidget* temp= new QWidget();
    QColor colore(255,255,255);
    const int Radius=1;
    Arc* a1;
    a1=new Arc(12,Radius,colore,0,1,NULL,0);
    a1->UpdateStartPoint(QPoint(0,0));
    a1->UpdateEndPoint(QPoint(10,10));

    QStyleOptionGraphicsItem *option = new QStyleOptionGraphicsItem();
    a1->paint(p,option,temp);

    EXPECT_TRUE(a1);

    delete a1;
    delete p;
    delete temp;
    delete option;
}

