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
	SoundBuffer buffer1;
	SoundBuffer buffer2;
	Sound ScreamSoundEffect;
	Sound shoot;
	Player MainPlayer;
	int numberOfEnemies = 10;
	Clock projectile_clock;
	Time projectile_cooldown;
	int counter = 0;
	int counter2 = 0;

	// Create the window
	RenderWindow Window(VideoMode(Resolution.x, Resolution.y), "Random RPG Map", Style::Close);

	// 8 bit music source http://ericskiff.com/music/
	BackgroundMusic.openFromFile("Music/Root.ogg");

	// load the background image and music
	tBackground.loadFromFile("Graphics/background.png");
	Background.setTexture(tBackground);
	BackgroundMusic.setVolume(15);
	BackgroundMusic.play();
	BackgroundMusic.setLoop(true);

	// load sound effects
	buffer1.loadFromFile("Music/scream.wav");
	ScreamSoundEffect.setBuffer(buffer1);
	ScreamSoundEffect.setVolume(25);
	buffer2.loadFromFile("Music/projectile.wav");
	shoot.setBuffer(buffer2);
	shoot.setVolume(100);
	
	// Projectile Vector Array
	std::vector<Projectile>::const_iterator iter;
	std::vector<Projectile> projectileArray;
	Projectile Projectile1;
	
	// Enemy Vector Array
	std::vector<Enemy>::const_iterator iter2;
	std::vector<Enemy> enemyArray;
	Enemy enemyEarth("Graphics/enemyEarth.png");
	Enemy enemyWater("Graphics/enemyWater.png");
	Enemy enemyThunder("Graphics/enemyThunder.png");
	Enemy enemyFire("Graphics/enemyFire.png");

	// loop to create random enemies
	for (int i = 0; i < numberOfEnemies; i++) {
		int randomEnemy = rand() % 4 + 1;
		int enemyXPosition = rand() % Window.getSize().x;
		int enemyYPosition = rand() % Window.getSize().y;
		switch (randomEnemy) {
		case 1: // create earth enemy
			enemyEarth.rect.setPosition(enemyYPosition, enemyXPosition);
			enemyArray.push_back(enemyEarth);
			break;
		case 2: // create fire enemy
			enemyFire.rect.setPosition(enemyYPosition, enemyXPosition);
			enemyArray.push_back(enemyFire);
			break;
		case 3: // create water enemy
			enemyWater.rect.setPosition(enemyYPosition, enemyXPosition);
			enemyArray.push_back(enemyWater);
			break;
		case 4: // create thunder enemy
			enemyThunder.rect.setPosition(enemyYPosition, enemyXPosition);
			enemyArray.push_back(enemyThunder);
			break;
		}
	}

	// game loop
	while (Window.isOpen()) {
		projectile_cooldown = projectile_clock.getElapsedTime();
		Event event;
		Window.setFramerateLimit(9);

		while (Window.pollEvent(event)) {
			if (event.type == Event::Closed)
				Window.close();
		}
		Window.clear();
		Window.draw(Background);

		// projectile collision
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++) {
			counter2 = 0;
			for (iter2 = enemyArray.begin(); iter2 != enemyArray.end(); iter2++) {
				
				// Collision between enemy and projectile
				if (projectileArray[counter].rect.getGlobalBounds().intersects(enemyArray[counter2].rect.getGlobalBounds())) {
					std::cout << "Colllision has occured" << std::endl;
					ScreamSoundEffect.play();
					//enemyArray[counter2].enemyRetreat(projectileArray[counter].direction);
					enemyArray[counter2].enemyTerror();
					projectileArray[counter].removeProjectile = true;
				}
				// TODO: return to this one, projectile is not getting deleted upon hitting wall
				if (
					projectileArray[counter].rect.getPosition().x == 0 ||
					projectileArray[counter].rect.getPosition().x == Resolution.x ||
					projectileArray[counter].rect.getPosition().y == 0 ||
					projectileArray[counter].rect.getPosition().y == Resolution.y
					) {
					projectileArray[counter].removeProjectile = true;
					std::cout << "Projectile Deleted upon wall hit\n";
				}
				counter2++;
			}
			counter++;
		}
		
		/*
		// Delete enemy upon impact
		counter = 0;
		for (iter2 = enemyArray.begin(); iter2 != enemyArray.end(); iter2++) {
			if (enemyArray[counter].enemyHit == true) {
				projectileArray[counter].d
				//enemyArray.erase(iter2);
				enemyArray[counter].enemyHit == false;
				break;
			}
			counter++;
		}
		*/
		
		// Delete projectile upon impact
		// TODO - add sound effect for projectile hit
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++) {
			if (projectileArray[counter].removeProjectile == true) {
				projectileArray.erase(iter);
				break;
			}
			counter++;
		}

		// Firing of a projectile, limited to 1 per 1.5sec
		if (Keyboard::isKeyPressed(Keyboard::Space) && projectile_cooldown.asSeconds() >= 1.5f) {
			shoot.play();
			projectile_clock.restart();
			Projectile1.rect.setPosition
			(
				MainPlayer.rect.getPosition().x + MainPlayer.rect.getSize().x / 2 - Projectile1.rect.getSize().x / 2,
				MainPlayer.rect.getPosition().y + MainPlayer.rect.getSize().y / 2 - Projectile1.rect.getSize().y / 2
			);
			Projectile1.direction = MainPlayer.direction;
			projectileArray.push_back(Projectile1);
		}


		// Draw Projectile
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++) { 
			projectileArray[counter].update();
			//Window.draw(projectileArray[counter].rect);
			Window.draw(projectileArray[counter].sprite);
			counter++;
		}
		
		// Draw Enemy
		counter2 = 0;
		for (iter2 = enemyArray.begin(); iter2 != enemyArray.end(); iter2++) {
			enemyArray[counter2].update();
			enemyArray[counter2].enemyMovement();
			//Window.draw(enemyArray[enemyCounter].rect);
			Window.draw(enemyArray[counter2].sprite);
			counter2++;
		}

		// Output the characters position on console - to be deleted
		std::cout << "(Player: " << MainPlayer.rect.getPosition().x << "," << MainPlayer.rect.getPosition().y << ")" << MainPlayer.direction << std::endl;

		Window.draw(MainPlayer.sprite);
		MainPlayer.update();
		MainPlayer.playerMovement();
		Window.display();
	}
}
