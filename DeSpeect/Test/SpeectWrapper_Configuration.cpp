#include "gtest/gtest.h"
#include <configuration.h>

TEST(SpeectWrapper,VerifySetConfig){
   Configuration* conf= new Configuration();

   conf->setConfig(Configuration::configName::MAXSIZE,"");

   EXPECT_TRUE(conf);

   delete conf;
}

TEST(SpeectWrapper,VerifyChanged){
   Configuration* conf= new Configuration();

   conf->hasChanged(Configuration::configName::Voice);

   EXPECT_TRUE(conf);

   delete conf;
}


TEST(SpeectWrapper,VerifyGetConfig){
   Configuration* conf= new Configuration();

   conf->getConfig(Configuration::configName::MAXSIZE);

   EXPECT_TRUE(conf);

   delete conf;
}
