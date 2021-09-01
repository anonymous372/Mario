#pragma once
#include<SFML/Graphics.hpp>
#include<vector>
#include"Animation.h"
#include"stage.h"
class monsters
{
public:
	Animation animation;
	int count;
	std::vector<sf::Vector2f> monsterPos;
	std::vector<sf::RectangleShape> monster;
	float totalTime;
	bool faceRight;
	float turnTime;
	monsters(sf::Texture* monsterTexture, sf::Vector2u imageCount, float switchtime,int count,stage st, float turnTime);
	void Draw(sf::RenderWindow& window) { for (int i = 0; i < count; i++) window.draw(monster[i]); }
	void Update(float deltaTime);
};

