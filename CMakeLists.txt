cmake_minimum_required(VERSION 3.28)
project(markov_names)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(markov_names
        CRandomName.cpp
        CRandomName.h
        CWordFrequency.cpp
        CWordFrequency.h
        main.cpp)
