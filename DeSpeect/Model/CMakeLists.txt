cmake_minimum_required(VERSION 2.8.9)
set (CMAKE_CXX_STANDARD 11)
include_directories(header)
include_directories(src)
set( SOURCES
    src/Speect.cpp
    src/configuration.cpp
    src/utterance.cpp
    src/relation.cpp
    src/item.cpp
)
set( HEADER
    header/Speect.h
    header/configuration.h
    header/utterance.h
    header/relation.h
    header/item.h
)

# compile
add_library(Model ${SOURCES} ${HEADER})
target_include_directories (Model PUBLIC INCLUDE_DIRECTORIES)
target_link_libraries(Model)
