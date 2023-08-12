#pragma once

#include<iostream>
#include<sstream>
#include<vector>

#include<SFML/Graphics.hpp>
#include<SFML/Network.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>

// SI system used
// Newtonian physics

class GameObject
{
private:
	//Fixed parameters
	sf::RectangleShape shape;
	sf::RectangleShape wheel;
	std::vector<sf::RectangleShape> frontWheels;
	std::vector<sf::RectangleShape> rearWheels;
	float height, width, density;
	float wheelHeight, wheelWidth;
	float lengthUnits;
	//Parameters
	float x, y; // coords of the centre of mass
	float mass;
	float muCoefficient;
	float speedX, speedY; // projections of the speed on the standart cartesian axes
	float normalForce;
	float frictionX, frictionY;
	float force; // parameter of car engine
	float accelX, accelY;
	float resultingForceX, resultingForceY;

	float carForwardAngle; // the rotation of the car respectively to the grid
	float carRotationIncrement;

	float carWheelAngle; // 30 degrees on average

	//Private funcs
	void initVariables();
	void initShapes();

	//Updaters
	void updateAccel();
	void updateSpeed();
	void updateInput();
	void updateFriction();
	void updateForce();
	void updatePosition();
public:
	//Constructors / Destructor
	GameObject();
	GameObject(float density);
	~GameObject();
	
	//Setters
	
	//Getters
	float getX();
	float getY();
	float getVelocityX();
	float getVelocityY();
	float getResultingForceX();
	float getResultingForceY();

	//Public funcs
	void update();
	void render(sf::RenderTarget* target);
};

