#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "Player.h"
#include "Entity.h"
#include "Projectile.h"

using namespace sf;

int main() {

	// Variable Declaration
	const Vector2f Resolution(1280, 720);
	Texture PushSpellTexture;
	Texture tBackground;
	Sprite Background;
	Music BackgroundMusic;

	RenderWindow Window(VideoMode(Resolution.x, Resolution.y), "Random RPG Map", Style::Close);

	// 8 bit music source http://ericskiff.com/music/
	BackgroundMusic.openFromFile("Music/Root.ogg");

	// load the background image and music
	tBackground.loadFromFile("Graphics/background.png");
	Background.setTexture(tBackground);
	BackgroundMusic.setVolume(15);
	BackgroundMusic.play();

	class Player MainPlayer;

	// Create the projectile vector
	std::vector<Projectile>::const_iterator iter;
	std::vector<Projectile> projectileArray;
	Projectile Projectile1;


	// game loop
	while (Window.isOpen()) {
		Event event;
		Window.setFramerateLimit(9);
		//Time time = clock.getElapsedTime();


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
			Window.draw(projectileArray[counter].sprite);
			counter++;
		}

		// Output the characters position on console - to be deleted eventually
		std::cout << "(" << MainPlayer.rect.getPosition().x << "," << MainPlayer.rect.getPosition().y << ")" << std::endl;

		Window.draw(MainPlayer.sprite);
		MainPlayer.update();
		MainPlayer.playerMovement();

		Window.display();
	}
}
