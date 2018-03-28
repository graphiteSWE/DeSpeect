cmake_minimum_required(VERSION 2.8.9)

## installer deve settare spct_DIR alla cartella dell'engine
set(spct_DIR ./../SpeectInstaller/install/include/speect/engine)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

## aggiunta Speect

include(${spct_DIR}/SpeectConf.cmake)
include_directories(${SPCT_INCLUDE_DIRS})

## aggiunta Modello
add_subdirectory(Model)
include_directories(Model/SpeectWrapper/header)
include_directories(Model/Command/header)

## aggiunta QT
add_subdirectory(Qt)
include_directories(Qt/header)

## creazione eseguibile
add_executable(main main.cpp)

find_library(despeect libspct.so HINTS ${spct_DIR}/../../../lib)
target_link_libraries( main ${Qt5Widgets_LIBRARIES} QTGraph SpeectWrapper Command ${despeect})
