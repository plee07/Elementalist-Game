#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "Player.h"
#include "Entity.h"
#include "Projectile.h"
#include "Enemy.h"

using namespace sf;

int main() {

	// Variable Declaration
	const Vector2f Resolution(1280, 720);
	Texture PushSpellTexture;
	Texture tBackground;
	Sprite Background;
	Music BackgroundMusic;
	Player MainPlayer;
	int numberOfEnemies = 10;

	RenderWindow Window(VideoMode(Resolution.x, Resolution.y), "Random RPG Map", Style::Close);

	// 8 bit music source http://ericskiff.com/music/
	BackgroundMusic.openFromFile("Music/Root.ogg");

	// load the background image and music
	tBackground.loadFromFile("Graphics/background.png");
	Background.setTexture(tBackground);
	BackgroundMusic.setVolume(15);
	BackgroundMusic.play();

	// Projectile Vector Array
	std::vector<Projectile>::const_iterator iter;
	std::vector<Projectile> projectileArray;
	Projectile Projectile1;
	
	// Enemy Vector Array
	std::vector<Enemy>::const_iterator iter2;
	std::vector<Enemy> enemyArray;
	Enemy Enemy1;

	for (int i = 0; i < numberOfEnemies; i++) {
		int enemyXPosition = rand() % 1250;
		int enemyYPosition = rand() % 700;
		Enemy1.rect.setPosition(enemyYPosition, enemyXPosition);
		enemyArray.push_back(Enemy1);
	}

	// game loop
	while (Window.isOpen()) {
		Event event;
		Window.setFramerateLimit(9);

		while (Window.pollEvent(event)) {
			if (event.type == Event::Closed)
				Window.close();
		}
		Window.clear();
		Window.draw(Background);
		
		// Firing of a projectile
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			Projectile1.rect.setPosition
			(
				MainPlayer.rect.getPosition().x + MainPlayer.rect.getSize().x / 2 - Projectile1.rect.getSize().x / 2,
				MainPlayer.rect.getPosition().y + MainPlayer.rect.getSize().y / 2 - Projectile1.rect.getSize().y / 2
			);
			Projectile1.direction = MainPlayer.direction;
			projectileArray.push_back(Projectile1);
		}

		// Draw Projectile
		int counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++) { 
			projectileArray[counter].update();
			//Window.draw(projectileArray[counter].rect);
			Window.draw(projectileArray[counter].sprite);
			counter++;
		}
		
		// Draw Enemy
		int enemyCounter = 0;
		for (iter2 = enemyArray.begin(); iter2 != enemyArray.end(); iter2++) {
			enemyArray[enemyCounter].update();
			enemyArray[enemyCounter].enemyMovement();
			//Window.draw(enemyArray[enemyCounter].rect);
			Window.draw(enemyArray[enemyCounter].sprite);
			enemyCounter++;
		}

		// Output the characters position on console - to be deleted
		std::cout << "(Player: " << MainPlayer.rect.getPosition().x << "," << MainPlayer.rect.getPosition().y << ")" << std::endl;

		Window.draw(MainPlayer.sprite);
		MainPlayer.update();

		MainPlayer.playerMovement();

		Window.display();
	}
}
