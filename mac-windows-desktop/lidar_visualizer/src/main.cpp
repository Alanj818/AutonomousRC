#include <iostream>
#include <SFML/Graphics.hpp>
#include "robot.hpp"
#include "grid.hpp"
#include "Wifi.hpp"

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "liDAR Visualizer");

    //variables
    float cell_size = 7.f;
    float robot_size = 10.f;

    //objects
    grid g(cell_size, window.getSize());
    robot r(robot_size);
    Wifi w;
    sf::Clock clock;
    sf::Color color = sf::Color::Magenta;

    r.set_color(color);
    r.set_position(400.0f, 300.0f);
    
    float robotAngle = 0.f;
    float dt = 0.f;
    sf::Vector2f robotPos = {0.f, 0.f};
    sf::Vector2i obstaclePos = {0, 0};

    //Start up Wifi
    w.begin();
    w.startCon();
    
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

        //this will listen to wifi packets
        w.udp_listen();
        float distance = static_cast<float>(w.getDistance());

        //these are robot angle, robot position, and time values
        robotAngle = r.getRotation();
        dt = clock.restart().asSeconds();
        robotPos = r.getPosition();

        //these handle inputs on keyboard for now
        r.handle_input(dt);
        g.handleInput();
        
        //these configure the grid for robot position and a "fake" scan 100cm in front of the robot at all times, like if something is always in front of it 100cm
        obstaclePos = g.lidarToGrid(distance, static_cast<int>(robotAngle), robotPos);
        //obstaclePos = g.lidarToGrid(100.f, static_cast<int>(robotAngle), robotPos);
        g.setCell(obstaclePos.y, obstaclePos.x, grid::cellData::Obstacle);
        g.setCell(static_cast<int>(robotPos.y / cell_size), static_cast<int>(robotPos.x / cell_size), grid::cellData::Taken);

        //this just prints out the angle continuously for debugging reasons
        //std::cout << robotAngle << std::endl;




        // clear the window with black color
        window.clear(sf::Color::Black);

        //this draws the robot and the grid
        g.drawGrid(window);
        r.draw(window);      

        // end the current frame
        window.display();
    }
    
    w.endCon();
}