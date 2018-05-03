#include "gtest/gtest.h"
#include <QApplication>
#include "node.h"
#include "arc.h"

#include <QWidget>
#include "datanodemanager.h"
#include "id.h"

TEST(View, NodeManagerClear){
    DataNodeManager n;
    std::map<std::string, std::string> m;
    m.insert(std::pair<std::string, std::string>("first","data"));
    n.showNode(m);
    n.clear();
    EXPECT_TRUE(n.getNodeId()==ID("",""));
}

TEST(View, NodeManagerNotNullTest){
    DataNodeManager n;
    std::map<std::string, std::string> m;
    m.insert(std::pair<std::string, std::string>("DespeectItemIDPath"," .n.n.n"));
    m.insert(std::pair<std::string, std::string>("DespeectItemIDRelation","Token"));
    n.showNode(m);
    EXPECT_TRUE(n.getNodeId()==ID(" .n.n.n", "Token"));
}
