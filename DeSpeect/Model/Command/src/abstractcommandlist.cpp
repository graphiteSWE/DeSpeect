#include "abstractcommandlist.h"


//Invokes the execute method of all commands in the list and clean the list
void AbstractCommandList::executeAll(){
    while(!commands.empty()){
        AbstractCommandList::executeStep();
    }

}

//Invokes the execute method of the first command in the list and remove command
void AbstractCommandList::executeStep(){
    if(!commands.empty()){
        AbstractCommand* pHead=*(commands.begin());
        commands.pop_front();

        ErrorLog.push_back(pHead->execute());
        delete pHead;
    }
}

//Return ErrorLog list
std::list<std::string> AbstractCommandList::getErrorState() const{
   return ErrorLog;
}


//Clear ErrorLog list
void AbstractCommandList::clearErrorState() const{
   ErrorLog.clear();
}

//Add command to list commands
void AbstractCommandList::addCommand(AbstractCommand* command){
    commands.push_back(command);
}


//Add all commands inside listOfCommands
void AbstractCommandList::addCommand(AbstractCommandList& listOfCommands){
     while(!listOfCommands.commands.empty()){
         AbstractCommand* command=*(listOfCommands.commands.begin());
         addCommand(command);
         listOfCommands.commands.pop_front();
     }

}
