#include "Speect.h"
#include "configuration.h"
#include "utterance.h"
#include "iterator"
#include "item.h"
#include "relation.h"
#include <iostream>
/* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/ 
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include<iostream>
int main(int argc, char **argv) {
	//instatiate speect and set some configuration
Speect* s=new Speect();
Configuration* temp=(s->getConfiguration());
temp->setConfig(Configuration::Voice,"/home/marco/Scrivania/SWE-Project/SpeectInstaller/voices/cmu_arctic_slt/voice.json");
temp->setConfig(Configuration::UtteranceText,"Hi speect test.");
//if the voice get inizialized
    if(s->init())
    {
    	std::cout<<"Here all the Utterance Processor Name:"<<std::endl;
		std::list<std::string> t=s->getUttProcessorNames();
        for(std::list<std::string>::iterator it=t.begin();it!=t.end();++it)
            std::cout<<(*it)<<std::endl;
        //instatiate the utterance
        s->createUtt();

		s_erc error=S_SUCCESS;
		std::cout<<"Executing Tokenizer"<<std::endl;
        SUttProcessorRun(s->getUttProcessor(std::string("Tokenize")),s->getUtterance()->getUtterance(),&error);
		std::cout<<"Printing the generated relations:"<<std::endl;
		std::list<std::string> t2=(s->getUtterance())->getRelationNamesList();
		for(std::list<std::string>::iterator it=t2.begin();it!=t2.end();++it)
        std::cout<<(*it)<<std::endl;
		std::cout<<"Executing Normalizer"<<std::endl;
        SUttProcessorRun(s->getUttProcessor(std::string("Normalize")),s->getUtterance()->getUtterance(),&error);
		std::cout<<"Printing the generated relations:"<<std::endl;
		t2=(s->getUtterance())->getRelationNamesList();
		for(std::list<std::string>::iterator it=t2.begin();it!=t2.end();++it)
        std::cout<<(*it)<<std::endl;

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
		
    }
}
