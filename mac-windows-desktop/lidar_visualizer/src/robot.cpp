#include "robot.hpp"

robot::robot(float x){
	size = x; 
	this->robotAngle = 0.f;
	sf::Angle angle = sf::degrees(robotAngle);
	body.setRadius(size);
	body.setOrigin({body.getRadius(), body.getRadius()});
	body.setRotation(angle);
}

void robot::draw(sf::RenderWindow& window){
	window.draw(body);
}

void robot::set_color(sf::Color color){
	body.setFillColor(color);
}

void robot::set_position(float x, float y){
	body.setPosition({x, y});
}

void robot::handle_input(float dt){
	sf::Vector2f movement({0.0f, 0.0f});
	float angularSpeed = 270.f;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)){
		movement.x += speed * dt * cos(radiansToDegrees(robotAngle));
		movement.y -= speed * dt * sin(radiansToDegrees(robotAngle));
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)){
		movement.x -= speed * dt * cos(radiansToDegrees(robotAngle)); 
		movement.y += speed * dt * sin(radiansToDegrees(robotAngle));
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)){
		robotAngle += angularSpeed * dt;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)){
		robotAngle -= angularSpeed * dt;
	}
	robotAngle = std::fmod(robotAngle, 360.f);

	if(robotAngle < 0.f)
	{
		robotAngle += 360.f;
	}

	setRotation(robotAngle);
	body.move(movement);

}

sf::Vector2f robot::getPosition(){
	return body.getPosition();
}

float robot::getRotation(){
	return robotAngle;
}

void robot::setRotation(float angle){
	sf::Angle newAngle = sf::degrees(angle);
	body.setRotation(newAngle);
}

float robot::radiansToDegrees(float angle){
	return angle * (M_PI / 180.f);
}