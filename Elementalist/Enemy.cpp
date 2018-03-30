#include "Enemy.h"


Enemy::Enemy(String texture) {
	EnemyTexture.loadFromFile(texture);
	sprite.setTexture(EnemyTexture);
	rect.setSize(Vector2f(64, 64));
	//rect.setPosition(100, 100);
	alive = true;
	enemyHit = false;
	movementSpeed = 20;
	spriteAnimation = 0;
	sprite.setTextureRect(IntRect(0,64*2, 64, 64));
	sprite.scale(Vector2f(2, 2));
	movementTime = 0;
	srand(time(NULL));
}


void Enemy::update() {
	sprite.setPosition(rect.getPosition());
}

void Enemy::enemyMovement() {
	movementTime++;
	if (movementTime >= 15) {
		movementTime = 0;
		direction = rand() % 4 + 1;
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
		if (rect.getPosition().y >= 720 - 128) {
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
		if (rect.getPosition().x >= 1280 - 128) {
			rect.move(0, 0);
			direction = 3;
		}
		else
			rect.move(movementSpeed, 0);
	}
	else {
		// do nothing
	}

	// to loop through the sprite animation left to right
	spriteAnimation++;
	if (spriteAnimation == 6)
		spriteAnimation = 0;
}

// Note: change the direction to the opposite direction if you want a terror effect
// I decided to use terror/stun effect instead
void Enemy::enemyRetreat(int projectileDirection) {
	if (projectileDirection == 1) {
		direction = 2;
		movementTime = 0;
	}
	if (projectileDirection == 2) {
		direction = 1;
		movementTime = 0;
	}	if (projectileDirection == 3) {
		direction = 4;
		movementTime = 0;
	}	if (projectileDirection == 4) {
		direction = 3;
		movementTime = 0;
	}
}

void Enemy::enemyTerror() {
	direction = 0;
	movementTime = 0;
	for (int terrorAnimation = 0; terrorAnimation <= 7; terrorAnimation++) {
		sprite.setTextureRect(IntRect(64 * 6, 64 * terrorAnimation, 64, 64));
	}
	sprite.setTextureRect(IntRect(64 * 5, 64 * 20, 64, 64));

}