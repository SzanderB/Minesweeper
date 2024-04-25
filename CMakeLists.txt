cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Project3)

add_executable(Project3 main.cpp
        Board.cpp
        Board.h
        Tile.cpp
        Tile.h
        TextureManager.cpp
        TextureManager.h
        Random.cpp
        Random.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include/SFML)
target_link_libraries(Project3 sfml-system sfml-window sfml-graphics sfml-audio)