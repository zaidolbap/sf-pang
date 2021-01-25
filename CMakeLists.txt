cmake_minimum_required(VERSION 3.12)

project(pang 
    VERSION 0.1.0
    DESCRIPTION "A vertical version of pong"
    LANGUAGES CXX
)

add_subdirectory(libs/pang_lib)

add_subdirectory(apps)
