#include "Player.h"

Player::Player() {
	PlayerTexture.loadFromFile("Graphics/mainCharacter.png");
	sprite.setTexture(PlayerTexture);
	rect.setSize(Vector2f(64, 64));
	rect.setPosition(1100, 100);
	movementSpeed = 10;
	spriteAnimation = 0;
	sprite.setTextureRect(IntRect(0, 64 * 2, 64, 64));
	//sprite.scale(Vector2f(2, 2));
	direction = 2;
	srand(time(NULL));
	playerStatus = (rand() % 4) + 1;
	//sprite.setColor(Color::Yellow);
}
void Player::update() {
	sprite.setPosition(rect.getPosition());
}

void Player::playerMovement() {
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		direction = 1;
		sprite.setTextureRect(IntRect(spriteAnimation * 64, 64 * 8, 64, 64));
		if (rect.getPosition().y <= 0)
			rect.move(0, 0);
		else
			rect.move(0, -movementSpeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		direction = 2;
		sprite.setTextureRect(IntRect(spriteAnimation * 64, 64 * 10, 64, 64));
		if (rect.getPosition().y >= 720-60)
			rect.move(0, 0);
		else
			rect.move(0, movementSpeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		direction = 3;
		sprite.setTextureRect(IntRect(spriteAnimation * 64, 64 * 9, 64, 64));
		if (rect.getPosition().x <= 0)
			rect.move(0, 0);
		else
			rect.move(-movementSpeed, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		direction = 4;
		sprite.setTextureRect(IntRect(spriteAnimation * 64, 64 * 11, 64, 64));
		if (rect.getPosition().x >= 1280-50)
			rect.move(0, 0);
		else
			rect.move(movementSpeed, 0);
	}

	// to loop through the sprite animation left to right
	spriteAnimation++;
	if (spriteAnimation == 4)
		spriteAnimation = 0;
}
