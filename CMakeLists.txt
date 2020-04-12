cmake_minimum_required(VERSION 3.15)
project(Assignment_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(ncurses_lib)

add_executable(Assignment_2
        ncurses_lib/curses.h
        ncurses_lib/panel.h
        Controller.cpp
        Controller.h
        definition.h
        Employee.h
        main.cpp
        Object.cpp
        Object.h
        Property.h
        Scene.h
        test.cpp
        TodoCattlefarm.cpp
        TodoCattlefarm.h
        TodoCow.cpp
        TodoCow.h
        TodoEmployee.cpp
        TodoFarmer.cpp
        TodoFarmer.h
        TodoFarmland.cpp
        TodoFarmland.h
        TodoFeeder.cpp
        TodoFeeder.h
        TodoProperty.cpp
        TodoScene.cpp
        View.cpp
        View.h)
