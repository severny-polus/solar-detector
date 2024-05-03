set(CMAKE_PROJECT_NAME host)

project(${CMAKE_PROJECT_NAME})

file(GLOB SOURCES src/*.c)

add_executable(host src/main.c)
add_library(detector STATIC src/detector.c src/detector.h)
target_link_libraries(host detector)

