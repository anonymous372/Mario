#pragma once
#include<SFML/Graphics.hpp>
class Box{
public:
	sf::RectangleShape box;
	Box(sf::Texture* texture, sf::Vector2f size, sf::Vector2f pos);
	sf::RectangleShape getbody() { return box; }
	void Draw(sf::RenderWindow& window) { window.draw(box);}
};