#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <QApplication>
#include <QFile>
#include <commandlist.h>
#include <unistd.h>
#define GetCurrentDir getcwd
#endif


#include "uttprocessorcommand.h"
#include <iostream>
#include "relation.h"
#include "loadplugincommand.h"
#include "setspeectconfigcommand.h"
#include <configuration.h>
#include<iostream>
#include "createaudiocommand.h"
#include "modelview.h"
int main(int argc, char **argv) {
    //set locale to C so that speect produce the right audio
    std::setlocale(LC_ALL, "C");
    //save all speect error on SpeectError.txt
    //stderr is the output stream used by speect
    QFile file("ErrorLog.txt");
    file.remove();
    stderr=freopen("ErrorLog.txt","a",stderr);
    setvbuf(stderr, NULL, _IONBF, 0);
    //instatiate speect and set some configuration

Speect* s=new Speect();
//set locale to C so that speect produce the right audio
std::setlocale(LC_ALL, "C");
QApplication a(argc,argv);
//set locale to C so that speect produce the right audio
std::setlocale(LC_ALL, "C");
CommandList::CommandBuilder* Builder=new CommandList::CommandBuilder(s);
//set locale to C so that speect produce the right audio
std::setlocale(LC_ALL, "C");
ModelView x(Builder);
//set locale to C so that speect produce the right audio
std::setlocale(LC_ALL, "C");
//Builder->LoadConfig(Configuration::Audio,"test.wav").getCommandList()->executeAll();
//AbstractCommand* t9;
//t9=new UttProcessorCommand(s,"Tokenize");
//t9->execute();

//delete s->getUtterance();
//abstract command to execute operation on speect
/*
x.requestConfiguration("test.wav",Configuration::Audio);
x.requestConfiguration("/home/marco/Scrivania/SWE-Project/SpeectInstaller/voices/cmu_arctic_slt/voice.json",Configuration::Voice);

x.requestConfiguration("Hi speect test.This is a test for multisons",Configuration::UtteranceText);
x.requestProcessorRun();
//s->createUtt();
x.requestConfiguration("Hi test.This is a test for multisons",Configuration::UtteranceText);
//x.requestProcessorRun();
/*x.requestConfiguration("/home/marco/Scrivania/SWE-Project/SpeectInstaller/voices/cmu_arctic_slt/voice.json",Configuration::Voice);
x.requestConfiguration("Hi speect test.This is a test for multisons",Configuration::UtteranceText);
std::list<std::string> t=s->getUttProcessorNames();
for(std::list<std::string>::iterator it=t.begin();it!=t.end();++it)
            std::cout<<(*it)<<std::endl;
QList<QString> tempList;
tempList.push_back("audio_riff.spi");
x.requestPluginLoad(tempList);
x.requestProcessorRun(0);
*/
/*
QList<QString> tempList;
tempList.push_back("audio_riff.spi");
x.requestPluginLoad(tempList);

*/
//set locale to C so that speect produce the right audio
std::setlocale(LC_ALL, "C");
x.show();
//set locale to C so that speect produce the right audio
std::setlocale(LC_ALL, "C");

a.exec();/*
t9=new CreateAudioCommand(s,"riff");
std::cout<<t9->execute();
delete t9;
        /*
		std::cout<<"Checking if Token head is equal to Word head and checking if IsEqual work: should return false"<<std::endl;
		std::cout<<(s->getUtterance()->getRelationByName("Token"))->getRelationHead().IsEqual("Word","")<<std::endl;
		std::cout<<"Going to the node of Token that is shared with Word and checking if IsEqual work: should return true"<<std::endl;
		std::cout<<(s->getUtterance()->getRelationByName("Token"))->getRelationHead().daughter().IsEqual("Word","")<<std::endl;
		std::cout<<"Printing all the Word nexts not printing full graph:"<<std::endl;
        Item i=s->getUtterance()->getRelationByName("Word")->getRelationHead();
        while(!i.isNull())
        {
			std::cout<<i.getName()<<std::endl;
            i=i.next();
		}
*/
//    }
}
