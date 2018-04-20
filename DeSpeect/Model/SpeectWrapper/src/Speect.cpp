#include "Speect.h"
#include "utterance.h"
#include "configuration.h"
Speect::Speect()
    :error(S_SUCCESS)
    ,utt(NULL)
    ,voice(NULL)
    ,config(new Configuration())
    ,plugins(std::list<SPlugin*>())
{
    //set locale to C so that speect produce the right audio
    std::setlocale(LC_ALL, "C");
    //initialize audio
    error=speect_init(s_logger_console_new(false));
}

Speect::~Speect()
{
    //delete all plugins loaded
    for(auto it=plugins.begin();it!=plugins.end();++it)
    {
        S_DELETE(*it,NULL,&error);
    }
    plugins.clear();
    //delete the utterance
    delete utt;
    //delete the voice
    S_DELETE(voice,NULL,&error);
    error=speect_quit();
}
//return error state s_erc is an enum of speect engine see documentation for more info
s_erc &Speect::getErrorState()
{
    return error;
}

//return the utterance
const Utterance *Speect::getUtterance() const
{
    return utt;
}
//return the configuration
Configuration *Speect::getConfiguration() const
{
    return config;
}
//load a plugin and add to the list of plugins loaded to manage memory
bool Speect::addPlugin(const std::string& PluginPath)
{
    bool success=false;
    SPlugin* p=s_pm_load_plugin(PluginPath.c_str(),&error);
    if(error==S_SUCCESS)
    {
        plugins.push_back(p);
        success=true;
    }
    else
    {
        S_DELETE(p,NULL,&error);
        success=false;
    }
    return success;
}
//instatiate the utterance and set the text to Configuration Utterancetext
//voice must be inizialized
#include "iostream"
bool Speect::createUtt()
{
        //if you want to re create an utterance delete the current one
        if(utt!=NULL)
        {
            delete utt;
            utt=NULL;
        }
        if(voice!=NULL){
            //instatiate the speect utterance and initialize it
            SUtterance *i=S_NEW(SUtterance,&error);
            SUtteranceInit(&i,voice,&error);
            //set the text of the utterance that speect will use to the one of the configuration
            SUtteranceSetFeature(i,"input"
                                 ,SObjectSetString(
                                     config->getConfig(Configuration::UtteranceText).c_str()
                                     ,&error
                                     )
                                 ,&error
                                 );
            //create the utterance object from the SUtterance if it's creation had success
            if(error==S_SUCCESS)
                utt=new Utterance(i);
        }

    //return if the utterance has been created
    return utt!=NULL;
}

//initialize the voice
bool Speect::init()
{
    //if there is an utterance delete it
    //utterance depend on voice
    if(utt!=NULL)
    {
        delete utt;
        utt=NULL;
    }
    //if there is a voice delete it
    if(voice!=NULL)
    {
        S_DELETE(voice,NULL,&error);
    }


    //load the voice
    voice=s_vm_load_voice(config->getConfig(Configuration::Voice).c_str(),&error);
    bool loadResult=error==S_SUCCESS;
    //if load failed destroy the allocated memory
    if(!loadResult)
    {
        S_DELETE(voice,NULL,&error);
        voice=NULL;
    }
    return loadResult;
}
//return the name of utterance processor
const std::list<std::string> Speect::getUttProcessorNames()
{
    //get a speect list and put it on a std list destroying all the item and freeing the memory
    SList* temp=SVoiceGetUttProcKeys(voice,&error);
    std::list<std::string> l;
    while(!SListIsEmpty(temp,&error))
    {

        SObject*obj=SListPop(temp,&error);
        l.push_front(std::string(SObjectGetString(obj,&error)));
        S_DELETE(obj,NULL,&error);
    }
    S_DELETE(temp,NULL,&error);
    return l;
}
//return the utterance processor by name
const SUttProcessor *Speect::getUttProcessor(const std::string &Name){
    return SVoiceGetUttProc(voice,Name.c_str(),&error);
}
