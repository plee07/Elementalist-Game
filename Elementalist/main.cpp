#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <ctime>

#include "Player.h"
#include "Entity.h"
#include "Projectile.h"
#include "Enemy.h"

using namespace sf;

int main() {
	// Variable Declaration
	Vector2f Resolution(1280,720);
	Texture BackgroundTexture;
	Texture Icon;
	Sprite ElementIcon;
	Sprite Background;
	Text gameOverText;
	Text victoryText;
	Music BackgroundMusic;
	SoundBuffer buffer1;
	SoundBuffer buffer2;
	Sound scream;
	Sound shoot;
	Player MainPlayer;
	Clock projectile_clock;
	Time projectile_cooldown;
	Clock element_clock;
	Time element_timer;
	Clock playerToEnemyCollision_clock;
	Time playerToEnemyCollision_cooldown;
	srand(time(NULL));
	bool gameStart = false;
	const int numberOfEnemies = 10;
	int counter = 0;
	int PlayerStunCountdown = 6;
	int enemyDeathCount = 0;

	// Load the font
	Font font;
	if (!font.loadFromFile("Font/8blimro.ttf"))
		std::cout << "Did not load font\n";

	// Game Over
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(125);
	gameOverText.setPosition(100, 100);
	gameOverText.setString("Game Over!");
	gameOverText.setFillColor(Color::White);

	// Victory
	victoryText.setFont(font);
	victoryText.setCharacterSize(125);
	victoryText.setPosition(100, 100);
	victoryText.setString("YOU WIN!");
	victoryText.setFillColor(Color::White);

	// Projectile Vector Array declaration
	std::vector<Projectile>::const_iterator iter;
	std::vector<Projectile> projectileArray;
	Projectile Projectile1;

	// Enemy Vector Array declaration
	std::vector<Enemy>::const_iterator iter2;
	std::vector<Enemy> enemyArray;

	// declare and load enemy sprite
	Enemy enemyEarth("Graphics/enemyEarth.png", 1, "Music/earth.wav");
	Enemy enemyFire("Graphics/enemyFire.png", 2, "Music/fire.wav");
	Enemy enemyWater("Graphics/enemyWater.png", 3, "Music/chill.wav");
	Enemy enemyThunder("Graphics/enemyThunder.png", 4, "Music/thunder.wav");
	
	// Create the window
	RenderWindow Window(VideoMode(Resolution.x, Resolution.y), "Elementalist", Style::Close);

	// load the background image, music, and element icon
	BackgroundTexture.loadFromFile("Graphics/background.png");
	Background.setTexture(BackgroundTexture);
	BackgroundMusic.openFromFile("Music/Root.ogg");
	BackgroundMusic.setVolume(15);
	BackgroundMusic.play();
	BackgroundMusic.setLoop(true);
	Icon.loadFromFile("Graphics/elemental_icon.png");
	ElementIcon.setTexture(Icon);
	ElementIcon.scale(Vector2f(2, 2));

	// load sound effects
	buffer1.loadFromFile("Music/scream.wav");
	scream.setBuffer(buffer1);
	scream.setVolume(50);
	buffer2.loadFromFile("Music/projectile.wav");
	shoot.setBuffer(buffer2);
	shoot.setVolume(100);
	
	// loop to create random enemies
	for (int i = 0; i < numberOfEnemies; i++) {
		int randomEnemy = rand() % 4 + 1;
		int enemyXPosition = rand() % (Window.getSize().x - 200 );
		int enemyYPosition = rand() % Window.getSize().y;
		switch (randomEnemy) {
		case 1: // create earth enemy
			enemyEarth.rect.setPosition(enemyXPosition, enemyYPosition);
			enemyArray.push_back(enemyEarth);
			break;
		case 2: // create fire enemy
			enemyFire.rect.setPosition(enemyXPosition, enemyYPosition);
			enemyArray.push_back(enemyFire);
			break;
		case 3: // create water enemy
			enemyWater.rect.setPosition(enemyXPosition, enemyYPosition);
			enemyArray.push_back(enemyWater);
			break;
		case 4: // create thunder enemy
			enemyThunder.rect.setPosition(enemyXPosition, enemyYPosition);
			enemyArray.push_back(enemyThunder);
			break;
		}
	}
	
	// game loop
	while (Window.isOpen()) {

		// Start various timer
		projectile_cooldown = projectile_clock.getElapsedTime();
		element_timer = element_clock.getElapsedTime();
		playerToEnemyCollision_cooldown = playerToEnemyCollision_clock.getElapsedTime();
		
		Window.setFramerateLimit(9);

		Event event;
		while (Window.pollEvent(event)) {
			//if (event.type == Event::Closed)
			if(Keyboard::isKeyPressed(Keyboard::Escape))
				Window.close();
		}

		Window.clear();
		Window.draw(Background);

		//TODO make this into a Player class method
		// display player's elemental status
		if (MainPlayer.playerStatus == 1) // Earth
			ElementIcon.setTextureRect(IntRect(0,32*4,32,32));
		if (MainPlayer.playerStatus == 2) // Fire
			ElementIcon.setTextureRect(IntRect(0, 0, 32, 32));
		if (MainPlayer.playerStatus == 3) // Water
			ElementIcon.setTextureRect(IntRect(32*9, 0, 32, 32));
		if (MainPlayer.playerStatus == 4) // Thunder
			ElementIcon.setTextureRect(IntRect(32*6, 0, 32, 32));
		Window.draw(ElementIcon);

		// Change player's status every 10 second
		if (element_timer.asSeconds() >= 10) {
			MainPlayer.playerStatus = (rand() % 4) + 1;
			element_clock.restart();
			Window.draw(ElementIcon);
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
		counter = 0;
		for (iter2 = enemyArray.begin(); iter2 != enemyArray.end(); iter2++) {
			enemyArray[counter].update();
			enemyArray[counter].enemyMovement();
			//Window.draw(enemyArray[counter].rect);
			Window.draw(enemyArray[counter].sprite);
			counter++;
		}

		// projectile to enemy collision
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++) {
			int counter2 = 0;
			for (iter2 = enemyArray.begin(); iter2 != enemyArray.end(); iter2++) {

				// Collision between enemy and projectile
				if (projectileArray[counter].rect.getGlobalBounds().intersects(enemyArray[counter2].rect.getGlobalBounds())) {
					//std::cout << "Enemy Colllision" << std::endl;
					scream.play();
					enemyArray[counter2].enemyTerror();
					projectileArray[counter].removeProjectile = true;
				}
				// wall collision
				if (
					projectileArray[counter].rect.getPosition().x <= 0 ||
					projectileArray[counter].rect.getPosition().x >= Resolution.x ||
					projectileArray[counter].rect.getPosition().y <= 0 ||
					projectileArray[counter].rect.getPosition().y >= Resolution.y
					) {
					projectileArray[counter].removeProjectile = true;
				}
				counter2++;
			}
			counter++;
		}

		// Delete projectile upon impact
		counter = 0;
		for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++) {
			if (projectileArray[counter].removeProjectile == true) {
				projectileArray.erase(iter);
				break;
			}
			counter++;
		}

		// Player to enemy collision
		counter = 0;
		for (iter2 = enemyArray.begin(); iter2 != enemyArray.end(); iter2++) {
			if (MainPlayer.rect.getGlobalBounds().intersects(enemyArray[counter].rect.getGlobalBounds())) {
				if (playerToEnemyCollision_cooldown.asSeconds() >= 2) {
					playerToEnemyCollision_clock.restart();
					scream.play();
					if (MainPlayer.playerStatus == 1 && enemyArray[counter].enemyStatus == 4) { // Player Earth beats  Enemy Thunder
						enemyArray[counter].enemyDead = true;
						enemyEarth.sound.play();
					}
					else if (MainPlayer.playerStatus == 4 && enemyArray[counter].enemyStatus == 3) { // Player Thunder beats Enemy Water
						enemyArray[counter].enemyDead = true;
						enemyThunder.sound.play();
					}
					else if (MainPlayer.playerStatus == 3 && enemyArray[counter].enemyStatus == 2) { // Player Water beats Enemy Fire
						enemyArray[counter].enemyDead = true;
						enemyWater.sound.play();
					}
					else if (MainPlayer.playerStatus == 2 && enemyArray[counter].enemyStatus == 1) { // Player Fire beats  Enemy Earth
						enemyArray[counter].enemyDead = true;
						enemyFire.sound.play();
					}
					else if (MainPlayer.playerStatus == 4 && enemyArray[counter].enemyStatus == 1) { // Enemy Earth beats Player Thunder
						MainPlayer.playerDeath();
						enemyEarth.sound.play();
					}
					else if (MainPlayer.playerStatus == 3 && enemyArray[counter].enemyStatus == 4) { // Enemy Thunder beats Player Water
						MainPlayer.playerDeath();
						enemyThunder.sound.play();
					}
					else if (MainPlayer.playerStatus == 2 && enemyArray[counter].enemyStatus == 3) { // Enemy Water beats Player Fire
						MainPlayer.playerDeath();
						enemyWater.sound.play();
					}
					else if (MainPlayer.playerStatus == 1 && enemyArray[counter].enemyStatus == 2) { // Enemy Fire beats Player Earth
						MainPlayer.playerDeath();
						enemyFire.sound.play();
					}

					else { // No weakness, scare player
						MainPlayer.playerTerror();
						enemyArray[counter].enemyTerror();
					}
				}
			}
			counter++;
		}

		// Delete enemy if hit with their weakness
		counter = 0;
		for (iter2 = enemyArray.begin(); iter2 != enemyArray.end(); iter2++){
			if (enemyArray[counter].enemyDead == true) {
				enemyArray.erase(iter2);
				enemyDeathCount++;
				std::cout << enemyDeathCount << std::endl;
				break;
			}
			counter++;
		}

		// Countdown begins if Player gets scared
		if (MainPlayer.playerPause) {
			Clock clock;
			Time timer = clock.getElapsedTime();
			if (timer.asSeconds() <= 0) {
				PlayerStunCountdown--;
				clock.restart();
			}
		}
		if (PlayerStunCountdown <= 0) {
			MainPlayer.playerPause = false;
			PlayerStunCountdown = 6;
		}

		// Output the characters position on console - to be deleted
		std::cout << "(Player: " << MainPlayer.rect.getPosition().x << "," << MainPlayer.rect.getPosition().y << ")" <<
			"Direction: " << MainPlayer.direction << " Status : " << MainPlayer.playerStatus << "Player Pause: " << MainPlayer.playerPause << std::endl;

		Window.draw(MainPlayer.sprite);
		MainPlayer.update();

		if(!MainPlayer.playerPause && !MainPlayer.playerDead) {
			MainPlayer.playerMovement();
		}

		// Game over status
		if (MainPlayer.playerDead) {
			counter = 0;
			for (iter2 = enemyArray.begin(); iter2 != enemyArray.end(); iter2++) {
				enemyArray.erase(iter2);
				break;
			}
			Window.draw(gameOverText);
			BackgroundMusic.stop();
		}

		// Victory status
		if (enemyDeathCount >= numberOfEnemies) {
			Window.draw(victoryText);
			BackgroundMusic.stop();
		}

		Window.display();
	}
}
