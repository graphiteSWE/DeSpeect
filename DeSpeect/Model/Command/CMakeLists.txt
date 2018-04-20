cmake_minimum_required(VERSION 2.8.9)
set (CMAKE_CXX_STANDARD 11)
include_directories(../SpeectWrapper/header)
include_directories(header)
set( SOURCES
    src/abstractcommand.cpp
    src/commandlist.cpp
    src/uttprocessorcommand.cpp
    src/loadplugincommand.cpp
    src/setspeectconfigcommand.cpp
    src/createaudiocommand.cpp
)
set( HEADER
    header/abstractcommand.h
    header/commandlist.h
    header/uttprocessorcommand.h
    header/loadplugincommand.h
    header/setspeectconfigcommand.h
    header/createaudiocommand.h

)
# compile
add_library(Command ${SOURCES} ${HEADER})
target_include_directories (Command PUBLIC INCLUDE_DIRECTORIES)
target_link_libraries(Command)
