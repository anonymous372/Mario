#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
using namespace std;
class stage
{
public:
	vector<sf::RectangleShape> ground;
	vector<sf::RectangleShape> sky;
	vector<sf::RectangleShape> crust;
	stage(sf::Texture* skyTexture,sf::Texture *groundTexture,sf::Texture *crustTexture,int count);
};

