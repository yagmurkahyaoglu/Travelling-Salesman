cmake_minimum_required(VERSION 2.8.2.12)
project(project3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.cpp
    Road.cpp
    Road.h
    Town.cpp
    Town.h)

add_executable(project3 ${SOURCE_FILES})