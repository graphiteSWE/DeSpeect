cmake_minimum_required(VERSION 2.8.9)
set (CMAKE_CXX_STANDARD 11)
set(MODEL_INCLUDE_DIRS
    ${YOUR_DIRECTORY}/SpeectWrapper/include
    ${YOUR_DIRECTORY}/Command/include
    )
add_subdirectory(SpeectWrapper)
add_subdirectory(Command)
