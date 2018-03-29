#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <QApplication>
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
#include "mainwindow.h"
int main(int argc, char **argv) {

    //save all speect error on SpeectError.txt
    //stderr is the output stream used by speect
    freopen("SpeectError.txt","w",stderr);

    //instatiate speect and set some configuration

Speect* s=new Speect();
//abstract command to execute operation on speect
AbstractCommand* t9=NULL;

t9=new SetSpeectConfigCommand(s,Configuration::Audio,"test.wav");
std::cout<<t9->execute()<<std::endl;
delete t9;
t9=new SetSpeectConfigCommand(s,Configuration::Voice,"/home/marco/Scrivania/SWE-Project/SpeectInstaller/voices/cmu_arctic_slt/voice.json");
std::cout<<t9->execute()<<std::endl;
delete t9;
t9=new SetSpeectConfigCommand(s,Configuration::UtteranceText,"Hi speect test.This is a test for multisons");
std::cout<<t9->execute()<<std::endl;
delete t9;
//if the voice get inizialized
  //  if(s->init())
 //   {
    	std::cout<<"Here all the Utterance Processor Name:"<<std::endl;
		std::list<std::string> t=s->getUttProcessorNames();
        for(std::list<std::string>::iterator it=t.begin();it!=t.end();++it)
            std::cout<<(*it)<<std::endl;

        std::cout<<"Adding Plugins via Commmand"<<std::endl;
        t9=new LoadPluginCommand(s,"audio_riff.spi");
        std::cout<<t9->execute();
        delete t9;
        t9=NULL;
        //instatiate the utterance
 //       s->createUtt();

		s_erc error=S_SUCCESS;
        std::cout<<std::endl<<"Executing Tokenizer via Command"<<std::endl;


      //  AbstractCommand* t9=new UttProcessorCommand(s,"Tokenize");
        t9=new UttProcessorCommand(s,"Tokenize");
        std::cout<< t9->execute()<<std::endl;
        delete t9;
        t9=NULL;

      /* if(s->getUtterance()){
        std::cout<<"Printing the generated relations:"<<std::endl;
		std::list<std::string> t2=(s->getUtterance())->getRelationNamesList();
        for(std::list<std::string>::iterator it=t2.begin();it!=t2.end();++it)
        std::cout<<(*it)<<std::endl;
        }*/
        std::cout<<"Executing Normalizer"<<std::endl;
        t9=new UttProcessorCommand(s,"Normalize");
        std::cout<< t9->execute()<<std::endl;
        delete t9;
        t9=NULL;
        std::cout<<"Executing Phrasify"<<std::endl;
        t9=new UttProcessorCommand(s,"Phrasify");
        std::cout<< t9->execute()<<std::endl;
        delete t9;
        t9=NULL;
        std::cout<<"Executing LexLookup"<<std::endl;
        t9=new UttProcessorCommand(s,"LexLookup");
        std::cout<< t9->execute()<<std::endl;
        delete t9;
        t9=NULL;
        std::cout<<"Executing Pauses"<<std::endl;
        t9=new UttProcessorCommand(s,"Pauses");
        std::cout<< t9->execute()<<std::endl;
        delete t9;
        t9=NULL;
        std::cout<<"Executing HTS Engine Synthesizer"<<std::endl;
        t9=new UttProcessorCommand(s,"HTS Engine Synthesizer");
        std::cout<< t9->execute()<<std::endl;
        delete t9;
        t9=NULL;
   if(s->getUtterance()){
        std::cout<<"Printing the generated relations:"<<std::endl;
        std::list<std::string> t2=(s->getUtterance())->getRelationNamesList();
		for(std::list<std::string>::iterator it=t2.begin();it!=t2.end();++it)
        std::cout<<(*it)<<std::endl;
        }
        t9=new CreateAudioCommand(s,"riff");
        std::cout<<t9->execute();
        QApplication a(argc,argv);
        MainWindow x;
        x.show();
        QVector<QColor> colors;
        colors.push_back(QColor(qRgb(172,25,248)));
        colors.push_back(QColor(qRgb(5,210,153)));
        colors.push_back(QColor(qRgb(71,194,52)));
        colors.push_back(QColor(qRgb(24,241,95)));
        colors.push_back(QColor(qRgb(199,1,7)));
        colors.push_back(QColor(qRgb(63,230,150)));
        colors.push_back(QColor(qRgb(151,157,0)));
        int i=0;
        if(s->getUtterance())
        foreach(auto relname,s->getUtterance()->getRelationNamesList())
        {
            auto it=s->getUtterance()->getRelationByName(relname).getRelationHead();
            x.g.printRelation(relname.c_str(),&it,colors.at(i));
            ++i;
        }


        delete t9;
return a.exec();
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
