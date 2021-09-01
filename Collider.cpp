#include "Collider.h"
#include<iostream>
bool Collider::CheckCollision(sf::RectangleShape& obj1, sf::RectangleShape& obj2, sf::Vector2f& direction,sf::Vector2f push)
{
	sf::Vector2f pos1 = obj1.getPosition();
	sf::Vector2f pos2 = obj2.getPosition();
	float deltax = pos1.x - pos2.x;
	float deltay =	pos1.y - pos2.y;
	float intersectx = abs(deltax) - (obj1.getSize().x/2.0f + obj2.getSize().x / 2.0f);
	float intersecty = abs(deltay) - (obj1.getSize().y / 2.0f + obj2.getSize().y / 2.0f);
	//std::cout << intersectx << " " << intersecty << "\t\t";
	if(intersectx < 0 && intersecty < 0) {
	
		if (intersectx < intersecty) {
			if (deltay < 0) {
				if (push.y == 0.0f) obj1.move(0.0f, -1.0f);
				obj1.move(0.0f, -push.y);
				obj2.move(0.0f, push.y);
				direction.x = 0.0f;
				direction.y = -1.0f;
			}
			else {
				if (push.y == 0.0f) obj1.move(0.0f, 1.0f);
				obj1.move(0.0f, push.y);
				obj2.move(0.0f, -push.y);
				direction.x = 0.0f;
				direction.y = 1.0f;
			}
		}
		else {
			if (deltax < 0) {
				if (push.x == 0.0f) obj1.move(-1.0f,0.0f);
				obj1.move(-push.x, 0.0f);
				obj2.move(push.x, 0.0f);
				direction.x = -1.0f;
				direction.y = 0.0f;
			}
			else {
				if (push.x == 0.0f) obj1.move(1.0f, 0.0f);
				obj1.move(push.x, 0.0f);
				obj2.move(-push.x, 0.0f);
				direction.x = 1.0f;
				direction.y = 0.0f;

			}
		}
		return true;
	}
	return false;
}

