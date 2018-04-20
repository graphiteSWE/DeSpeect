
set(spct_DIR ./../../SpeectInstaller/install/include/speect/engine)
include(${spct_DIR}/SpeectConf.cmake)
include_directories(${SPCT_INCLUDE_DIRS})

find_library(despeect libspct.so HINTS ${spct_DIR}/../../../lib)

add_executable(
    unit_tests
    Command_setspeectconfig.cpp
    )

target_link_libraries(
    unit_tests
    gtest_main
    Command
    SpeectWrapper
    ${despeect}
    )

add_test(
  NAME
    unit
  COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
  )
