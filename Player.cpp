#include "Player.h"
//#include "Animation.h"
Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed,float jumpHeight) :
	animation(texture,imageCount,switchTime) 
{	
	hurt = false;
	lives = 3;
	state = 0;
	this->jumpHeight = jumpHeight;
	this->speed = speed;
	row = 1;
	faceRight = true;
	body.setSize(sf::Vector2f(100.0f, 190.0f));
	body.setOrigin(50, 80);
	body.setPosition(100.0f, -100.0f);
	body.setTexture(texture);
	canJump = true;
}

void Player::Update(float deltaTime)
{
	bool Running = false;
	velocity.x = 0.0f; 
	float gravity = 1300.0f;	
	//velocity.y *= 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		velocity.x -= speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		velocity.x += speed;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump) {
		canJump = false;
		velocity.y = -sqrtf(2.0f * gravity * jumpHeight);
	}
	//Special Jump
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump) {
		canJump = false;
		velocity.y = -sqrtf(2.0f * 2*gravity * jumpHeight);
	}
	//SPECIAL RUN
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
			velocity.x += (speed * 2.0f);
			Running = true;
		}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
			velocity.x -= (speed * 2.0f);
			Running = true;
		}
	velocity.y += gravity * deltaTime;
	if (velocity.x==0.0f) {
		row = 0;
	}
	else {
			if (Running)
				row = 2;
			else
				row = 1;
		if (velocity.x > 0) {
			faceRight = true;
		}
		else {
			faceRight = false;
		}
	}
	if (hurt) {
		state = 1;
		row = 5;
		Sleep(5);
	}
	else {
		if (state == 1) lives--;
		state = 0;
	}
	animation.update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::onCollision(sf::Vector2f direction,bool hurt)
{
	this->hurt = hurt;
	if (direction.x < 0.0f) {
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f) {
		velocity.x = 0.0f;
	}
	if (direction.y > 0.0f) {
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y < 0.0f) {
		velocity.y = 0.0f;
		canJump = true;
	}
}
