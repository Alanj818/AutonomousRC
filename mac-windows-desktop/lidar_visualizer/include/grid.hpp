#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

class grid{
    public:
        enum class cellData{
            Obstacle,
            Free,
            Taken,
            Unknown
        };
        grid(float cell_size, sf::Vector2u window_size); 
        void drawGrid(sf::RenderWindow& window);
        void setCell(int x, int y, cellData state);
        void setCell(const std::vector<int>& x,const std::vector<int>& y, cellData state);
        sf::Vector2i lidarToGrid(float lidar_distance, int servo_angle, sf::Vector2f robot_position);
        void handleInput();
        void resetGrid();
    private:
        float cell_size;
        sf::Vector2u window_size;
        std::vector<std::vector<cellData>> cell_state;
};

#endif