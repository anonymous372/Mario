#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include"Collider.h"
#include<Windows.h>

class Player{
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	float jumpHeight;
	sf::Vector2f velocity;
	bool canJump; 
	bool hurt;
	int state;
public:
	int lives;

	sf::RectangleShape body;
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime,float speed,float jumpHeight);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition() {return body.getPosition(); }
	sf::RectangleShape getbody() { return body; }
	void onCollision(sf::Vector2f direction,bool hurt);
};

