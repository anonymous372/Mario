#include "monsters.h"

monsters::monsters(sf::Texture* monsterTexture, sf::Vector2u imageCount, float switchTime, int count,stage st,float turnTime):
	animation(monsterTexture, imageCount, switchTime)
{
	faceRight = true;
	this->count = count;
	this->turnTime = turnTime;
	for (int i = 0; i < count; i++) {
		sf::Vector2f v
		(st.ground[i + 3].getPosition().x-200.0f,
		st.ground[i + 3].getPosition().y-st.ground[i + 3].getSize().y/2.0f-100.0f);
		monsterPos.push_back(v);
	}
	for (int i = 0; i < count; i++) {
		sf::RectangleShape dum;
		dum.setTexture(monsterTexture);
		dum.setSize(sf::Vector2f(100.0f, 200.0f));
		dum.setOrigin(sf::Vector2f(50.0f, 100.0f));
		dum.setPosition(monsterPos[i]);
		monster.push_back(dum);
	}
}

void monsters::Update(float deltaTime)
{
	int row = 0;
	float movex = 0.13f;
	if (totalTime < turnTime) {
		totalTime += deltaTime;
		
		if (!faceRight) movex = -movex;

			for (int i = 0; i < count; i++){
				monster[i].move(movex,0.0f);
			}
	}
	else{
		totalTime -= turnTime;
		faceRight = !faceRight;
	}
	animation.update(row, deltaTime, faceRight);
	for (int i = 0; i < count; i++) {
		monster[i].setTextureRect(animation.uvRect);
	}
}