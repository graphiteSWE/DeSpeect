#include "gtest/gtest.h"
#include <QApplication>
#include <processormanager.h>
TEST(Graph, VerifyNodePaint){
    int argc;
    char **argv=NULL;
    QApplication app(argc,argv);

    ProcessorManager *p=new ProcessorManager();

    EXPECT_TRUE(p->isLayoutClean());

    delete p;

}
