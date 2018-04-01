#include "Enemy.h"

Enemy::Enemy(String texture, int status, String elementSound) {
	EnemyTexture.loadFromFile(texture);
	sprite.setTexture(EnemyTexture);
	rect.setSize(Vector2f(64, 64));
	buffer.loadFromFile(elementSound);
	sound.setBuffer(buffer);
	sound.setVolume(30);
	enemyStatus = status;
	movementSpeed = 10;
	spriteAnimation = 0;
	removeEnemy = false;
	sprite.setTextureRect(IntRect(0,64*2, 64, 64));
	//sprite.scale(Vector2f(2, 2));
	movementTime = 0;
	direction = (rand() % 4) + 1;
	srand(time(NULL));
}

void Enemy::update() {
	sprite.setPosition(rect.getPosition());
}

// TODO -  need to update the rectangle size so that it matches the sprite, it's very wonky when movement/direction is involved
void Enemy::enemyMovement() {
	movementTime++;
	if (movementTime >= 15) {
		movementTime = 0;
		direction = (rand() % 4) + 1;
	}
	if (direction == 1) { // UP
		sprite.setTextureRect(IntRect(spriteAnimation * 64, 64*8, 64, 64));
		if (rect.getPosition().y <= 0) {
			rect.move(0, 0);
			direction = 2;
		}
		else
			rect.move(0, -movementSpeed);
	}
	else if (direction == 2) { // DOWN
		sprite.setTextureRect(IntRect(spriteAnimation * 64, 64 * 10, 64, 64));
		if (rect.getPosition().y >= 720 - 60) {
			rect.move(0, 0);
			direction = 1;
		}
		else
			rect.move(0, movementSpeed);
	}
	else if (direction == 3) { // LEFT
		sprite.setTextureRect(IntRect(spriteAnimation * 64, 64*9, 64, 64));
		if (rect.getPosition().x <= 0) {
			rect.move(0, 0);
			direction = 4;
		}
		else
			rect.move(-movementSpeed, 0);
	}
	else if (direction == 4) { // RIGHT
		sprite.setTextureRect(IntRect(spriteAnimation * 64, 64*11, 64, 64));
		if (rect.getPosition().x >= 1280 - 59) {
			rect.move(0, 0);
			direction = 3;
		}
		else
			rect.move(movementSpeed, 0);
	}

	// to loop through the sprite animation left to right
	spriteAnimation++;
	if (spriteAnimation == 6)
		spriteAnimation = 0;
}

// enemy temporarily unable to move
void Enemy::enemyTerror() {
	sprite.setTextureRect(IntRect(64 * 5, 64 * 2, 64, 64));
	direction = 0;
	movementTime = 0;
}