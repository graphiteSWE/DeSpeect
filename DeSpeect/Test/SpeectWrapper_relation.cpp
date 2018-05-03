#include "gtest/gtest.h"
#include <commandlist.h>
#include <unistd.h>

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
#include <thread>

TEST(SpeectWrapper, CreateRelationTest){
    std::string a="";
    a.clear();
    Relation* r=new Relation(Item(NULL, "a"), a);
    ASSERT_TRUE(r);
    delete r;
}
