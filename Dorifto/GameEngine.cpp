#include "GameEngine.h"

void GameEngine::initVariables()
{
	window = nullptr;
}

void GameEngine::initWindow()
{
	videoMode.height = 768;
	videoMode.width = 1366;

	window = new sf::RenderWindow(videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);
}

void GameEngine::initFonts()
{
	font.loadFromFile("D:/vs2022_code/proj/Dorifto/Fonts/JOY.otf");
}

void GameEngine::initText()
{
	uiText.setFont(font);
	uiText.setCharacterSize(12);
	uiText.setFillColor(sf::Color::White);
	uiText.setString("NONE");
}

GameEngine::GameEngine()
{
	initVariables();
	
	initWindow();

	initFonts();
	initText();
}

GameEngine::~GameEngine()
{
	delete window;
}

const bool GameEngine::running() const
{
	return window->isOpen();
}

void GameEngine::pollEvents()
{
	while (window->pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				window->close();
			break;
		}
	}
}

void GameEngine::updateMousePos()
{
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void GameEngine::updateText()
{
	std::stringstream ss;

	ss << "(x, y): (" << obj.getX() << ", " << obj.getY() << ")\n";
	ss << "(velX, velY): " << obj.getVelocityX() << ", " << obj.getVelocityY() << ")\n";
	ss << "(forceX, forceY): " << obj.getResultingForceX() << ", " << obj.getResultingForceY() << ")\n";

	this->uiText.setString(ss.str());
}

void GameEngine::update()
{
	pollEvents();
	updateText();
	obj.update();

	updateMousePos();
}

void GameEngine::renderText(sf::RenderTarget* target)
{
	target->draw(uiText);
}

void GameEngine::render()
{
	window->clear();

	obj.render(window);

	renderText(window);

	window->display();
}
