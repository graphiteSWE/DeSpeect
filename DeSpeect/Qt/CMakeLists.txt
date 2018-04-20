cmake_minimum_required(VERSION 2.8.9)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set (CMAKE_CXX_STANDARD 11)
include_directories(header)
include_directories(ui)
include_directories(src)
set( SOURCES
        src/arc.cpp
	src/graphmanager.cpp
        src/id.cpp
        src/node.cpp
        src/line.cpp
        src/modelview.cpp
        src/processormanager.cpp
        src/view.ui
        )
set( HEADER
        header/arc.h
        header/graphmanager.h
        header/id.h
        header/modelview.h
        header/node.h
        header/line.h
        header/processormanager.h
)
set( MOC_HEADER
        mainwindow.moc
)
QT5_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )
QT5_WRAP_UI( UI_HEADERS ${UIS} )
QT5_WRAP_CPP( MOC_SRCS ${MOC_HEADERS} )

# compile
add_library(QTGraph ${SOURCES} ${HEADER})
target_include_directories (QTGraph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} INCLUDE_DIRECTORIES)
target_link_libraries( QTGraph ${Qt5Widgets_LIBRARIES} )
