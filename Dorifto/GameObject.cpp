#include "GameObject.h"

void GameObject::initVariables()
{
	height = 30.f; // Meters
	width = 30.f; // Meters
	force = 50.f; // Newtons
	mass = height * width * density * lengthUnits;
	std::cout << "mass: " << mass << "\n";
	speedX = 0.f, speedY = 0.f;
	normalForce = mass * 9.81f;
	std::cout << "normalForce: " << normalForce << "\n";
	std::cout << "frictionApprox: " << normalForce * muCoefficient << "\n";
	frictionX = 0.f, frictionY = 0.f;
	accelX = 0.f, accelY = 0.f;
	resultingForceX = 0.f, resultingForceY = 0.f;
}

void GameObject::initShape()
{
	shape.setFillColor(sf::Color::White);
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(sf::Vector2f(0.f, 0.f));
}

void GameObject::updateAccel()
{
	accelX = resultingForceX / mass;
	accelY = resultingForceY / mass;
}

void GameObject::updateSpeed()
{
	speedX = std::abs(speedX + accelX) <= 0.5f ? 0.f : speedX + accelX;
	speedY = std::abs(speedY + accelY) <= 0.5f ? 0.f : speedY + accelY;
}

void GameObject::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		resultingForceX += -force;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		resultingForceX += force;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		resultingForceY += -force;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		resultingForceY += force;
	}
}

void GameObject::updateFriction()
{
	frictionX = (std::abs(speedX) <= 0.5f && std::abs(speedY) <= 0.5f) ? 0.f : -speedX / std::sqrtf(speedX * speedX + speedY * speedY) * normalForce * muCoefficient;
	frictionY = (std::abs(speedX) <= 0.5f && std::abs(speedY) <= 0.5f) ? 0.f :  -speedY / std::sqrtf(speedX * speedX + speedY * speedY) * normalForce * muCoefficient;
	resultingForceX += frictionX;
	resultingForceY += frictionY;
}

void GameObject::updateForce()
{
	resultingForceX = 0.f, resultingForceY = 0.f;
	
	updateInput();
	updateFriction();

	/*std::cout << "Accel: " << accelX << " " << accelY << "\n";*/
}

void GameObject::updatePosition()
{
	x += speedX; y += speedY;
	shape.move(speedX, speedY);
}

GameObject::GameObject()
{
	initVariables();
	initShape();
}

GameObject::GameObject(float density) : density(density)
{
	initVariables();
	initShape();
}

GameObject::~GameObject()
{
}

float GameObject::getX()
{
	return x;
}

float GameObject::getY()
{
	return y;
}

float GameObject::getVelocityX()
{
	return speedX;
}

float GameObject::getVelocityY()
{
	return speedY;
}

float GameObject::getResultingForceX()
{
	return resultingForceX;
}

float GameObject::getResultingForceY()
{
	return resultingForceY;
}

void GameObject::update()
{
	updateForce();
	updateAccel();
	updateSpeed();
	updatePosition();
}

void GameObject::render(sf::RenderTarget* target)
{
	target->draw(shape);
}
