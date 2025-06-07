cmake_minimum_required(VERSION 3.15)
project(TextAdventure)

set(CMAKE_CXX_STANDARD 17)

# Include base source folder
include_directories(${CMAKE_SOURCE_DIR})

# Gather all .cpp and .h files recursively from source directories
# Recursively gather all .cpp and .h files
file(GLOB_RECURSE SOURCES
    core/*.cpp core/*.h
    commands/*.cpp commands/*.h
    effects/*.cpp effects/*.h
    entities/*.cpp entities/*.h
    equipment/*.cpp equipment/*.h
    items/*.cpp items/*.h
    main/*.cpp main/*.h
    menus/*.cpp menus/*.h
    skills/*.cpp skills/*.h
    systems/*.cpp systems/*.h)

# Main executable
add_executable(text-adventure ${SOURCES})
