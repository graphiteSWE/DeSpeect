#include "gtest/gtest.h"
#include <QApplication>
#include "arc.h"

#include <commandlist.h>
#include <unistd.h>
//#define GetCurrentDir getcwd

#include "ui_view.h"
#include "modelview.h"
#include <QFileDialog>
#include <graphmanager.h>
#include <loadplugincommand.h>
#include <setspeectconfigcommand.h>
#include <uttprocessorcommand.h>
#include "relation.h"
#include "QTextStream"
#include <QFont>
#include <QProcess>

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
    a1=new Arc(12,Radius,colore,0,0,NULL,0);
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

