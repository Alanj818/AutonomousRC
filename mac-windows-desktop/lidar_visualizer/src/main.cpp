#include <iostream>
#include <SFML/Graphics.hpp>
#include "robot.hpp"
#include "grid.hpp"

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "liDAR Visualizer");
    float cell_size = 7.f;
    float robot_size = 10.f;
    grid g(cell_size, window.getSize());
    robot r(robot_size);
    sf::Color color = sf::Color::Magenta;
    r.set_color(color);
    r.set_position(400.0f, 300.0f);
    sf::Clock clock;

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        //these are robot angle, robot position, and time values
        float robotAngle = r.getRotation();
        float dt = clock.restart().asSeconds();
        sf::Vector2f robotPos = r.getPosition();

        //these handle inputs on keyboard for now
        r.handle_input(dt);
        g.handleInput();
        
        //these configure the grid for robot position and a "fake" scan 100cm in front of the robot at all times, like if something is always in front of it 100cm
        g.setCell(static_cast<int>(robotPos.y / cell_size), static_cast<int>(robotPos.x / cell_size), grid::cellData::Taken);
        sf::Vector2i obstaclePos = g.lidarToGrid(100.f, static_cast<int>(robotAngle), robotPos);
        g.setCell(obstaclePos.y, obstaclePos.x, grid::cellData::Obstacle);

        //this just prints out the angle continuously for debugging reasons
        std::cout << robotAngle << std::endl;



        
        // clear the window with black color
        window.clear(sf::Color::Black);

        //this draws the robot and the grid
        g.drawGrid(window);
        r.draw(window);      

        // end the current frame
        window.display();
    }
}