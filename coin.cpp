#include "coin.h"

coin::coin(int count, sf::Vector2u imageCount, sf::Texture *texture,float switchTime,int coinSetCount) :
	animation(texture,imageCount,switchTime)
{
	this->count = count;
	this->coinSetCount = coinSetCount;

	for (int j = 0; j < coinSetCount; j++) {
		std::vector<bool> dum;
		for (int i = 0; i < count; i++) {
			dum.push_back(false);
		}
		isPicked.push_back(dum);
	}
	float dif = 100.0f;
	for (int i = 0; i < coinSetCount;i++) {
		difference.push_back(dif);
	}
	
	for (int i = 0; i < coinSetCount; i++) {
		sf::Vector2f dum(600.0f*i+100.0f,200-80.0f*i);
		coinPos.push_back(dum);
	}
	
	for (int i = 0; i < coinSetCount; i++) {
		std::vector<sf::RectangleShape> dum;
		for (int j = 0; j < count; j++) {
			sf::RectangleShape dummy;
			dummy.setSize(sf::Vector2f(60.0f, 60.0f));
			dummy.setOrigin(30.0f, 30.0f);
			dummy.setPosition(coinPos[i].x + difference[i]* (float)j, coinPos[i].y);
			dummy.setTexture(texture);
			dum.push_back(dummy);
		}
		Coin.push_back(dum);
	}
}
void coin::Update(float deltaTime) {
	int row = 0;
	animation.update(row, deltaTime, true);
	for(int j=0;j<coinSetCount;j++)
	for (int i = 0; i < count; i++) {
		Coin[j][i].setTextureRect(animation.uvRect);
	}
}
