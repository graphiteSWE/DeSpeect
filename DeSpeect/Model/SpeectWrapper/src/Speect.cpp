#include "Speect.h"
#include "utterance.h"
#include "configuration.h"
std::string Speect::createId(const SItem *it)
{
    std::string path="";
    const SRelation* rel=SItemRelation(it,&error);
    bool fail=false;
    SItem *temp=NULL;
    while(!SItemEqual(it,SRelationHead(rel,&error),&error)&&!fail)
    {
        temp=SItemPrev(it,&error);
        if(temp!=NULL)
        {
            path=".n"+path;
            it=temp;
        }
        else{
            temp=SItemParent(it,&error);
            if(temp!=NULL)
            {
            path=".daughter"+path;
            it=temp;
            }
            else
                fail=true;
        }
    }

    return fail?"":path=" "+path;

}

Speect::Speect()
    :error(S_SUCCESS)
    ,utt(NULL)
    ,voice(NULL)
    ,config(new Configuration())
    ,plugins(std::list<SPlugin*>())
{

    //initialize audio
    error=speect_init(s_logger_console_new(false));
    addPlugin("audio_riff.spi");
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

#include <bits/stl_map.h>
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

const std::list<std::string> Speect::getUttTypeName()
{
    SList *temp=SVoiceGetUttTypesKeys(voice,&error);
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
const std::list<std::string> Speect::getUttProcessorNames(const std::string & uttType)
{

    const SList *temp=SVoiceGetUttType(voice,uttType.c_str(),&error);
    std::list<std::string> l;

    if(temp){
        int size=SListSize(temp,&error);
        for(int i=0;i<size;++i)
        {
            l.push_back(std::string(SObjectGetString(SListNth(temp,i,&error),&error)));
        }
    }
    return l;
}

const std::map<std::string, std::string> Speect::getNode(const std::string &path, const std::string& relation)
{
    std::map<std::string,std::string> featureMap;

    const SItem* temp=SItemPathToItem(SRelationHead(SUtteranceGetRelation(utt->getUtterance(),relation.c_str(),&error),&error),path.c_str(),&error);

    featureMap.insert(std::pair<std::string,std::string>
                      ("DespeectItemIDPath",createId(temp))
                      );
    featureMap.insert(std::pair<std::string,std::string>
                      ("DespeectItemIDRelation",relation)
                      );
    SList* list=SItemFeatKeys(temp,&error);
    if(list)
    {
        int size=SListSize(list,&error);
        for(int i=0;i<size;++i)
        {
            std::string featureName(SObjectGetString(SListNth(list,i,&error),&error));
            const SObject* feature=SItemGetObject(temp,featureName.c_str(),&error);

            if(feature!=NULL){
                if(SObjectIsType(feature,"SInt",&error)){
                    int t=SObjectGetInt(feature,&error);
                    featureMap.insert(std::pair<std::string,std::string>
                              (std::string(featureName)
                              ,(std::string(std::to_string(t))
                                )
                               )
                              );
                }
                else
                if(SObjectIsType(feature,"SFloat",&error)){
                    float t=SObjectGetFloat(feature,&error);
                    featureMap.insert(std::pair<std::string,std::string>
                              (std::string(featureName)
                              ,(std::string(std::to_string(t))
                                )
                               )
                              );
                }
                else
                if(SObjectIsType(feature,"SString",&error)){
                    featureMap.insert(std::pair<std::string,std::string>
                              (std::string(featureName)
                              ,(std::string(SObjectGetString(feature,&error))
                                )
                               )
                              );
                }

            }
            else
            {
                featureMap.insert(std::pair<std::string,std::string>
                               (std::string(featureName)
                               ,(std::string(featureName)
                                 )
                                )
                               );
            }
        }
    }
    return featureMap;
}
