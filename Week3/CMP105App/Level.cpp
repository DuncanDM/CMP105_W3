#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects

	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font\n";
	}

	circle.setRadius(20);
	circle.setPosition(100, 100);
	circle.setFillColor(sf::Color::Blue);
	circle.setOutlineColor(sf::Color::White);
	circle.setOutlineThickness(3.f);

	contCircle.setRadius(20);
	contCircle.setPosition(100, 400);
	contCircle.setFillColor(sf::Color::Red);
	contCircle.setOutlineColor(sf::Color::White);
	contCircle.setOutlineThickness(3.f);

	allCircle.setRadius(20);
	allCircle.setPosition(400, 400);
	allCircle.setFillColor(sf::Color::Green);
	allCircle.setOutlineColor(sf::Color::White);
	allCircle.setOutlineThickness(3.f);

	velocity = 250.f;
	allVelocity = velocity;

	text.setFont(font);
	text.setString("allCircle Velocity: ");
	text.setCharacterSize(24);
	text.setFillColor(sf::Color::Red);
	text.setPosition(0, 0);
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	//contCircle Controls
	if (input->isKeyDown(sf::Keyboard::Up) && boundaryT == false)
	{
		contCircle.move(0, -velocity * dt);
	}

	if (input->isKeyDown(sf::Keyboard::Down) && boundaryB == false)
	{
		contCircle.move(0, velocity * dt);
	}

	if (input->isKeyDown(sf::Keyboard::Right) && boundaryR == false)
	{
		contCircle.move(velocity * dt, 0);
	}

	if (input->isKeyDown(sf::Keyboard::Left) && boundaryL == false)
	{
		contCircle.move(-velocity * dt, 0);
	}

	//allCircle Velocity
	if (input->isKeyDown(sf::Keyboard::Dash) && allVelocity > 0.f)
	{
		allVelocity--;
	}

	if (input->isKeyDown(sf::Keyboard::Equal) && allVelocity < 2500.f)
	{
		allVelocity++;
	}
}

// Update game objects
void Level::update(float dt)
{
	sf::Vector2f circlePos = circle.getPosition();
	sf::Vector2f contCirclePos = contCircle.getPosition();
	sf::Vector2f allCirclePos = allCircle.getPosition();

	sf::Vector2u winSize = window->getSize();

	//Side to Side Circle
	if (circlePos.x >= winSize.x - 40)
	{
		forward = false;
	}
	else if (circlePos.x <= 0)
	{
		forward = true;
	}

	if (forward == true)
	{
		circle.move(velocity * dt, 0);
	}
	else
	{
		circle.move(-velocity * dt, 0);
	}

	//Controllable Circle
	//Right-side of screen
	if (contCirclePos.x >= winSize.x - 40)
	{
		boundaryR = true;
	}
	else
	{
		boundaryR = false;
	}
	//Left-side of screen
	if (contCirclePos.x <= 0)
	{
		boundaryL = true;
	}
	else
	{
		boundaryL = false;
	}
	//Bottom of screen
	if (contCirclePos.y >= winSize.y - 40)
	{
		boundaryB = true;
	}
	else
	{
		boundaryB = false;
	}
	//Top of screen
	if (contCirclePos.y <= 0)
	{
		boundaryT = true;
	}
	else
	{
		boundaryT = false;
	}

	//All Directions Circle
	if (allCirclePos.x >= winSize.x - 40)
	{
		forwardX = false;
	}
	else if (allCirclePos.x <= 0)
	{
		forwardX = true;
	}

	if (allCirclePos.y >= winSize.y - 40)
	{
		forwardY = false;
	}
	else if (allCirclePos.y <= 0)
	{
		forwardY = true;
	}

	if (forwardX == true)
	{
		allCircle.move(allVelocity * dt, 0);
	}
	else
	{
		allCircle.move(-allVelocity * dt, 0);
	}

	if (forwardY == true)
	{
		allCircle.move(0, allVelocity * dt);
	}
	else
	{
		allCircle.move(0 , -allVelocity * dt);
	}

	int outVelocity = allVelocity;

	std::string output("allCircle Velocity: " + std::to_string(outVelocity));
	text.setString(output);
}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(circle);
	window->draw(contCircle);
	window->draw(allCircle);
	window->draw(text);

	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color::Black);
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}