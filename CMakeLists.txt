cmake_minimum_required(VERSION 3.29)

include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

project(solar-detector)

pico_sdk_init()
enable_language(C CXX)

file(GLOB SOURCES src/*.c)
add_executable(solar-detector ${SOURCES})

# pull in common dependencies
target_link_libraries(solar-detector pico_stdlib)

# create map/bin/hex file etc.
pico_add_extra_outputs(solar-detector)

# add url via pico_set_program_url
# example_auto_set_url(blink)