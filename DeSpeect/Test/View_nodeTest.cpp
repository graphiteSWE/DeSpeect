#include "gtest/gtest.h"
#include <QApplication>
#include "node.h"
#include "arc.h"

#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include <QColor>
#include "item.h"

#include <QGraphicsSceneMouseEvent>

//#include <QtTest/QTest>
TEST(Graph, VerifyNodePaint){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    QPainter* p = new QPainter();
    QWidget* temp= new QWidget();

    Node* n = new Node("n1","n1","n1",0,0,10,QColor(255,0,0),NULL);

    QStyleOptionGraphicsItem *option = new QStyleOptionGraphicsItem();
    n->paint(p,option,temp);

    EXPECT_TRUE(n);

    delete n;
    delete p;
    delete temp;
    delete option;


}

TEST(Graph, VerifyNodePaintSelected){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    QPainter* p = new QPainter();
    QWidget* temp= new QWidget();

    Node* n = new Node("n1","n1","n1",0,0,10,QColor(255,0,0),NULL);

    n->setSelected(true);

    QStyleOptionGraphicsItem *option = new QStyleOptionGraphicsItem();
    n->paint(p,option,temp);

    EXPECT_TRUE(n);

    delete n;
    delete p;
    delete temp;
    delete option;


}

TEST(Graph, VerifyNodePaintFocus){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    QPainter* p = new QPainter();
    QWidget* temp= new QWidget();

    Node* n = new Node("n1","n1","n1",0,0,10,QColor(255,0,0),NULL);

    n->setFocus();
    n->setSelected(false);
    QStyleOptionGraphicsItem *option = new QStyleOptionGraphicsItem();
    n->paint(p,option,temp);

    EXPECT_TRUE(n);

    delete n;
    delete p;
    delete temp;
    delete option;


}

TEST(Graph, VerifyNodeEqNode){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);

    Node n1("n1","n1","n1",0,0,10,QColor(255,0,0),NULL);
    Node n2("n2","n2","n2",30,30,10,QColor(255,255,0),NULL);

    EXPECT_FALSE(n1==n2);

}

TEST(Graph, VerifyNodeEqNodeID){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);

    Node n1("n1","n1","n1",0,0,10,QColor(255,0,0),NULL);
    ID idN1("n1","n1");

    EXPECT_TRUE(n1==idN1);

}

TEST(Graph, VerifyNodeCatchVisibility){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);

    Node* n = new Node("n1","n1","n1",0,0,10,QColor(255,0,0),NULL);
    n->catchVisibilityChange();

    EXPECT_TRUE(n);

}


TEST(Graph, VerifyNodeMouseRelease){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);
    Node* n = new Node("n1","n1","n1",0,0,10,QColor(255,0,0),NULL);
    QGraphicsSceneMouseEvent e(QEvent::GraphicsSceneMouseRelease);
    n->mouseReleaseEvent(&e);

    EXPECT_TRUE(n);

    delete n;

}
