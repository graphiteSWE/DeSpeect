set(spct_DIR ./../../SpeectInstaller/install/include/speect/engine)
include(${spct_DIR}/SpeectConf.cmake)
include_directories(${SPCT_INCLUDE_DIRS})
find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDES})
add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set (ui ../Qt/src/view.ui)

QT5_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )
QT5_WRAP_UI( UI_HEADERS ${ui} )
QT5_WRAP_CPP( MOC_SRCS ${MOC_HEADERS} )

find_library(despeect libspct.so HINTS ${spct_DIR}/../../../lib)
########################################################################Speect_config
add_executable(
    Speect_config
    Command_setspeectconfig.cpp
    )

target_link_libraries(
    Speect_config
    gtest_main
    Command
    SpeectWrapper
    ${despeect}
    )
add_test(
    NAME
        Speect_config
    COMMAND
        Speect_config
    )
########################################################################Relation_Name
add_executable(
    Relation_Name
    Relation_Name.cpp
    )

target_link_libraries(
    Relation_Name
    gtest_main
    Command
    SpeectWrapper
    ${despeect}
    )
add_test(
    NAME
        Relation_Name
    COMMAND
        Relation_Name
    )
########################################################################Item_Name
add_executable(
    Item_Name
    Item_Name.cpp
    )

target_link_libraries(
    Item_Name
    gtest_main
    Command
    SpeectWrapper
    ${despeect}
    )
add_test(
    NAME
        Item_Name
    COMMAND
        Item_Name
    )
########################################################################
add_executable(
    LoadPlugin
    Command_loadplugin.cpp
    )

target_link_libraries(
    LoadPlugin
    gtest_main
    Command
    SpeectWrapper
    ${despeect}
    )
add_test(
    NAME
        LoadPlugin
    COMMAND
        LoadPlugin
    )
########################################################################
add_executable(
    Utterance_Name
    Utterance_Name.cpp
    )

target_link_libraries(
    Utterance_Name
    gtest_main
    Command
    SpeectWrapper
    ${despeect}
    )
add_test(
    NAME
        Utterance_Name
    COMMAND
        Utterance_Name
    )

########################################################################
add_executable(
    Command_createaudio
    Command_createaudio.cpp
    )

target_link_libraries(
    Command_createaudio
    gtest_main
    Command
    SpeectWrapper
    ${despeect}
    )
add_test(
    NAME
        Command_createaudio
    COMMAND
        Command_createaudio
    )
########################################################################
add_executable(
    Command_getuttname
    Command_getuttname.cpp
    )

target_link_libraries(
    Command_getuttname
    gtest_main
    Command
    SpeectWrapper
    ${despeect}
    )
add_test(
    NAME
        Command_getuttname
    COMMAND
        Command_getuttname
    )

########################################################################
add_executable(
    View_graphprint
    ModelView_graphprint.cpp
    ${ui}
    )

target_link_libraries(
    View_graphprint
    ${Qt5Widgets_LIBRARIES}
    QTGraph
    gtest_main
    Command
    SpeectWrapper
    ${despeect}
    )
add_test(
    NAME
        View_graphprint
    COMMAND
        View_graphprint
    )

########################################################################
add_executable(
    View_idTest
    View_idTest.cpp
    )

target_link_libraries(
    View_idTest
    QTGraph
    gtest_main
    ${despeect}
    )
add_test(
    NAME
       View_idTest
    COMMAND
        View_idTest
    )

########################################################################
add_executable(
    View_arcTest
    View_arcTest.cpp
    )

target_link_libraries(
    View_arcTest
    ${Qt5Widgets_LIBRARIES}
    QTGraph
    gtest_main
    Command
    SpeectWrapper
    ${despeect}
    )
add_test(
    NAME
       View_arcTest
    COMMAND
       View_arcTest
    )

########################################################################
add_executable(
    View_nodeTest
    View_nodeTest.cpp
    )

target_link_libraries(
    View_nodeTest
    ${Qt5Widgets_LIBRARIES}
    QTGraph
    gtest_main
    Command
    SpeectWrapper
    ${despeect}
    )
add_test(
    NAME
       View_nodeTest
    COMMAND
       View_nodeTest
    )

########################################################################
add_executable(
    View_dataNodeManagerTest
    View_dataNodeManagerTest.cpp
    )

target_link_libraries(
    View_dataNodeManagerTest
    ${Qt5Widgets_LIBRARIES}
    QTGraph
    gtest_main
    Command
    SpeectWrapper
    ${despeect}
    )
add_test(
    NAME
       View_dataNodeManagerTest
    COMMAND
       View_dataNodeManagerTest
    )

########################################################################
add_executable(
    SpeectWrapper_Speect
    SpeectWrapper_Speect.cpp
    )

target_link_libraries(
    SpeectWrapper_Speect
    ${Qt5Widgets_LIBRARIES}
    QTGraph
    gtest_main
    Command
    SpeectWrapper
    ${despeect}
    )
add_test(
    NAME
       SpeectWrapper_Speect
    COMMAND
       SpeectWrapper_Speect
    )

########################################################################
add_executable(
    View_lineTest
    View_lineTest.cpp
    )

target_link_libraries(
    View_lineTest
    ${Qt5Widgets_LIBRARIES}
    QTGraph
    gtest_main
    Command
    SpeectWrapper
    ${despeect}
    )
add_test(
    NAME
       View_lineTest
    COMMAND
       View_lineTest
    )

########################################################################
add_executable(
    SpeectWrapper_relation
    SpeectWrapper_relation.cpp
    )

target_link_libraries(
    SpeectWrapper_relation
    ${Qt5Widgets_LIBRARIES}
    QTGraph
    gtest_main
    Command
    SpeectWrapper
    ${despeect}
    )
add_test(
    NAME
       SpeectWrapper_relation
    COMMAND
       SpeectWrapper_relation
    )
