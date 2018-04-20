cmake_minimum_required(VERSION 2.8.9)

## installer deve settare spct_DIR alla cartella dell'engine
set(spct_DIR ./../SpeectInstaller/install/include/speect/engine)

## install Test
# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

include(../test-framework/cmake/googletest.cmake)
fetch_googletest(
  ${CMAKE_SOURCE_DIR}/../test-framework/cmake
  ${CMAKE_SOURCE_DIR}/../test-framework/build
)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")

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

## aggiunta Test
enable_testing()
add_subdirectory(Test)

## creazione eseguibile
add_executable(main main.cpp)

find_library(despeect libspct.so HINTS ${spct_DIR}/../../../lib)
target_link_libraries( main ${Qt5Widgets_LIBRARIES} QTGraph SpeectWrapper Command ${despeect})
