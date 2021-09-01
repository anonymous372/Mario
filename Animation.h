#pragma once
#include<SFML/Graphics.hpp>
class Animation
{	
	sf::Vector2u imageCount;
	sf::Vector2u curImage;
	float totalTime,switchTime;
public:
	sf::IntRect uvRect;
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	void update(int row, float deltaTime,bool faceRight);
};

