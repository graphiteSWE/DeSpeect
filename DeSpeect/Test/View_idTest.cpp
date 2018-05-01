#include "gtest/gtest.h"
#include "id.h"

TEST(Graph, VerifyId){
    ID* a = new ID("a","a");
    ID* b = new ID("b","b");
    EXPECT_FALSE(a==b);
    delete a;
    delete b;
}
