cmake_minimum_required(VERSION 3.5)

project(EveryoneIsHere LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(EveryoneIsHere main.cpp)

install(TARGETS EveryoneIsHere
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
