#pragma once
#define _CRT_SECURE_NO_WARNINGS 1

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include"Bg.h"


class game
{
private:
	sf::RenderWindow* window;
	std::map<std::string, sf::Texture*> textures;

	std::vector<Bg> Backgrounds;
	sf::Sprite worldBackground;
	sf::Texture worldBackgroundTex;
	void initWorld();
	void initWindow();


public:
	game();
	virtual ~game();
	void run();
	void updatePollEvents();
	void update();
	void updateWorld();
	void render();
};

