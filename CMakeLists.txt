cmake_minimum_required(VERSION 3.15)
project(TextAdventure)

set(CMAKE_CXX_STANDARD 17)

# Include base source folder
include_directories(${CMAKE_SOURCE_DIR})

# Gather all .cpp and .h files recursively from source directories
file(GLOB_RECURSE SOURCES
     core/*.cpp core/*.h
     entities/*.cpp entities/*.h
     equipment/*.cpp equipment/*.h
     systems/*.cpp systems/*.h
     menus/*.cpp menus/*.h
     effects/*.cpp effects/*.h
     items/*.cpp items/*.h
     skills/*.cpp skills/*.h
     commands/*.cpp commands/*.h
     main/*.cpp main/*.h)


# Create the executable
add_executable(text-adventure ${SOURCES})

# Equipment test harness (loose file in root)
add_executable(equipment_test equipment_test.cpp)
target_include_directories(equipment_test PRIVATE ${CMAKE_SOURCE_DIR})