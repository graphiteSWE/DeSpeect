#include "gtest/gtest.h"
#include "id.h"

TEST(Graph, VerifyId){
    ID a("a","a");
    ID b("b","b");
    EXPECT_FALSE(a==b);
}
