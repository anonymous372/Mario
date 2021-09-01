#pragma once
#include<SFML/Graphics.hpp>
class Collider {
public:
	bool CheckCollision(sf::RectangleShape& obj1, sf::RectangleShape& obj2,sf::Vector2f& direction, sf::Vector2f push);
};