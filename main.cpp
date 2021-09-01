#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<vector>
#include<Windows.h>
#include "Player.h"
#include"Box.h"
#include"Collider.h"
#include"coin.h"
#include"stage.h"
#include"monsters.h"
using namespace std;

sf::RenderWindow window(sf::VideoMode(800, 600), "My", sf::Style::Close | sf::Style::Resize);

static const float VIEW_HEIGHT = 800.0f,VIEW_WIDTH=600.0f;
void ResizeView(sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_WIDTH * aspectRatio, VIEW_HEIGHT);
}
string intToString(int a) {
	string s;
	s += 48 + a / 10;
	s +=a % 10+48;
	return s;
}
void main() {
	int stage_count = 10;
	int coinSetCount=15;
	int countCoin = 5;
	int tcoins = coinSetCount * countCoin;
	int monsterCount = 5;
	// COIN TEXT
	int coinsPicked = 0;
	sf::RectangleShape coin_outline(sf::Vector2f(170.0f,70.0f));
	coin_outline.setOutlineThickness(7);
	coin_outline.setOutlineColor(sf::Color(255, 215, 0));
	coin_outline.setFillColor(sf::Color::Transparent);
	sf::Text coinCount;
	sf::Font sm;
	sm.loadFromFile("SuperMario.ttf");
	coinCount.setFont(sm);
	coinCount.setCharacterSize(45);
	coinCount.setFillColor(sf::Color(255, 215, 0));
	coinCount.setString("Coins :"+intToString(coinsPicked));
	
	//START MENU
	while (window.isOpen()) {
		sf::RectangleShape button(sf::Vector2f(300.0f,150.0f));
		button.setOrigin(150.0f, 75.0f);
		button.setPosition(400.0f, 300.0f);

		sf::Texture buttonTexture;
		buttonTexture.loadFromFile("button.jpg");
		button.setTexture(&buttonTexture);
		while (1) {
			sf::Event e;
			while (window.pollEvent(e)) {
				if (e.type == e.Closed) {
					window.close();
				}
			}
			window.clear();
			window.draw(button);
			window.display();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
				if (mouse_pos.x > 250 && mouse_pos.x < 550 && mouse_pos.y>225 && mouse_pos.y < 375)
					goto lbl;
			}
		}
		break;
	}
	lbl:
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_WIDTH,VIEW_HEIGHT));

	sf::Texture groundTexture;
	groundTexture.loadFromFile("ground.jpg");
	sf::Texture skyTexture;
	skyTexture.loadFromFile("sky.jpg");
	sf::Texture crustTexture;
	crustTexture.loadFromFile("crust.jpg");


	// TEXTURES
	sf::RectangleShape pipe(sf::Vector2f(100.0f, 300.0f));
	pipe.setOrigin(50.0f, 150.0f);
	pipe.setPosition(50.0f,400.0f);
	sf::Texture pipeTexture;
	pipeTexture.loadFromFile("pipe.png");
	pipe.setTexture(&pipeTexture);

	sf::Texture playerTexture;
	playerTexture.loadFromFile("all_motion_copy.png");
	playerTexture.setSmooth(true);

	sf::Texture coinTexture;
	coinTexture.loadFromFile("coin.png");
	coinTexture.setSmooth(true);

	sf::Texture boxTexture;
	boxTexture.loadFromFile("box.jpg");
	boxTexture.setSmooth(true);
	
	sf::Texture monsterTexture;
	monsterTexture.loadFromFile("monster.png");
	monsterTexture.setSmooth(true);

	sf::RectangleShape heart(sf::Vector2f(40.0f, 40.0f));
	sf::Texture heartTexture;
	heartTexture.loadFromFile("heart.png");
	heart.setTexture(&heartTexture);

	// SOUNDS
	sf::SoundBuffer buffer;
	buffer.loadFromFile("super_mario.wav");
	sf::Sound music;
	music.setBuffer(buffer);
	music.setVolume(10);
	music.play();

	sf::SoundBuffer buffer2;
	buffer2.loadFromFile("coin_sound.wav");
	sf::Sound coin_sound;
	coin_sound.setVolume(10);
	coin_sound.setBuffer(buffer2);
			
	//CLASS MEMBERS
	Collider c;
	Player player(&playerTexture,sf::Vector2u(6, 6), 0.2f,130.0f,270.0f);
	
	coin cn(countCoin, sf::Vector2u(6, 1), &coinTexture, 0.1f, coinSetCount);
	Box box1(&boxTexture,sf::Vector2f(200.0f,200.0f),sf::Vector2f(600.0f,450.0f));
	Box box2(&boxTexture, sf::Vector2f(200.0f, 200.0f), sf::Vector2f(300.0f, 450.0f));
	Box box3(&boxTexture, sf::Vector2f(200.0f, 500.0f), sf::Vector2f(7000.0f, -100.0f));
	
	stage s(&skyTexture,&groundTexture,&crustTexture,stage_count);
	
	monsters mn(&monsterTexture,sf::Vector2u(5,1),0.24f,monsterCount,s,4.0f);

	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Clock time;
	bool face = true;

	// THE LOOOP
	float tm=0;
	bool flg=false;
	int brk = 0;
	while (window.isOpen()) {
		//break;
		deltaTime = clock.restart().asSeconds();
		tm = tm + (float)deltaTime;
		if (tm > 26.0f) {
			music.play();
			tm = 0.0f;
		}
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type==e.Closed) {
				window.close();
			}
			if (e.type == e.Resized) {
				ResizeView(view);
			}
		}
		// UPDATES
		player.Update(deltaTime);
		cn.Update(deltaTime);
		mn.Update(deltaTime);

		sf::Vector2f direction;

		if(c.CheckCollision(player.body, box1.box, direction, sf::Vector2f(1.0f,0.0f))) player.onCollision(direction, false);
		if(c.CheckCollision(player.body, box2.box, direction, sf::Vector2f(1.0f, 0.0f))) player.onCollision(direction, false);
		if (c.CheckCollision(box1.box, box2.box, direction, sf::Vector2f(1.0f, 1.0f))) player.onCollision(direction, false);
		if (c.CheckCollision(player.body, box3.box, direction, sf::Vector2f(1.0f, 0.0f))) player.onCollision(direction, false);
		if (c.CheckCollision(player.body, pipe, direction, sf::Vector2f(0.0f, 0.0f))) player.onCollision(direction, false);
		for(int j=0;j<cn.coinSetCount;j++)
		for (int i = 0; i < cn.count; i++)
			if (c.CheckCollision(player.body, cn.Coin[j][i], direction, sf::Vector2f(0.000001f, 0.000001f))) {
				if (!cn.isPicked[j][i]) {
					coin_sound.play();
					coinsPicked++;
					coinCount.setString("Coins :" + intToString(coinsPicked));
				}
				cn.isPicked[j][i] = true;
			}
		for (int i = 0; i < stage_count; i++) {
			if (c.CheckCollision(player.body, s.ground[i], direction, sf::Vector2f(0.0f, 0.0f))) player.onCollision(direction, false);
			if (c.CheckCollision(player.body, s.crust[i], direction, sf::Vector2f(0.0f, 0.0f))) player.onCollision(direction, false);
		}
		bool hurt = false;
		for (int i = 0; i < monsterCount; i++) {
			if (c.CheckCollision(player.body, mn.monster[i], direction, sf::Vector2f(0.000001f, 0.000001f)))
				hurt = true;
			if (c.CheckCollision(player.body, mn.monster[i], direction, sf::Vector2f(0.000001f, 0.000001f))) player.onCollision(direction, hurt);
		}
		
		
		view.setCenter(player.GetPosition().x, player.GetPosition().y - 100);

		coinCount.setPosition(player.GetPosition().x - 287.0f, player.GetPosition().y - 400.0f);
		coin_outline.setPosition(player.GetPosition().x - 290.0f, player.GetPosition().y - 400.0f);
		
		heart.setPosition(player.GetPosition().x + 250.0f, player.GetPosition().y - 400.0f);
		
		window.clear();
		window.setView(view);
		for (int i = 0; i < stage_count; i++)
			window.draw(s.sky[i]);
		for (int i = 0; i < stage_count; i++)
			window.draw(s.ground[i]);
		for (int i = 0; i < stage_count; i++)
			window.draw(s.crust[i]);
		box1.Draw(window);
		box2.Draw(window);
		box3.Draw(window);
		window.draw(pipe);
		cn.Draw(window);
		window.draw(coinCount);
		window.draw(coin_outline);
		for (int i = 0; i < player.lives; i++) {
			window.draw(heart);		
			heart.move(-45.0f, 0.0f);
		}
		mn.Draw(window);
		player.Draw(window);
		int cnt = 0;
		for (int j = 0; j < cn.coinSetCount; j++)
			for (int i = 0; i < cn.count; i++)
				if (cn.isPicked[j][i]) cnt++;
		window.display();
		if (player.lives == 0 || cnt == tcoins) {
			flg = true;
			tcoins = 0;
		}
		if (flg) brk++;
		if (brk == 50) break;
	}
	window.close();
	sf::RenderWindow w(sf::VideoMode(800, 600), "My", sf::Style::Close | sf::Style::Resize);
	sf::Text text;
	text.setFont(sm);
	if (player.lives>0) {
		text.setString("Congratulations !! \n\tYou Won");
		text.setCharacterSize(100);
		text.setPosition(50.0f, 200.0f);
		text.setFillColor(sf::Color::Green);
	}
	else {
		text.setString("\t\t\tOh No!!\n You Lost All Yours Lives");
		text.setCharacterSize(70);
		text.setPosition(3.0f, 200.0f);
		text.setFillColor(sf::Color::Red);
	}
	while (w.isOpen()) {
		if (tcoins) break;
		sf::Event e;
		while (w.pollEvent(e)) {
			if (e.type == e.Closed) {
				w.close();
			}
		}
		w.clear();
		w.draw(text);
		w.display();
	}
	
}

