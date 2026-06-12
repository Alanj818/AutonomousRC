cmake_minimum_required(VERSION 3.28)

project(lidar_visualizer)

add_executable(lidar_visualizer)

target_sources(lidar_visualizer
    PRIVATE
        src/main.cpp
        src/robot.cpp
        src/grid.cpp
        src/Wifi.cpp
    PUBLIC 
        include/robot.hpp
        include/grid.hpp
        include/Wifi.hpp
)

target_include_directories(lidar_visualizer
    PRIVATE
        include
)

find_package(SFML REQUIRED COMPONENTS Graphics Window)

target_link_libraries(lidar_visualizer
    PRIVATE
        SFML::Graphics
        SFML::Window 
)