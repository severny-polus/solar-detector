set(CMAKE_PROJECT_NAME host)

project(${CMAKE_PROJECT_NAME})

file(GLOB SOURCES src/*.c)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
