#include "Game.h"
void game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("d:/uni/project/wallpaper/city/City1_bright.png"))
	{
		std::cout << "error::game::could not load background texture" << "\n";

	}

	this->worldBackground.setTexture(this->worldBackgroundTex);
	Backgrounds.push_back(Bg(&worldBackgroundTex, -30.f));
}
void game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1440, 1080), "test", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}
void game::updatePollEvents()
{
	sf::Event e;
	while (this->window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			this->window->close();
		if (e.KeyPressed && e.key.code == sf::Keyboard::Escape)
			this->window->close();

	}
}
game::game()
{
	this->initWindow();
	this->initWorld();
}
game::~game()
{


}
void game::run()
{

	while (this->window->isOpen())
	{



		this->updatePollEvents();
		this->window->display();


	}
}
void game::update()
{
	//this->updateworld();
}




void game::render()
{

	this->window->clear();

	for (Bg& background : Backgrounds)
		background.Draw(*window);




	this->window->display();

}


