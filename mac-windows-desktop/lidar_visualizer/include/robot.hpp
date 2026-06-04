#ifndef ROBOT_H
#define ROBOT_H

#include <SFML/Graphics.hpp>
#include <math.h>

class robot{
public: 
	robot(float x); //constructor
	void draw(sf::RenderWindow& window);
	void set_position(float x, float y);
	void set_color(sf::Color color);
	void handle_input(float dt); 
	sf::Vector2f getPosition();
	float getRotation();
	void setRotation(float angle);
	float radiansToDegrees(float angle);

private:
	float size = 0;
	sf::CircleShape body;
	float speed = 200.0f;
	float robotAngle = 20.f;
};

#endif