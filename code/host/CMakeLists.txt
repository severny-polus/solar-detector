cmake_minimum_required(VERSION 3.29)

set(CMAKE_PROJECT_NAME host)

project(${CMAKE_PROJECT_NAME})

file(GLOB SOURCES src/*)

add_executable(host ${SOURCES})

