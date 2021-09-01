#include "Animation.h"
Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime) {
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	curImage.x = 0;
	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}
void Animation::update(int row, float deltaTime,bool faceRight) {
	curImage.y = row;
	totalTime += deltaTime;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		curImage.x++;
		if (curImage.x >= imageCount.x) {
			curImage.x = 0;
		}
	}
	uvRect.top = curImage.y * uvRect.height;
	if (faceRight) {
		uvRect.left = curImage.x * uvRect.width;
		uvRect.width = abs(uvRect.width);
	}
	else {
		uvRect.left = (curImage.x+1) * abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);
	}
}