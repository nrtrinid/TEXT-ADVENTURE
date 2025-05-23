cmake_minimum_required(VERSION 3.15)
project(TextAdventure)

set(CMAKE_CXX_STANDARD 17)

# Include header folders
include_directories(core entities menus)

# Gather all .cpp files
file(GLOB_RECURSE SOURCES
     core/*.cpp
     entities/*.cpp
     menus/*.cpp
     main/*.cpp)

# Create the executable
add_executable(text-adventure ${SOURCES})
