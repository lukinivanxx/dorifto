#pragma once

#include "GameObject.h"

class GameEngine
{
private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;
	//Mouse pos
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	//Game logic
	/*uint64_t tick;*/

	//Game objects
	GameObject obj;

	//Resources
	sf::Font font;

	//Text
	sf::Text uiText;

	//Private functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
public:
	// Constructors / Destructors
	GameEngine();
	~GameEngine();
	//Accessors
	const bool running() const;
	//Functions
	void pollEvents();
	void updateMousePos();
	void updateText();
	void update();

	void renderText(sf::RenderTarget* target);
	void render();
};

