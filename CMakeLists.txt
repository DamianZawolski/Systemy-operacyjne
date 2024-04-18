cmake_minimum_required(VERSION 3.28)
project(Systemy_operacyjne)

set(CMAKE_CXX_STANDARD 14)

add_executable(Systemy_operacyjne
        Projekt/main.cpp
        Projekt/road.h
        Projekt/road.cpp
        Projekt/car.cpp)

add_library()