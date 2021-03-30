cmake_minimum_required(VERSION 3.5)
project(BBID)

add_library(BBID SHARED
    libBBID.cpp
    )


target_include_directories(BBID
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

