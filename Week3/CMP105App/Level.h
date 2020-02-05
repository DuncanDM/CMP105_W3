#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;

	sf::CircleShape circle;
	sf::CircleShape contCircle;
	sf::CircleShape allCircle;

	sf::Font font;
	sf::Text text;

	float velocity;

	bool forward = true;

	bool boundaryT = false;
	bool boundaryL = false;
	bool boundaryR = false;
	bool boundaryB = false;

	float allVelocity;
	bool forwardX = true;
	bool forwardY = true;
};