#include "GameObject.h"

void GameObject::initVariables()
{
	height = 30.f;
	width = 100.f;
	wheelHeight = 5.f;
	wheelWidth = 20.f;

	x = width / 2;
	y = height / 2;
	carWheelAngle = 0.f;
	carForwardAngle = 0.f;
	
	force = 100.f; // Newtons
	lengthUnits = 1.f;
	muCoefficient = 0.5f;
	density = 1.f;
	
	mass = height * width * density * lengthUnits;
	normalForce = mass * 9.81f;
	
	speedX = 0.f, speedY = 0.f;
	
	frictionX = 0.f, frictionY = 0.f;
	accelX = 0.f, accelY = 0.f;
	resultingForceX = 0.f, resultingForceY = 0.f;

	std::cout << "mass: " << mass << "\n";
	std::cout << "normalForce: " << normalForce << "\n";
	std::cout << "frictionApprox: " << normalForce * muCoefficient << "\n";
}

void GameObject::initShapes()
{
	shape.setFillColor(sf::Color::White);
	shape.setSize(sf::Vector2f(width, height));
	shape.setOrigin(sf::Vector2f(width / 2, height / 2));
	shape.setPosition(sf::Vector2f(x, y));

	wheel.setFillColor(sf::Color::Red);
	wheel.setSize(sf::Vector2f(wheelWidth, wheelHeight));
	wheel.setOrigin(sf::Vector2f(wheelWidth / 2, wheelHeight / 2));
	wheel.setPosition(sf::Vector2f(x - width / 2 + wheelWidth / 2 + 3, y - height / 2 + wheelHeight / 2));
	rearWheels.push_back(wheel);
	wheel.setPosition(sf::Vector2f(x - width / 2 + wheelWidth / 2 + 3, y + height / 2 - wheelHeight / 2));
	rearWheels.push_back(wheel);

	wheel.setPosition(sf::Vector2f(x + width / 2 - wheelWidth / 2 - 3, y - height / 2 + wheelHeight / 2));
	frontWheels.push_back(wheel);
	wheel.setPosition(sf::Vector2f(x + width / 2 - wheelWidth / 2 - 3, y + height / 2 - wheelHeight / 2));
	frontWheels.push_back(wheel);

}

void GameObject::updateAccel()
{
	accelX = resultingForceX / mass;
	accelY = resultingForceY / mass;
}

void GameObject::updateSpeed()
{
	speedX += accelX;
	speedY += accelY;
}

void GameObject::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		carWheelAngle = (carWheelAngle + 0.5f <= 20.f) ? carWheelAngle + 0.5f : carWheelAngle;
		frontWheels[0].setRotation(carWheelAngle + carForwardAngle);
		frontWheels[1].setRotation(carWheelAngle + carForwardAngle);
		std::cout << carWheelAngle << "\n";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		carWheelAngle = (carWheelAngle - 0.5f >= -20.f) ? carWheelAngle - 0.5f: carWheelAngle;
		frontWheels[0].setRotation(carWheelAngle + carForwardAngle);
		frontWheels[1].setRotation(carWheelAngle + carForwardAngle);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		resultingForceX = std::cos((carWheelAngle + carForwardAngle) * 3.1415f / 180.f) * force;
		resultingForceY = std::sin((carWheelAngle + carForwardAngle) * 3.1415f / 180.f) * force;
		//carForwardAngle = carWheelAngle == 0.f ? 0.f : carForwardAngle + 0.5f * carWheelAngle / std::abs(carWheelAngle);
	}
	carForwardAngle = carForwardAngle + carWheelAngle;
	shape.setRotation(carForwardAngle);
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
	//updateFriction();

	/*std::cout << "Accel: " << accelX << " " << accelY << "\n";*/
}

void GameObject::updatePosition()
{
	x += speedX; y += speedY;
	shape.move(speedX, speedY);
	for (auto& z : frontWheels) { 
		z.move(speedX, speedY);
		z.setRotation(carWheelAngle + carForwardAngle);

	}
	for (auto& z : rearWheels) {
		z.move(speedX, speedY);
		z.setRotation(carForwardAngle);
	}
	
}

GameObject::GameObject()
{
	initVariables();
	initShapes();
}

GameObject::GameObject(float density) : density(density)
{
	initVariables();
	initShapes();
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
	for (auto& x : rearWheels) target->draw(x);
	for (auto& x : frontWheels) target->draw(x);
}
