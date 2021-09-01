#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include"Animation.h"
class coin
{
public:
	std::vector<std::vector<bool>> isPicked;
	int count;
	int coinSetCount;
	std::vector <std::vector<sf::RectangleShape> > Coin;
	std::vector<float> difference;
	std::vector <sf::Vector2f> coinPos;
	Animation animation;
public:
	coin(int count, sf::Vector2u imageCount, sf::Texture *texture,float switchTime,int coinSetCount);
	void Draw(sf::RenderWindow& window) { 
		for (int j = 0; j < coinSetCount; j++) 
			for (int i = 0; i < count; i++) 
				if (!isPicked[j][i]) window.draw(Coin[j][i]); 
	}
	void Update(float deltaTime);
};

