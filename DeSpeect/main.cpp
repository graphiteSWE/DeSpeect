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
    //save all speect error on SpeectError.txt
    //stderr is the output stream used by speect
    QFile file("ErrorLog.txt");
    file.remove();
    stderr=freopen("ErrorLog.txt","a",stderr);
    setvbuf(stderr, NULL, _IONBF, 0);
    //instatiate speect and set some configuration
    Speect* s=new Speect();
    QApplication a(argc,argv);
    CommandList::CommandBuilder* Builder=new CommandList::CommandBuilder(s);
    ModelView x(Builder);
    //set locale to C so that speect produce the right audio
    std::setlocale(LC_ALL, "C");
    x.show();
    a.exec();
}
