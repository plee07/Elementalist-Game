#include "Projectile.h"
#include "Player.h"

Projectile::Projectile() {
	rect.setSize(Vector2f(47, 43));
	rect.setPosition(0, 0);
	movementSpeed = 20;
	if (!PushProjectile.loadFromFile("Graphics/ball.png"))
		std::cout << "Projectile Load Error";
	sprite.setTexture(PushProjectile);
	sprite.setTextureRect(IntRect(237, 224, 47, 43));
	sprite.scale(Vector2f(2, 2));
}

void Projectile::update() {
	sprite.setPosition(rect.getPosition());
	if (direction == 1) {
		rect.move(0, -movementSpeed); // up
	}
	if (direction == 2) {
		rect.move(0, movementSpeed); // down
	}
	if (direction == 3) {
		rect.move(-movementSpeed, 0); // left
	}
	if (direction == 4) {
		rect.move(movementSpeed, 0); // right

	}
}
