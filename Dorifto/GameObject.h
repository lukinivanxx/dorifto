#pragma once

#include<iostream>
#include<sstream>

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
	float height, width, density = 10.f;
	float lengthUnits = 0.01f;
	//Parameters
	float x, y; // coords of the centre of mass
	float mass;
	float muCoefficient = 0.01f;
	float speedX, speedY; // projections of the speed on the standart cartesian axes
	float normalForce;
	float frictionX, frictionY;
	float force;
	float accelX, accelY;
	float resultingForceX, resultingForceY;

	//Private funcs
	void initVariables();
	void initShape();

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

