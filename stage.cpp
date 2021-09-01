#include "stage.h"
stage::stage(sf::Texture* skyTexture, sf::Texture* groundTexture, sf::Texture* crustTexture,int count) {
	
	float stage_height[] = { 675,675,600,300,200,100,500,600,800,1300};
	for (int i = 1; i <= count; i++) {
		sf::RectangleShape gr(sf::Vector2f(1000.0f, 250.0f));
		gr.setOrigin(500.0f, 125.0f);
		gr.setTexture(groundTexture);
		gr.setPosition((1000.0f * float(i) - 500.0f), stage_height[i - 1]);

		sf::RectangleShape sk(sf::Vector2f(1000.0f, 550.0f));
		sk.setTexture(skyTexture);
		sk.setPosition(1000.0f * float(i - 1), stage_height[i - 1] - 675);
		
		sf::RectangleShape cr(sf::Vector2f(1000.0f, 400.0f));
		cr.setTexture(crustTexture);
		cr.setOrigin(500.0f, 200.0f);
		cr.setPosition(1000.0f * float(i) - 500.0f, stage_height[i - 1]+325.0f);
		
		crust.push_back(cr);
		sky.push_back(sk);
		ground.push_back(gr);
	}
}
