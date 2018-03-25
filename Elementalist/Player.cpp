#include "Player.h"


Player::Player() {
	PlayerTexture.loadFromFile("Graphics/character.png");
	sprite.setTexture(PlayerTexture);
	rect.setSize(Vector2f(32, 48));
	rect.setPosition(100, 100);
	movementSpeed = 5;
	spriteAnimation = 0;
	sprite.setTextureRect(IntRect(0, 0, 32, 48));
	sprite.scale(Vector2f(2, 2));
}
void Player::update() {
	sprite.setPosition(rect.getPosition());
}

void Player::playerMovement() {
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		direction = 1;
		sprite.setTextureRect(IntRect(spriteAnimation * 32, 48 * 3, 32, 48));
		if (rect.getPosition().y <= 0)
			rect.move(0, 0);
		else
			rect.move(0, -movementSpeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		direction = 2;
		sprite.setTextureRect(IntRect(spriteAnimation * 32, 0, 32, 48));
		if (rect.getPosition().y >= 720 - 48)
			rect.move(0, 0);
		else
			rect.move(0, movementSpeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		direction = 3;
		sprite.setTextureRect(IntRect(spriteAnimation * 32, 48, 32, 48));
		if (rect.getPosition().x <= 0)
			rect.move(0, 0);
		else
			rect.move(-movementSpeed, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		direction = 4;
		sprite.setTextureRect(IntRect(spriteAnimation * 32, 48 * 2, 32, 48));
		if (rect.getPosition().x >= 1280 - 32)
			rect.move(0, 0);
		else
			rect.move(movementSpeed, 0);
	}

	// to loop through the sprite animation left to right
	spriteAnimation++;
	if (spriteAnimation == 4)
		spriteAnimation = 0;
}
