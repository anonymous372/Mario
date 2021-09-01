#include"Box.h"
//#include<SFML/Graphics.hpp>
Box::Box(sf::Texture* texture, sf::Vector2f size, sf::Vector2f pos) {
	box.setSize(size);
	box.setOrigin(size / 2.0f);
	box.setPosition(pos);																																										
	box.setTexture(texture);
}