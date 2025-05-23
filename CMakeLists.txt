cmake_minimum_required(VERSION 3.15)
project(TextAdventure)

set(CMAKE_CXX_STANDARD 17)

# Include header folders
include_directories(
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/entities
    ${CMAKE_SOURCE_DIR}/menus
)

# Gather all .cpp and .h files recursively from source directories
file(GLOB_RECURSE SOURCES
     core/*.cpp
     core/*.h
     entities/*.cpp
     entities/*.h
     menus/*.cpp
     menus/*.h
     main/*.cpp
     main/*.h)


# Create the executable
add_executable(text-adventure ${SOURCES})
