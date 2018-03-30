#include "Projectile.h"
#include "Player.h"

Projectile::Projectile() {
	rect.setSize(Vector2f(48, 48));
	rect.setPosition(0, 0);
	movementSpeed = 20;
	if (!PushProjectile.loadFromFile("Graphics/ghost.png"))
		std::cout << "Projectile Load Error";
	sprite.setTexture(PushProjectile);
	sprite.setTextureRect(IntRect(0, 0, 48, 48));
	sprite.scale(Vector2f(2, 2));
	removeProjectile = false;
}

void Projectile::update() {
	sprite.setPosition(rect.getPosition());
	if (direction == 1) {
		sprite.setTextureRect(IntRect(0, 48*3, 48, 48));
		rect.move(0, -movementSpeed); // up
	}
	if (direction == 2) {
		sprite.setTextureRect(IntRect(0, 48 * 0, 48, 48));
		rect.move(0, movementSpeed); // down
	}
	if (direction == 3) {
		sprite.setTextureRect(IntRect(0, 48 * 1, 48, 48));
		rect.move(-movementSpeed, 0); // left
	}
	if (direction == 4) {
		sprite.setTextureRect(IntRect(0, 48 * 2, 48, 48));
		rect.move(movementSpeed, 0); // right

	}
}
